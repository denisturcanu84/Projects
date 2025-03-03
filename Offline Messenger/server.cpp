// Sa se dezvolte o aplicatie client/server care sa permita schimbul
// de mesaje intre utilizatori care sunt conectati si sa ofere functionalitatea 
//trimiterii mesajelor si catre utilizatorii offline, acestora din urma aparandu-le
// mesajele atunci cand se vor conecta la server. De asemenea, utilizatorii vor avea
// posibilitatea de a trimite un raspuns (reply) in mod specific la anumite mesaje primite.
// Aplicatia va oferi si istoricul conversatiilor pentru si cu fiecare utilizator in parte. 
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <sstream>
#include <mutex>
#include <shared_mutex> // pt logged users
#include <unordered_map>
#include <queue>
#include <fstream>

using namespace std;

#define PORT 2222

struct Message {
    string sender;
    string receiver;
    string content;
    int message_id;
    int reply_to_id;  // it's -1 if the message is not a reply
};

// global counters
static int client_count = 0;
static int message_id_counter = 0;

mutex message_id_mutex;

// maps for user management
unordered_map<string, int> logged_users; // username, socket
unordered_map<int, string> socket_to_username; // socket, username
shared_mutex logged_users_mutex;

// storage for offline messages and message history
unordered_map<string, queue<Message>> offline_messages; // username -> coada de mesaje offline
mutex offline_messages_mutex;
unordered_map<string, vector<Message>> message_history; // username -> toate mesajele
mutex history_mutex;

// string manipulation functions
string toLowerAndTrim(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    return s;
}
string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// generate unique ID s for each message
int getNextMessageId() {
    lock_guard<mutex> lock(message_id_mutex);
    return ++message_id_counter;
}

// save message to both users history
void saveMessageToHistory(const Message& msg) {
    lock_guard<mutex> lock(history_mutex);
    message_history[msg.sender].push_back(msg);
    message_history[msg.receiver].push_back(msg);
}

// MAIN COMMAND HANDLER FUNCTION
string handle_command(const string& command, int client_socket) {
    string local_username;

    // WHOISONLINE - show all online users
    if (command == "whoisonline") {
        shared_lock<shared_mutex> lock(logged_users_mutex);
        string online_users_list;
          if(logged_users.empty()){
            online_users_list = "No users online";
          } else {
                online_users_list = "Online users:\n";
                for (const auto& pair : logged_users) {
                    online_users_list += toUpper(pair.first) + "\n";
                }
          }
          return online_users_list;
     }

    // WHOAMI - shows the current user
    else if(command == "whoami"){
        if (socket_to_username.count(client_socket)) {
            string local_username = socket_to_username[client_socket];
            return "You are logged in as: " + local_username;
        } else {
            return "You are not logged in.";
        }
    }
    
    // LOGIN - log in with a username
    else if (command.find("login") == 0) {
        string params = command.substr(5);
        stringstream ss(params);
        getline(ss, local_username);
        
        if (local_username.empty()) {
            return "Usage: login <username>";
        }

        if (socket_to_username.count(client_socket)) {
            return "You are already logged in as: " + socket_to_username[client_socket];
        }

        local_username = toLowerAndTrim(local_username);
        if (logged_users.find(local_username) == logged_users.end()) {
            unique_lock<shared_mutex> lock(logged_users_mutex);
            logged_users[local_username] = client_socket;
            socket_to_username[client_socket] = local_username;
            
            // deliver offline messages if any
            lock_guard<mutex> offline_lock(offline_messages_mutex);
            if (offline_messages.count(local_username)) {
                while (!offline_messages[local_username].empty()) {
                    Message msg = offline_messages[local_username].front();
                    offline_messages[local_username].pop();
                    
                    string prefix = (msg.reply_to_id != -1) ? "[Reply to " + to_string(msg.reply_to_id) + "]" : "";
                    string offline_msg = "[OFFLINE MESSAGE][" + to_string(msg.message_id) + "]" +  prefix + "[" + toUpper(msg.sender) + "]: " +  msg.content + "\n";
                    send(client_socket, offline_msg.c_str(), offline_msg.length(), 0);
                }
            }
            return "You've been logged in.";
        }
        return "Username '" + local_username + "' is already in use.";
    }
    
    // LOGOUT 
    else if(command == "logout"){
        unique_lock<shared_mutex> lock(logged_users_mutex);
        if(socket_to_username.count(client_socket)){
        string local_username = socket_to_username[client_socket];
        socket_to_username.erase(client_socket);
        logged_users.erase(local_username);
        return "You've been logged out.";
        } else return "You're not logged in.";
    }

    // MESSAGE <USERNAME> <TEXT> - send a message to a user
    else if (command.find("message") == 0) {
        shared_lock<shared_mutex> lock(logged_users_mutex);
        if (!socket_to_username.count(client_socket)) {
            return "You must be logged in";
        }

        string params = command.substr(8);
        string local_username = socket_to_username[client_socket];
        size_t first_space = params.find(' ');

        if (first_space == string::npos) {
            return "Usage: message <receiver_username> <message>";
        }

        string receiver_username = toLowerAndTrim(params.substr(0, first_space));
        string message_content = params.substr(first_space + 1);
        
        Message msg {
            toLowerAndTrim(local_username), // sender
            receiver_username, // receiver
            message_content, // message content
            getNextMessageId(), // message ID
            -1  // is not a reply message
        };

       // check if the receiver is online
                if (logged_users.count(receiver_username)) {
            int receiver_socket = logged_users[receiver_username];
            string full_message = "[" + to_string(msg.message_id) + "][" + toUpper(local_username) + "]: " + message_content + "\n";
            send(receiver_socket, full_message.c_str(), full_message.length(), 0);
        } else {
            // Save the message for offline delivery
            lock_guard<mutex> offline_lock(offline_messages_mutex);
            offline_messages[receiver_username].push(msg);
            return "User is offline. Message will be delivered when they log in.";
        }

        saveMessageToHistory(msg);
        return "Message sent successfully to " + receiver_username;
    }

    // REPLY <MESSAGE_ID> <USERNAME> <TEXT> - reply to a specific message
    else if (command.find("reply") == 0) {

        if (!socket_to_username.count(client_socket)) {
            return "You must be logged in";
        }

        // it extracts the message ID, receiver username and message content
        stringstream ss(command.substr(6));
        int reply_to_id;
        string receiver_username;
        string message_content;

        ss >> reply_to_id >> receiver_username;
        getline(ss, message_content);

        if (message_content.empty() || receiver_username.empty()) {
            return "Usage: reply <message_id> <username> <message>";
        }

        message_content = message_content.substr(1); // remove leading space

        // create a new message with reply flag set
        Message msg {
            socket_to_username[client_socket], // sender
            toLowerAndTrim(receiver_username),   // receiver
            message_content,    // message content
            getNextMessageId(), // generate a new message ID
            reply_to_id // sets the reply flag
        };
        
        // send or store the message
        if (logged_users.count(receiver_username)) {
            // if user is online, sends the message directly
            int receiver_socket = logged_users[receiver_username];
            string full_message = "[Reply to " + to_string(reply_to_id) + "][" +  toUpper(msg.sender) + "]: " + message_content + "\n";
            send(receiver_socket, full_message.c_str(), full_message.length(), 0);
        } else {
            // if user is offline, stores the message in the offline queue
            lock_guard<mutex> offline_lock(offline_messages_mutex);
            offline_messages[receiver_username].push(msg);
        }

        saveMessageToHistory(msg);
        return "Reply sent successfully";
    }

    // GETHISTORY <USERNAME> - get the chat history with a specific user
    else if (command.find("gethistory") == 0) {

        if (!socket_to_username.count(client_socket)) {
            return "You must be logged in";
        }

        // get target username
        string params = command.substr(10);
        string target_username = toLowerAndTrim(params);
        
        if (target_username.empty()) {
            return "Usage: gethistory <username>";
        }

        string current_user = socket_to_username[client_socket];

        if (toLowerAndTrim(current_user) == toLowerAndTrim(target_username)) {
        return "You cannot view your own history. Specify another user.";
        }

        lock_guard<mutex> history_lock(history_mutex);
        
        stringstream history_stream;
        history_stream << "Chat history with " << toUpper(target_username) << ":\n";
        
        if (message_history.count(current_user)) {
            // loop through all the messages
            for (const auto& msg : message_history[current_user]) {
                // only include messages between the current user and the target user
                if (msg.sender == target_username || msg.receiver == target_username) {
                    // add reply prefix if it's a reply message
                    string prefix = (msg.reply_to_id != -1) ? "[Reply to " + to_string(msg.reply_to_id) + "]" : "";
                    history_stream << "[" << msg.message_id << "]" << prefix << "[" << toUpper(msg.sender) << "]: " << msg.content << "\n";
                }
            }
        }
        
        return history_stream.str();
    }
    else {
    return "Invalid command: " + command;
  }
}

// handler for each client connection
void handle_client(int client_socket) {
    int client_number = ++client_count; 

    char buffer[1024] = {0};
    cout << "Client " << client_number << " connected" << endl;

    while (true) {
        memset(buffer, 0, sizeof(buffer)); 
        int valread = read(client_socket, buffer, 1024); // read command from client

        // handle client disconnection
        if (valread <= 0) { 
            unique_lock<shared_mutex> lock(logged_users_mutex);
            if(socket_to_username.count(client_socket)){
              string username = socket_to_username[client_socket];
              socket_to_username.erase(client_socket);
              logged_users.erase(username);
              cout << "User [" << username << "] with client ID: [" << client_number << " ] has been disconnected" << endl;
            }
            close(client_socket);
            return;
        }
        string command(buffer);
        cout << "Client " << client_number << " input: " << command << endl;

        // processes the command and sends the response back to the client
        string response = handle_command(command, client_socket);
        send(client_socket, response.c_str(), response.length(), 0);
    }
}

int main() {
    // initialize server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        cerr << "Socket creation failed" << endl;
        return -1;
    }

    // setup server address
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // bind socket to the address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        cerr << "Binding failed" << endl;
        return -1;
    }

    // listen for connections
    if (listen(server_fd, 3) < 0) {
        cerr << "Listening failed" << endl;
        return -1;
    }

    cout << "Server started on port " << PORT << endl;

    // MAIN SERVER LOOP
    while (true) {
        int client_socket;
        sockaddr_in client_address;
        socklen_t addrlen = sizeof(client_address);

        // accept new client connections
        client_socket = accept(server_fd, (struct sockaddr *)&client_address, &addrlen);
        if (client_socket < 0) {
        cerr << "Accepting connection failed" << endl;
        continue;
        }

        // create a new thread for each client
        thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }
    
    return 0;
}

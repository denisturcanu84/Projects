#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <mutex>
#include <map>
#include <sstream>
using namespace std;

#define PORT 2222

// mutex for thread safe console output
mutex cout_mutex;

// cache to store received messages for reply functionality
map<int, string> message_cache;

void print_help() {
    cout << "\nAvailable commands:" << endl;
    cout << "login <username> - Log in with the specified username" << endl;
    cout << "message <username> <message> - Send a message to a user" << endl;
    cout << "reply <message_id> <username> <message> - Reply to a specific message" << endl;
    cout << "gethistory <username> - Get chat history with a specific user" << endl;
    cout << "whoisonline - See who is currently online" << endl;
    cout << "whoami - See your current username" << endl;
    cout << "help - Show this help message" << endl;
    cout << "exit - Exit the application\n" << endl;
}

void clear_current_line() {
    cout << "\r\033[K"; // \r moves cursor to start, \033[K clears the line
}

// thread function to handle incoming messages from the server
void receive_messages(int sock) {
    char buffer[1024] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            string message = buffer;
            
            // process message for caching - extracts message ID if present
            size_t start_bracket = message.find('[');
            size_t end_bracket = message.find(']');
            if (start_bracket != string::npos && end_bracket != string::npos) {
                string id_part = message.substr(start_bracket + 1, end_bracket - start_bracket - 1);
                if (id_part.find_first_not_of("0123456789") == string::npos) {
                    int msg_id = stoi(id_part);
                    message_cache[msg_id] = message;
                }
            }

            // thread-safe console output
            {
                lock_guard<mutex> lock(cout_mutex);
                clear_current_line(); 
                cout << message << endl;
                cout << "Enter Command: " << flush; // re-print the command prompt
            }
        } else if (valread <= 0) {

            // handle disconnection from server
            {
                lock_guard<mutex> lock(cout_mutex);
                cout << "\nDisconnected from server.\n";
                close(sock);
            }
            break;
        }
    }
}

// function to print a cached message when using the 'reply' command
void print_cached_message(int message_id) {
    if (message_cache.find(message_id) != message_cache.end()) {
        cout << "Referenced message:\n" << message_cache[message_id] << endl;
    } else {
        cout << "Message with ID " << message_id << " not found in cache.\n" << endl;
    }
}

int main() {

    // initialize socket
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    // create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\nSocket creation error\n";
        return -1;
    }

    // setup server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << "\nInvalid address/ Address not supported\n";
        return -1;
    }

    // connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "\nConnection Failed\n";
        return -1;
    }

    cout << "Connected to server. Type 'help' for available commands.\n" << endl;
    
    // start message receiver thread
    thread receiver_thread(receive_messages, sock);

    // main loop to read user input
    string command;
    while (true) {
        cout << "Enter Command: " << flush;
        getline(cin, command);

        if (command.empty()) {
            continue;
        }
        
        // handle local commands 
        if (command == "help") {
            print_help();
            continue;
        } else if (command == "exit") {
            send(sock, command.c_str(), command.length(), 0);
            close(sock);
            break;
        } else if (command.find("reply") == 0) {
            // show the message being replied to
            stringstream ss(command.substr(6));
            int reply_to_id;
            ss >> reply_to_id;
            {
                lock_guard<mutex> lock(cout_mutex);
                print_cached_message(reply_to_id);
            }
        }

        // send the command to the server
        if (send(sock, command.c_str(), command.length(), 0) < 0) {
            cout << "Failed to send command to server.\n";
            break;
        }
    }

    // wait for the receiver thread to finish
    receiver_thread.join(); 
    return 0;
}
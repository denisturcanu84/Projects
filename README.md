# Projects

## COLTUL NEGRU

[Watch on YouTube](https://www.youtube.com/watch?v=sVfXm--K9XI&lc=Ugwsw_4Z1Nme3x8Wno14AaABAg)

### Technologies Used

- **C++** for game logic and implementation
- **Graphics.h and WinBGIm** for graphical interface
- **Standard Library functions** for various utilities

### How to Play "Coltul Negru"

#### Game Objective
- Create a continuous path that connects the first piece on the board to the colored corner.
- The player who completes the path to the colored corner wins.
- The player who leads the path out of the board loses.
- Each player must continue the path.

#### Game Instructions
- Press the UP/DOWN arrow keys to choose the desired piece and ENTER to select it.
- Left-click with the mouse to place the piece on a possible spot.

#### Rules
- Each player must continue the path with the available pieces.
- If the path goes out of the board, that player loses.
- If the path reaches the colored corner, that player wins.

#### Game Setup
- At the beginning of the game, choose the board size (4x4, 5x5, 6x6, 7x7, or 8x8).

#### Gameplay
- Each player selects a piece and places it on the board according to the rules.
- The game continues until a player wins or loses according to the rules.


## Offline Messenger

Think of this as WhatsApp or Messenger, but running on your local network. You can:

- Chat with other users in real-time
- Send messages to offline users (they'll get them when they log in)
- Reply to specific messages
- See your chat history with any user
- Check who's currently online

### Technologies Used

- **C++** for server and client implementation
- **TCP (Transmission Control Protocol)** for reliable communication
- **Multithreading** for handling multiple clients simultaneously
- **Mutexes and Shared Locks** for thread safety
- **Console I/O** for client interface

### How Does It Work?

#### The Server

The server acts as a post office, managing user connections and message delivery. It:

- Keeps track of who's online
- Delivers messages immediately to online users
- Holds messages for offline users
- Maintains conversation histories

#### The Client (Your Chat Window)

The client is your interface to the chat system. It:

- Connects to the server
- Shows incoming messages in real-time
- Lets you send messages and commands
- Keeps track of messages you might want to reply to

### Cool Features Explained

#### 1. Replying to Messages

You can reply to specific messages using a simple command structure.

#### 2. Offline Messages

Messages sent to offline users are stored and delivered when they log in.

#### 3. Chat History

You can retrieve your chat history with any user.

### Future Improvements

- **End-to-End Encryption**: Implement secure message encryption
- **Group Chats**: Allow multiple users to chat together
- **File Sharing**: Enable users to send files and images
- **GUI Client**: Create a graphical interface


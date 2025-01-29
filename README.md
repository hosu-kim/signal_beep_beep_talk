<p align="center">
  <img src="images/logo.webp" width="400">
</p>

# Signal beep beep talk
Siganl beep beep talk is a simple client-server communication project using UNIX signals.

The project demonstrates inter-process communication (IPC) by sending messages from a client to a server.
## Features
- **Client**: Sends a string message to the server, character by character, using signals.
- **Server**: Receives the message from the client, reconstructs it, and prints it out.
## Getting Started!
### Prerequisites
- A UNIX-like operating system (Linux, macOS, etc.)
- A C compiler (gcc, clang, etc.)
### Installation
1. Clone the repository:
``` sh
git clone git@github.com:hosu-kim/signal_beep_beep_talk.git
cd signal_beep_beep_talk
```
2. Compile the project:
``` sh
make
```
### Usage
1. Start the server:
``` sh
./server
```
The server will print its process ID (PID), which you will need to provide to the client.
2. In a separate terminal, run the client with the server's PID and the message you want to send:
``` sh
./client [server_pid] [message]
```
Replace [server_pid] with the actual PID of the server and [message] with the string you want to send.
### Example
1. Start the server:
``` sh
$ ./server
Server PID: 12345
```
2. In a separate terminal, send a message from the client:
``` sh
$ ./client 12345 "Hello, Beep! Beep!"
```
## Project Structure
- `client.c`: Contains the client implementation.
- `server.c`: Contains the server implementation.
- `includes/`: Contains the header files for the project.
- `Makefile`: Used to compile the project.
## How It Works
### Client
The client program takes two arguments: the server's PID and the message to send. It converts each character of the message into its binary representation and sends each bit using signals (`SIGUSR1` for bit 1 and `SIGUSR2` for bit 0).
### Server
The server program sets up signal handlers to receive the signals sent by the client. It reconstructs the received bits into characters and stores them in a buffer. When a null character (`\0`) is received, it prints the complete message.
### Signal Handlers
- `SIGUSR1`: Represents bit 1.
- `SIGUSR2`: Represents bit 0.
The server uses these signals to build the message character by character.
## Error Handling
- The client checks if the provided server PID is valid.
- The server dynamically resizes the buffer to accommodate the incoming message.
- The server handles buffer overflow by printing an error message if the buffer is full.
## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <thread>
#include <mutex>
#include "IMenu.h"
#include "DisplayRecommendedMoviesCommand.h"
#include "AddMovieCommand.h"
#include "HelpCommand.h"
#include "DeleteCommand.h"
#include "ICommand.h"
#include "ConsoleMenu.h"
#include "App.h"
#include "Utils.h"

#define MAX_CLIENTS 3
#define PORT 5555

using namespace std;

// Function to handle client requests
void handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesReceived;

    while (true) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0) {
                std::cout << "Client disconnected.\n";
            } else {
                std::cerr << "Error reading from client socket. Exiting...\n";
            }
            break;
        }

        buffer[bytesReceived] = '\0'; // Null-terminate the received data
        string input(buffer);

        // Add to command history
        Utils::appendToFile(input, "../data/commandsHistory.txt");

        // Extract command
        size_t res = input.find(" ");
        string command = (res != string::npos) ? input.substr(0, res) : input;

        // Initialize commands
        map<string, ICommand*> commands;
        commands["POST"] = new AddMovieCommand();
        commands["PATCH"] = new AddMovieCommand();
        commands["GET"] = new DisplayRecommendedMoviesCommand();
        commands["help"] = new HelpCommand();
        commands["DELETE"] = new DeleteCommand();

        string response = " ";

        // Simulate command execution
        if (commands.find(command) != commands.end()) {
            response = commands[command]->execute();
        } else {
            response = "\n";
        }

        // Send response back to the client
        send(clientSocket, response.c_str(), response.size(), 0);

        // Clean up commands
        for (auto& cmd : commands) {
            delete cmd.second;
        }
    }

    // Close the client socket after interaction ends
    close(clientSocket);
}

// Server entry point
int main() {
    // Clear Data
    Utils::clearFile("../data/movies.txt");
    Utils::clearFile("../data/commandsHistory.txt");

    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        // Create a new thread to handle this client
        thread clientThread(handleClient, clientSocket);
        clientThread.detach();  // Detach the thread to run independently
    }

    close(serverSocket);
    return 0;
}

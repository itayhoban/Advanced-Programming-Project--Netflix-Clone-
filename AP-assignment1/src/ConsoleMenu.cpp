#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "IMenu.h"
#include "DisplayRecommendedMoviesCommand.h"
#include "AddMovieCommand.h"
#include "HelpCommand.h"
#include "ICommand.h"
#include "ConsoleMenu.h"
#include "App.h"
#include "Utils.h"

using namespace std;

    // Constructor to initialize or test the class
    ConsoleMenu::ConsoleMenu() {
        // std::cout << "ConsoleMenu initialized." << std::endl;
    }

    // Implementation of the nextCommand method
    std::string ConsoleMenu::nextCommand() {
        std::string input;
        std::string task;

        // Read the input line
        if (!getline(std::cin, input)) {
            // If getline fails, exit the loop gracefully
            std::cerr << "Error: Failed to read input. Exiting..." << std::endl;
            exit(1); // Or return a special string to indicate termination
        }

        // Add to commands history
        Utils::appendToFile(input, "../data/commandsHistory.txt");

        // Extract the first word as the task
        size_t res = input.find(" ");
        if (res != std::string::npos) {
            task = input.substr(0, res);
        } else {
            task = input;
        }

        return task;
    }

    // Implementation of the displayError method
    void ConsoleMenu::displayError(const std::string& error) {
        cout << "Error: " << error;
    }

int main() {
    ConsoleMenu menu;

    // Clear Data
    Utils::clearFile("../data/movies.txt");
    Utils::clearFile("../data/commandsHistory.txt");

    // Initialize commands with dynamically allocated objects
    std::map<std::string, ICommand*> commands;
    commands["add"] = new AddMovieCommand();
    commands["recommend"] = new DisplayRecommendedMoviesCommand();
    commands["help"] = new HelpCommand();

    // Create and run the app
    App app(&menu, commands);
    app.run();

    // Clean up dynamically allocated commands
    for (auto& cmd : commands) {
        delete cmd.second;
    }

    return 0;
}



#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstring>
#include "AddMovieCommand.h"
#include "Utils.h"

using namespace std;

// Implementation of execute method
void AddMovieCommand::execute() {
    string command = lastCommand();

    // Remove extra spaces
    /*we storage the data by the following rules:
    1. The first word in each row is be the userID.
    2. The second word and so on are the movies the user watched.
    3. There will be exactly one space between each word. 
    */ 
    Utils::removeSpaces(command);
    
    // If valid command 
    if(isValidAddCommand(command)) {
        // Add arguments
        string arguments = Utils::trimFirstWord(command);
        string path = "../data/movies.txt";
        Utils::appendToFile(arguments, path);
    }
}

string AddMovieCommand::lastCommand() {
    // Get last command from commadsHistory.txt
    ifstream file("../data/commandsHistory.txt");
    if (!file.is_open()) {
        // Print error
        cerr << "Error: Unable to open file 'data/commandsHistory.txt'" << endl;
        return "";
    }

    string line;
    string lastLine;

    // Iterate through the file to find the last line
    while (getline(file, line)) {
        lastLine = line;
    }

    file.close();
    return lastLine;
}

bool AddMovieCommand::isValidAddCommand(string command) {
    if(Utils::containsTab(command)) return false;
    // The arguments are the command line without the task word (first word)
    string arguments = Utils::trimFirstWord(command);

    // No arguments
    if (arguments.compare("") == 0)
        return false; 
    
    // Valid iff arguments are valid
    return isValidAddArguments(arguments);
}

bool AddMovieCommand::isValidAddArguments(string arguments) {
    vector<string> args = Utils::split(arguments, ' ');
    // Not enough arguments
    if(args.size() < 2) return false;

    // Validate arguments
    for (int i = 0; i < args.size(); i++) {
        std::string word = args[i];
        if(!Utils::is_number(word)) return false;
    }

    return true;
}
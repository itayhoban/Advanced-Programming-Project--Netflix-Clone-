#include <iostream>
#include <fstream>
#include "HelpCommand.h"
#include "Utils.h"

using namespace std;

// Implementation of execute method
void HelpCommand::execute() {
    string command = lastCommand();
    if (HelpCommand::isValidHelpCommand(command)) {
    //     // Reading all commands from commadsHistory.txt
    //     ifstream file("../data/commandsHistory.txt");
    //     if (!file.is_open()) {
    //         // Print error
    //         cerr << "Error: Unable to open file 'data/commandsHistory.txt'" << endl;
    //         return;
    //     }

    //     string line;
    //     while (getline(file, line)) {
    //         cout << line << endl;
    //     }
    //     file.close();

    cout << "add [userid] [movieid1] [movieid2] ..." << endl;
    cout << "recommend [userid] [movieid]" << endl;
    cout << "help" << endl;
    }
}

string HelpCommand::lastCommand() {
    ifstream file("../data/commandsHistory.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '../data/commandsHistory.txt'" << endl;
        return "";
    }

    string line, lastLine;
    while (getline(file, line)) {
        lastLine = line;
    }

    file.close();
    return lastLine;
}

bool HelpCommand::isValidHelpCommand(string& command){
    if(Utils::containsTab(command)) return false;
    string arguments = Utils::trimFirstWord(command);

    if (!arguments.empty()) {
        return false; // No arguments
    }

    return true;
}

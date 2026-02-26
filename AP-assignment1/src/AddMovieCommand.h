#ifndef ADDMOVIECOMMAND_H
#define ADDMOVIECOMMAND_H

#include "ICommand.h"
#include <iostream>

using namespace std;

class AddMovieCommand : public ICommand {
public:
    void execute() override;
    string lastCommand();
    bool isValidAddCommand(string command);
    bool isValidAddArguments(string arguments);
};

#endif // ADDMOVIECOMMAND_H

#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include <string>
#include "IMenu.h"
#include "Utils.h"

class ConsoleMenu : public IMenu {
public:
    // Constructor
    ConsoleMenu();

    // Method to get the next command from the user
    std::string nextCommand() override;

    // Method to display an error message
    void displayError(const std::string& error) override;
};

#endif // CONSOLEMENU_H

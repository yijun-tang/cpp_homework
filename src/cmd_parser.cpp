#include "cmd_parser.h"
#include <iostream>

// Constructor to initialize command map
CommandParser::CommandParser() {
    // Populate the map with command functions
    commandMap["add"] = addProduct;
    commandMap["remove"] = removeProduct;
    commandMap["update"] = updateQuantity;
    commandMap["help"] = showHelp;
}

// Parse and execute a command
void CommandParser::parse(const std::string& command) {
    auto it = commandMap.find(command);
    if (it != commandMap.end()) {
        // Command found, execute the corresponding function
        it->second();
    } else {
        // Command not found
        std::cout << "Invalid command. Type 'help' for a list of available commands." << std::endl;
    }
}

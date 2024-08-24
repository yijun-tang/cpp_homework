#ifndef CMD_PARSER_H_
#define CMD_PARSER_H_

#include <map>
#include <functional>
#include <string>
#include "cmd_functions.h"

class CommandParser {
public:
    CommandParser();

    // Parse and execute a command
    void parse(const std::string& command);

private:
    // Associate command strings with functions
    std::map<std::string, std::function<void()>> commandMap;
};

#endif // CMD_PARSER_H_

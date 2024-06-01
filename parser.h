#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include <map>

class Command;
class Parser {
    std::map<std::string,std::string> comms;
    std::map<std::string,std::string> scomms;
    public:
    Parser();
    Command parse(std::string s);
    Command sparse(std::string s);
    int getInt(std::string s);
};


#endif
#ifndef COMMAND_H_
#define COMMAND_H_
#include <string>

class Command {
    std::string type;
    int times;
    public:
    std::string getType();
    int getTimes();
    void setType(std::string);
    void setTimes(int x);
};

#endif

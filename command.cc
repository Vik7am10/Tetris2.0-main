#include "command.h"
#include <string>

std::string Command::getType() {
    return type;
}

int Command::getTimes() {
    return times;
}

void Command::setType(std::string s) {
    type = s;
}

void Command::setTimes(int x) {
    times = x;
}

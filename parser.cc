#include "parser.h"
#include "command.h"
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <iostream>
using namespace std;

Parser::Parser() {
    comms["left"] = "left";
    comms["right"] = "right";
    comms["down"] = "down";
    comms["clockwise"] = "clockwise";
    comms["counterclockwise"] = "counterclockwise";
    comms["drop"] = "drop";
    comms["levelup"] = "levelup";
    comms["leveldown"] = "leveldown";
    comms["norandom"] = "norandom";
    comms["random"] = "random";
    comms["sequence"] = "sequence";
    comms["I"] = "I";
    comms["J"] = "J";
    comms["L"] = "L";
    comms["O"] = "O";
    comms["S"] = "S";
    comms["Z"] = "Z";
    comms["T"] = "T";
    comms["restart"] = "restart";
    scomms["blind"] = "blind";
    scomms["force"] = "force";
    scomms["heavy"] = "heavy";
}

Command Parser::parse(string s) {
    Command c;
    // find times:
    istringstream iss{s};
    int times = 0;
    if (iss >> times) {
        if (times < 0) { // bad arg
            c.setTimes(0);
            c.setType("invalid");
            return c;
        }
        c.setTimes(times);
        s = s.substr(to_string(times).length());
    } else {
        c.setTimes(1);
    }

    // find type:
    map<string,string> copy(comms);
    auto p = comms.begin();
    while (p != comms.end()) {
        string cmd = p->first;
        if (cmd.size() < s.size()) {
            copy.erase(cmd);
        } else if (cmd.size() == s.size()) {
            if (cmd != s) {
                copy.erase(cmd);
            }
        } else if (cmd.size() > s.size()) {
            if (cmd.substr(0,s.size()) != s) {
                copy.erase(cmd);
            }
        }
        ++p;
    }
    if (copy.size() != 1) {
        // invalid arg (either no match or too many matches)
        c.setTimes(0);
        c.setType("invalid");
        return c;
    } else {
        // valid arg
        string cmd = copy.begin()->first;
        c.setType(comms[cmd]);
        return c;
    }
}

Command Parser::sparse(string s) {
    Command c;
    // find type:
    map<string,string> copy(scomms);
    auto p = scomms.begin();
    while (p != scomms.end()) {
        string cmd = p->first;
        if (cmd.size() < s.size()) {
            copy.erase(cmd);
        } else if (cmd.size() == s.size()) {
            if (cmd != s) {
                copy.erase(cmd);
            }
        } else if (cmd.size() > s.size()) {
            if (cmd.substr(0,s.size()) != s) {
                copy.erase(cmd);
            }
        }
        ++p;
    }
    if (copy.size() != 1) {
        // invalid arg (either no match or too many matches)
        c.setTimes(0);
        c.setType("invalid");
        return c;
    } else {
        // valid arg
        string cmd = copy.begin()->first;
        c.setType(scomms[cmd]);
        return c;
    }
}

int Parser::getInt(string s) {
    istringstream iss{s};
    int n;
    iss >> n;
    return n;
}
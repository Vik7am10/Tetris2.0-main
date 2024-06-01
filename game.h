#ifndef GAME_H_
#define GAME_H_
#include <iostream>
#include <memory>
#include "parser.h"
#include "display.h"
#include "abstractboard.h"

enum Turn {P1, P2};

class Game {
    std::ostream &out;
    std::unique_ptr<DisplayAscii> da;
    std::unique_ptr<DisplayUI> du;
    bool textOnly;
    Parser p;
    Turn t;
    std::unique_ptr<AbstractBoard> b1;
    std::unique_ptr<AbstractBoard> b2;
    void notify(std::istream&);

    public:
    Game(std::ostream&);
    void play(std::istream&);
    void setTextOnly(bool);
    void setSeed(std::string);
    void setSFO(std::string);
    void setSFT(std::string);
    void setStartLevel(std::string);
};

#endif
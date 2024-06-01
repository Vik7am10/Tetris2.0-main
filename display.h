#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "window.h"
#include <memory>
#include <iostream>
#include "abstractboard.h"

class DisplayT {
    protected:
    const int BOX_WIDTH = 1000; // width of box
    const int BOX_HEIGHT = 1000; // height of box
    const int X_INDENT = 100; // x-indent (how much inwards from the left)
    const int Y_INDENT = 50; // y-indent (how much inwards from the top)
    const int LINE_SPACING = 20; // how much (up/down) lines are seperated by
    const int LINE_TAB = 200; // how much each Q/A is separated by IF A is blank
    const int SECOND = 500; // how much second board is left-offset from first board
    const int CHAR_SIZE = 5; // how large is one char?
    const int DIV_WIDTH = 275;
    const int DIV_HEIGHT = 5;
    const int CELL_SIZE = 25;
    public:
    virtual void draw(std::unique_ptr<AbstractBoard> &, std::unique_ptr<AbstractBoard> &) = 0;
    virtual ~DisplayT();
};

class DisplayAscii : public DisplayT {
    std::ostream &out;
    public:
    DisplayAscii(std::ostream &);
    virtual void draw(std::unique_ptr<AbstractBoard> &, std::unique_ptr<AbstractBoard> &) override;
};

class DisplayUI : public DisplayT {

    std::unique_ptr<Xwindow> wptr;
    public:
    DisplayUI();
    virtual void draw(std::unique_ptr<AbstractBoard> &, std::unique_ptr<AbstractBoard> &) override;

};


#endif
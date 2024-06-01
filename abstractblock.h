#ifndef ABSTRACTBLOCK_H_
#define ABSTRACTBLOCK_H_

#include "cell.h"
#include <vector>
#include <memory>
#include <string>

class Board;
class AbstractBlock {

    protected:
    int level;
    std::vector<std::shared_ptr<Cell>> block;
    Board* B;
    int x, y;
    bool Left();
    bool Right();
    void moveLeft();
    void moveRight();
    void moveDown();
    public:
        bool Down();
        AbstractBlock();
        // AbstractBlock(std::unique_ptr<Board> B): B{std::move(B)} {}
        virtual void move(std::string direction); 
        virtual void drop();
        virtual void rotate(int direction) = 0;

        virtual void setBoard(Board* b);
        virtual void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) = 0;

        virtual void removeRows(std::vector<int>);
        virtual bool isEmpty();
        virtual std::vector<std::shared_ptr<Cell>> getCells();
        virtual int getLevel();

        virtual void setX(int);
        virtual void setY(int);
        virtual int getX();
        virtual int getY();
        virtual ~AbstractBlock();
};

#endif


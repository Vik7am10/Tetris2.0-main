#ifndef DECORATORBLOCK_H_
#define DECORATORBLOCK_H_

#include "abstractblock.h"
#include "Board.h"

class DecoratorBlock: public AbstractBlock {
    protected:
        std::unique_ptr<AbstractBlock> component;
    public:
        DecoratorBlock(std::unique_ptr<AbstractBlock> b);
        virtual void move(std::string direction) override;
        virtual void drop() override;
        virtual void rotate(int direction) override;

        virtual void setBoard(Board* b) override;
        virtual void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;

        virtual void removeRows(std::vector<int>) override;
        virtual bool isEmpty() override;
        virtual std::vector<std::shared_ptr<Cell>> getCells() override;
        virtual int getLevel() override;

        virtual void setX(int) override;
        virtual void setY(int) override;
        virtual int getX() override;
        virtual int getY() override;
        virtual ~DecoratorBlock();
};

#endif
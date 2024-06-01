#ifndef MIDDLEBLOCK_H_
#define MIDDLEBLOCK_H_

#include "abstractblock.h"

class MiddleBlock : public AbstractBlock {
    char orientation;
public:
    MiddleBlock();
    void setBoard(Board*) override;
    void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
    void rotate(int direction) override;
};

#endif
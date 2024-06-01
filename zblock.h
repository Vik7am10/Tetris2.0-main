#ifndef ZBLOCK_H_
#define ZBLOCK_H_

#include "abstractblock.h"
class Board;

class ZBlock: public AbstractBlock {
    char orientation;
    bool canRotate() const;
    public:
        ZBlock();
        void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
        void rotate(int direction) override;
};

#endif

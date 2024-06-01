#ifndef IBLOCK_H_
#define IBLOCK_H_

#include "abstractblock.h"
#include "Board.h"

class IBlock: public AbstractBlock {
    char orientation;
    bool canRotate() const;
    public:
        IBlock();
        void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
        void rotate(int direction) override;
};

#endif

#ifndef SBLOCK_H_
#define SBLOCK_H_

#include "abstractblock.h"

class SBlock: public AbstractBlock {
    char orientation;
    bool canRotate() const;
    public:
        SBlock();
        void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
        void rotate(int direction) override;
};

#endif

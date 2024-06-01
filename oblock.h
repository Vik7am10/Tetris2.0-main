#ifndef OBLOCK_H_
#define OBLOCK_H_

#include "abstractblock.h"

class OBlock: public AbstractBlock {
    char orientation;
    public:
        OBlock();
        void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
        void rotate(int direction) override;
};

#endif
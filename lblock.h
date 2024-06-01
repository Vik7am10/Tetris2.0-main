#ifndef LBLOCK_H_
#define LBLOCK_H_

#include "abstractblock.h"

class LBlock: public AbstractBlock {
    char orientation;
    void rotateHorizontal(int direction);
    void rotateL(int direction);
    void rotateR(int direction);
    void rotateUpside(int direction);
    bool canRotate() const;
    public:
        LBlock();
        void changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) override;
        void rotate(int direction) override;
};

#endif

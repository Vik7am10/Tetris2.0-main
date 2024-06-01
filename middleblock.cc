#include "middleblock.h"
#include "Board.h"

MiddleBlock::MiddleBlock() { }

void MiddleBlock::setBoard(Board* b) {
    B = b;
    level = b->getLevel();
    changeCells(b->getGrid());
}

void MiddleBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
   /* for (int i = 0; i < 2; i++) {
        block.emplace_back(B->getCell(i, 14));
        block.at(i)->setType('o');
    }
    for (int i = 0; i < 2; i++) {
        block.emplace_back(B->getCell(i, 13));
        block.at(i + 2)->setType('o');
    } */
}

void MiddleBlock::rotate(int direction) { return; }
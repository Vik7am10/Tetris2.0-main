#include "oblock.h"
#include "Board.h"

OBlock::OBlock() { }

void OBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[4][i]);//B->getCell(i, 4));
        block.at(i)->setType('o');
    }
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[3][i]);//B->getCell(i, 3));
        block.at(i + 2)->setType('o');
    }
}

void OBlock::rotate(int direction) {return;}
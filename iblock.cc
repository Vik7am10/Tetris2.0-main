#include "iblock.h"
#include "Board.h"

IBlock::IBlock() {}

void IBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    for (int i = 0; i < 4; i++) {
        block.emplace_back(cells[3][i]);
        block.at(i)->setType('i');
    }
}

bool IBlock::canRotate() const {
    int x = block.at(0)->getX();
    int y = block.at(0)->getY();
    if (orientation == 'h') {
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 4; i++) {
                if (B->getCell(x + i, y -  1 - j)->getType() != 'n') return false;
            }
        }
    } else {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 3; i++) {
                if (B->getCell(x + 1 + i, y - j)->getType() != 'n') return false;
            }
        }
    }
}

void IBlock::rotate(int direction) {
    int x = block.at(0)->getX();
    int y = block.at(0)->getY();
    if (orientation == 'h') {
            for (int i = 0; i < 4; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x, y - i)->setType('i');
                block.emplace_back(B->getCell(x, y - i));
            }
            orientation = 'l';
    } else {
         for (int i = 0; i < 4; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + i, y)->setType('i');
                block.emplace_back(B->getCell(x + i,y));
         }
         orientation = 'h';
    }
}

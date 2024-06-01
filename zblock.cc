#include "zblock.h"
#include "Board.h"

ZBlock::ZBlock() {}

void ZBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[2][i]);//B->getCell(i, 2));
        block.at(i)->setType('z');
    }
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[3][i + 1]);//B->getCell(i + 1, 3));
        block.at(i + 2)->setType('z');
    }
}

bool ZBlock::canRotate() const {
    int x = block.at(0)->getX();
    int y = block.at(0)->getY();
    if (orientation == 'h') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + i, y - 1)->getType() != 'n') return false;
        }
        if (B->getCell(x + 2, y)->getType() != 'n') return false;
        if (B->getCell(x, y + 1)->getType() != 'n') return false;
    } else {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 1, y + i)->getType() != 'n') return false;
        }
        if (B->getCell(x, y + 2)->getType() != 'n') return false;
        if (B->getCell(x - 1, y)->getType() != 'n') return false;
    }    
}

void ZBlock::rotate(int direction) {  
    if (!canRotate()) return;  
    if (orientation == 'h') {
        block.at(0)->setType('n');
        int x = block.at(0)->getX();
        int y = block.at(0)->getY();
        char t = 'z';
        block.erase(block.begin());
        B->getCell(x + 1, y - 1)->setType(t);
        block.emplace_back(B->getCell(x + 1, y - 1));  
        for (int i = 0; i < 2; i++) {
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x +  1 - i, y)->setType(t);
            block.emplace_back(B->getCell(x + 1 - i,y));    //(x+1,y) to (x,y)
        }
        block.at(0)->setType('n');
        block.erase(block.begin());
        B->getCell(x, y + 1)->setType(t);
        block.emplace_back(B->getCell(x, y + 1));
        orientation = 'l';
    } else {
        block.at(3)->setType('n');
        int x = block.at(3)->getX();
        int y = block.at(3)->getY();
        char t = 'z';
        block.pop_back();
        B->getCell(x + 2, y)->setType(t);
        block.emplace_back(B->getCell(x + 2, y));  
        for (int i = 0; i < 2; i++) {
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y - i)->setType(t);
            block.emplace_back(B->getCell(x + 1, y - i));  // (x+1,y) to (x+1,y+1)  
        }
        block.at(0)->setType('n');
        block.erase(block.begin());
        B->getCell(x, y - 1)->setType(t);
        block.emplace_back(B->getCell(x, y - 1));
        orientation = 'h';
    }
}

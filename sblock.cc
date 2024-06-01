#include "sblock.h"
#include "Board.h"

SBlock::SBlock() {};

void SBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[3][i]);//B->getCell(i, 3));
        block.at(i)->setType('s');
    }
    for (int i = 0; i < 2; i++) {
        block.emplace_back(cells[2][i + 1]);//B->getCell(i + 1, 2));
        block.at(i + 2)->setType('s');
    }
}

bool SBlock::canRotate() const {
    int x = block.at(0)->getX();
    int y = block.at(0)->getY();
    if (orientation == 'h') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + i, y - 2)->getType() != 'n') return false;
        }
        if (B->getCell(x + 2, y)->getType() != 'n') return false;
        if (B->getCell(x, y - 1)->getType() != 'n') return false;
    } else {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 2, y + i)->getType() != 'n') return false;
        }
        if (B->getCell(x + 1, y)->getType() != 'n') return false;
        if (B->getCell(x, y + 2)->getType() != 'n') return false;
    }
}

void SBlock::rotate(int direction) {
    if(!canRotate()) return;
    if (orientation == 'h') {
        block.at(0)->setType('n');
        int x = block.at(0)->getX();
        int y = block.at(0)->getY();
        block.erase(block.begin());
        B->getCell(x, y - 2)->setType('s');
        block.emplace_back(B->getCell(x, y - 2));  
        for (int i = 0; i < 2; i++) {
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + i, y - 1)->setType('s');
            block.emplace_back(B->getCell(x + i,y - 1));    
        }
        block.at(0)->setType('n');
        block.erase(block.begin());
        B->getCell(x + 1, y)->setType('s');
        block.emplace_back(B->getCell(x + 1, y));
        orientation = 'l';
    } else {
        block.at(3)->setType('n');
        int x = block.at(3)->getX();
        int y = block.at(3)->getY();
        block.pop_back();
        B->getCell(x + 1, y - 1)->setType('s');
        block.insert(block.begin(), B->getCell(x + 1, y - 1)); // 
        for (int i = 0; i < 2; i++) {
            block.at(3)->setType('n');
            block.pop_back();
            B->getCell(x, y - 1 + i)->setType('s');
            block.insert(block.begin(),B->getCell(x, y - 1 + i));    
        }  
        block.at(3)->setType('n');
        block.pop_back();
        B->getCell(x - 1, y)->setType('s');
        block.insert(block.begin(), B->getCell(x - 1, y)); //
        orientation = 'h';
    }
}

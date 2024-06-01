#include "tblock.h"
#include "Board.h"

TBlock::TBlock() { }

void TBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    for (int i = 0; i < 3; i++) {
        block.emplace_back(cells[2][i]);//B->getCell(i, 2));
        block.at(i)->setType('t');
    }
    block.emplace_back(cells[3][1]);//B->getCell(1, 3));
    block.at(3)->setType('t');
}

bool TBlock::canRotate() const{
   int x = block.at(0)->getX();
   int y = block.at(0)->getY(); 
   if (orientation == 'h') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + i, y - 1)->getType() != 'n') return false;
        }
        if (B->getCell(x + 2, y + 1)->getType() != 'n') return false;
        if (B->getCell(x, y + 1)->getType() != 'n') return false;
   } else if (orientation == 'u') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x - i, y - 2)->getType() != 'n') return false;
        }
        if (B->getCell(x, y - 1)->getType() != 'n') return false;
        if (B->getCell(x - 2, y - 1)->getType() != 'n') return false;
   } else if (orientation == 'r') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 2, y - i)->getType() != 'n') return false;
        }
        if (B->getCell(x + 1, y - 2)->getType() != 'n') return false;
        if (B->getCell(x + 1, y)->getType() != 'n') return false;
   } else {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 1, y + i)->getType() != 'n') return false;
        }
        if (B->getCell(x - 1, y)->getType() != 'n') return false;
        if (B->getCell(x - 1, y + 2)->getType() != 'n') return false;
   }
}

void TBlock::rotateHorizontal(int direction) {
        if (!canRotate()) return;
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x, y + 1 - i)->setType(t); // (x , y - 1) to (x , y + 1)
                block.emplace_back(B->getCell(x, y + 1 - i));
            }
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y)->setType(t);
            block.emplace_back(B->getCell(x + 1, y));
            orientation = 'r';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            block.at(3)->setType('n');
            block.pop_back();
            for (int i = 0; i < 3; i++) {
                block.at(2)->setType('n');
                block.pop_back();
                B->getCell(x, y - i)->setType(t); //(x - 1, y + 2) to (x - 1, y)
                block.insert(block.begin(),B->getCell(x, y - i));
            }
            B->getCell(x - 1, y - 1)->setType(t);
            block.emplace_back(B->getCell(x - 1, y - 1));
            orientation = 'l';
        }
}

void TBlock::rotateR(int direction) {
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + 2 - i, y)->setType(t);
                block.emplace_back(B->getCell(x + 2 - i, y)); // (x + 2, y) to (x, y)
            }
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y - 1)->setType(t);
            block.emplace_back(B->getCell(x + 1, y - 1));
            orientation = 'u';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            B->getCell(x, y + 1)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x, y + 1));
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x - 1 + i, y)->setType(t);
                block.insert(block.begin(),B->getCell(x - 1 + i ,y));
            }
            orientation = 'h';
        }
}

void TBlock::rotateL(int direction) {
        if (direction == 'c') {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            block.at(3)->setType('n');
            block.pop_back();
            for (int i = 0; i < 3; i++) {
                block.at(2)->setType('n');
                block.pop_back();
                B->getCell(x + i, y + 1)->setType(t);
                block.insert(block.begin(), B->getCell(x + i, y + 1)); // (x + 1, y - 2) to (x - 1, y - 2)
            }
            B->getCell(x + 1, y)->setType(t);
            block.emplace_back(B->getCell(x + 1, y));
            orientation = 'u';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            block.at(3)->setType('n');
            block.pop_back();
            for (int i = 2; i >= 0; i--) {
                block.at(2)->setType('n');
                block.pop_back();
                B->getCell(x + i, y)->setType(t);
                block.insert(block.begin(),B->getCell(x + i ,y)); // (x,y) to (x + 2, y)
            }
            B->getCell(x + 1, y + 1)->setType(t);
            block.emplace_back(B->getCell(x + 1, y + 1));
            orientation = 'h';
        }
}

void TBlock::rotateUpside(int direction) {
        if (direction == 'a') {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            B->getCell(x - 1, y)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x - 1, y));
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x, y - i + 1)->setType(t);
                block.insert(block.begin(),B->getCell(x ,y - i + 1)); // (x, y + 1) to (x, y - 1)
            }
            orientation = 'l';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(2)->setType('n');
                block.erase(block.begin() + 2);
                B->getCell(x - 1, y + i - 1)->setType(t);
                block.insert(block.begin(),B->getCell(x - 1 ,y + i - 1)); // (x - 1, y + 1) to (x - 1, y - 1)
            }
            orientation = 'r';
        }
}

void TBlock::rotate(int direction) {
    if (orientation == 'h') rotateHorizontal(direction); 
    else if (orientation == 'r') rotateR(direction);
    else if (orientation == 'u') rotateUpside(direction);
    else rotateL(direction); 
}

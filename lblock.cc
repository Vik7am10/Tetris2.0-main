#include "lblock.h"
#include "Board.h"


LBlock::LBlock() {}

void LBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    block.emplace_back(cells[2][2]); // B->getCell(2, 2));
    block.at(0)->setType('l');
    for (int i = 0; i < 3; i++) {
        block.emplace_back(cells[3][i]); //B->getCell(i, 3));
        block.at(i + 1)->setType('l');
    }
}

bool LBlock::canRotate() const {
   int x = block.at(0)->getX();
   int y = block.at(0)->getY(); 
   if (orientation == 'h') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x - i, y - 1)->getType() != 'n') return false;
        }
        if (B->getCell(x - 2, y)->getType() != 'n') return false;
        if (B->getCell(x - 1, y)->getType() != 'n') return false;
   } else if (orientation == 'u') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + i, y - 2)->getType() != 'n') return false;
        }
        if (B->getCell(x + 1, y)->getType() != 'n') return false;
        if (B->getCell(x + 2, y)->getType() != 'n') return false;
   } else if (orientation == 'r') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 2, y + i)->getType() != 'n') return false;
        }
        if (B->getCell(x, y + 2)->getType() != 'n') return false;
        if (B->getCell(x, y + 1)->getType() != 'n') return false;
   } else {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 1, y - i)->getType() != 'n') return false;
        }
        if (B->getCell(x, y - 1)->getType() != 'n') return false;
        if (B->getCell(x, y - 2)->getType() != 'n') return false;
   }
}

void LBlock::rotateHorizontal(int direction) {
        if (!canRotate()) return;
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x - 2, y - 1)->setType(t);
            block.emplace_back(B->getCell(x - 2, y - 1));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x - 1, y - 1 + i)->setType(t);
                block.emplace_back(B->getCell(x - 1 ,y - 1 + i));
            }
            orientation = 'r';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x, y - i)->setType(t);
                block.insert(block.begin(),B->getCell(x, y - i));
            }
            B->getCell(x + 1, y)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x + 1, y));
            orientation = 'l';
        }
}

void LBlock::rotateR(int direction) {
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x , y + 2)->setType(t);
            block.emplace_back(B->getCell(x, y + 2));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + i, y + 1)->setType(t);
                block.emplace_back(B->getCell(x + i,y + 1));
            }
            orientation = 'u';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x + 1 - i, y)->setType(t);
                block.insert(block.begin(),B->getCell(x + 1 - i ,y));
            }
            B->getCell(x + 1, y - 1)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x + 1, y - 1));
            orientation = 'h';
        }
}

void LBlock::rotateL(int direction) {
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y - 1)->setType(t);
            block.emplace_back(B->getCell(x + 1, y - 1));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + 1 - i, y)->setType(t);
                block.emplace_back(B->getCell(x + 1 - i, y));
            }
            orientation = 'h';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x + i, y + 1)->setType(t);
                block.insert(block.begin(),B->getCell(x + i ,y + 1));
            }
            B->getCell(x, y + 2)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x, y + 2));
            orientation = 'u';
        }
}

void LBlock::rotateUpside(int direction) {
        if (direction == 'a') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y)->setType(t);
            block.emplace_back(B->getCell(x + 1, y));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x, y - i)->setType(t);
                block.emplace_back(B->getCell(x, y - i));
            }
            orientation = 'l';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x - 1, y - 1 + i)->setType(t);
                block.insert(block.begin(),B->getCell(x - 1 ,y - 1 + i));
            }
            B->getCell(x - 2, y - 1)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x - 2 , y - 1));
            orientation = 'r';
        }
}

void LBlock::rotate(int direction) {
    if (orientation == 'h') rotateHorizontal(direction); 
    else if (orientation == 'r') rotateR(direction);
    else if (orientation == 'u') rotateUpside(direction);
    else rotateL(direction);         
} 

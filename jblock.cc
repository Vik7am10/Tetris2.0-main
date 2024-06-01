#include "jblock.h"
#include "Board.h"

JBlock::JBlock() {}

void JBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
    block.emplace_back(cells[2][0]);
    block.at(0)->setType('j');
    for (int i = 0; i < 3; i++) {
        block.emplace_back(cells[3][i]); // B->getCell(i, 3));
        block.at(i + 1)->setType('j');
    }
}

bool JBlock::canRotate() const {
   int x = block.at(0)->getX();
   int y = block.at(0)->getY(); 
   if (orientation == 'h') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + i, y - 1)->getType() != 'n') return false;
        }
        if (B->getCell(x + 2, y)->getType() != 'n') return false;
        if (B->getCell(x + 1, y)->getType() != 'n') return false;
   } else if (orientation == 'u') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x - i, y - 2)->getType() != 'n') return false;
        }
        if (B->getCell(x - 1, y)->getType() != 'n') return false;
        if (B->getCell(x - 2, y)->getType() != 'n') return false;
   } else if (orientation == 'r') {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 1, y + i)->getType() != 'n') return false;
        }
        if (B->getCell(x, y + 1)->getType() != 'n') return false;
        if (B->getCell(x, y + 2)->getType() != 'n') return false;
   } else {
        for (int i = 0; i < 3; i++) {
            if (B->getCell(x + 2, y - i)->getType() != 'n') return false;
        }
        if (B->getCell(x, y - 1)->getType() != 'n') return false;
        if (B->getCell(x, y - 2)->getType() != 'n') return false;
   }
}

void JBlock::rotateHorizontal(int direction) {
        if (direction == 'c') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y - 1)->setType(t);
            block.emplace_back(B->getCell(x + 1,y - 1));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x, y - 1 + i)->setType(t);
                block.emplace_back(B->getCell(x, y - 1 + i));
            }
            orientation = 'r';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x - 1, y - i)->setType(t);
                block.insert(block.begin(),B->getCell(x - 1 ,y - i));
            }
            B->getCell(x - 2, y)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x - 2, y));
            orientation = 'l';
        }
}

void JBlock::rotateR(int direction) {
        if (direction == 'c') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x + 1, y + 2)->setType(t);
            block.emplace_back(B->getCell(x + 1,y + 2));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + 1 - i, y + 1)->setType(t);
                block.emplace_back(B->getCell(x + 1 - i,y + 1));
            }
            orientation = 'u';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x + i, y)->setType(t);
                block.insert(block.begin(),B->getCell(x + i ,y));
            }
            B->getCell(x, y - 1)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x, y - 1));
            orientation = 'h';
        }
}

void JBlock::rotateL(int direction) {
        if (direction == 'c') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x, y - 1)->setType(t);
            block.emplace_back(B->getCell(x, y - 1));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x + i, y)->setType(t);
                block.emplace_back(B->getCell(x + i,y));
            }
            orientation = 'h';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x + 1 - i, y + 1)->setType(t);
                block.insert(block.begin(),B->getCell(x + 1 - i ,y + 1));
            }
            B->getCell(x + 1, y + 2)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x + 1, y + 2));
            orientation = 'u';
        }
}

void JBlock::rotateUpside(int direction) {
        if (direction == 'c') {
            int x = block.at(0)->getX();
            int y = block.at(0)->getY();
            char t = block.at(0)->getType();
            block.at(0)->setType('n');
            block.erase(block.begin());
            B->getCell(x - 2, y)->setType(t);
            block.emplace_back(B->getCell(x - 2,y));
            for (int i = 0; i < 3; i++) {
                block.at(0)->setType('n');
                block.erase(block.begin());
                B->getCell(x - 1, y - i)->setType(t);
                block.emplace_back(B->getCell(x - 1,y - i));
            }
            orientation = 'l';
        } else {
            int x = block.at(3)->getX();
            int y = block.at(3)->getY();
            char t = block.at(3)->getType();
            for (int i = 2; i >= 0; i--) {
                block.at(3)->setType('n');
                block.pop_back();
                B->getCell(x, y - 1 + i)->setType(t);
                block.insert(block.begin(),B->getCell(x ,y - 1 + i));
            }
            B->getCell(x + 1, y - 1)->setType(t);
            block.at(3)->setType('n');
            block.pop_back();
            block.insert(block.begin(), B->getCell(x + 1, y - 1));
            orientation = 'r';
        }
}

void JBlock::rotate(int direction) {
    if (orientation == 'h') rotateHorizontal(direction); 
    else if (orientation == 'r') rotateR(direction);
    else if (orientation == 'u') rotateUpside(direction);
    else rotateL(direction); 
        
}

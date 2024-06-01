#include "abstractblock.h"
#include "Board.h"

AbstractBlock::AbstractBlock(){}

AbstractBlock::~AbstractBlock(){}

void AbstractBlock::setBoard(Board* b) {
    this->B = b;
    level = b->getLevel();
    block.clear();
    changeCells(b->getGrid());
}

bool checkIn(int elem, std::vector<int> vec) {
    for (auto next : vec) {
        if (next == elem) {
            return true;
        }
    }
    return false;
}

void AbstractBlock::removeRows(std::vector<int> rows) {
    for (auto iter = block.begin(); iter != block.end();) {
        if (checkIn((*iter)->getY(), rows)) {
            (*iter)->setType('n');
            iter = block.erase(iter);
        }
        else {
            iter++;
        }
    }
}

bool AbstractBlock::isEmpty() { return block.size() == 0; }

std::vector<std::shared_ptr<Cell>> AbstractBlock::getCells() {
    return block;
}

int AbstractBlock::getLevel() {
    return level;
}

int AbstractBlock::getX() {
    return x;
}

int AbstractBlock::getY() {
    return y;
}

void AbstractBlock::setX(int x) {
    int least = 14;
    for (auto v:block) {
        int i = v->getX();
        if (i < least) least = i;
    }
    x = least;
}

void AbstractBlock::setY(int y) {
    int highest = 17;
    for (auto v:block) {
        int i = v->getY();
        if (i > highest) highest = i;
    }
    y = highest;
}


bool AbstractBlock::Left() {
    for (auto v:block) { 
        int l = v->getX();
        if (l == 0) return false;
        int h = v->getY();
        char t = B->getCell(l-1,h)->getType();
        int x1 = B->getCell(l-1,h)->getX();
        int y1 = B->getCell(l-1,h)->getY();
        bool inblock = false;
        for (auto r:block) if (x1 == r->getX() && y1 == r->getY()) inblock = true;
        bool flag1 = false;
        if(t != 'n' && t != v->getType()) flag1 = true;
        bool flag2 = false;
        if(!inblock && t == v->getType()) flag2 = true;
        if (flag2 || flag1) return false;
    }
    return true;
}

bool AbstractBlock::Right() {
      for (auto v:block) { // need to define getCell in Block class
        int l = v->getX();
        if (l >= 10) return false; //check correct row end
        int h = v->getY();
        char t = B->getCell(l+1,h)->getType();
        int x1 = B->getCell(l+1,h)->getX();
        int y1 = B->getCell(l+1,h)->getY();
        bool inblock = false;
        for (auto r:block) if (x1 == r->getX() && y1 == r->getY()) inblock = true;
        bool flag1 = false;
        if(t != 'n' && t != v->getType()) flag1 = true;
        bool flag2 = false;
        if(!inblock && t == v->getType()) flag2 = true;
        if (flag2 || flag1) return false;
    }
    return true;
}

bool AbstractBlock::Down() {
      for (auto v:block) { // need to define getCell in Block class
        int h = v->getY();
        if (h >= 14) return false;
        int l = v->getX();
        char t = B->getCell(l,h+1)->getType();
        int x1 = B->getCell(l,h+1)->getX();
        int y1 = B->getCell(l,h+1)->getY();
        bool inblock = false;
        for (auto r:block) if (x1 == r->getX() && y1 == r->getY()) inblock = true;
        bool flag1 = false;
        if(t != 'n' && t != v->getType()) flag1 = true;
        bool flag2 = false;
        if(!inblock && t == v->getType()) flag2 = true;
        if (flag2 || flag1) return false;
    }
    return true;
}

void AbstractBlock::moveLeft() {
    if (!Left()) return;
    char t = block.at(3)->getType();
    int x4 = block.at(3)->getX() - 1;
    int y4 = block.at(3)->getY();
    block.at(3)->setType('n');
    int x3 = block.at(2)->getX() - 1;
    int y3 = block.at(2)->getY();
    block.at(2)->setType('n');
    int x2 = block.at(1)->getX() - 1;
    int y2 = block.at(1)->getY();
    block.at(1)->setType('n');
    int x1 = block.at(0)->getX() - 1;
    int y1 = block.at(0)->getY();
    block.at(0)->setType('n');
    block.pop_back();
    block.pop_back();
    block.pop_back();
    block.pop_back();
    B->getCell(x1,y1)->setType(t);
    B->getCell(x2,y2)->setType(t);
    B->getCell(x3,y3)->setType(t);
    B->getCell(x4,y4)->setType(t);
    block.emplace_back(B->getCell(x1,y1));
    block.emplace_back(B->getCell(x2,y2));
    block.emplace_back(B->getCell(x3,y3));
    block.emplace_back(B->getCell(x4,y4));
}

void AbstractBlock::moveRight() {
    if (!Right()) return;
    char t = block.at(3)->getType();
    int x4 = block.at(3)->getX() + 1;
    int y4 = block.at(3)->getY();
    block.at(3)->setType('n');
    int x3 = block.at(2)->getX() + 1;
    int y3 = block.at(2)->getY();
    block.at(2)->setType('n');
    int x2 = block.at(1)->getX() + 1;
    int y2 = block.at(1)->getY();
    block.at(1)->setType('n');
    int x1 = block.at(0)->getX() + 1;
    int y1 = block.at(0)->getY();
    block.at(0)->setType('n');
    block.pop_back();
    block.pop_back();
    block.pop_back();
    block.pop_back();
    B->getCell(x1,y1)->setType(t);
    B->getCell(x2,y2)->setType(t);
    B->getCell(x3,y3)->setType(t);
    B->getCell(x4,y4)->setType(t);
    block.emplace_back(B->getCell(x1,y1));
    block.emplace_back(B->getCell(x2,y2));
    block.emplace_back(B->getCell(x3,y3));
    block.emplace_back(B->getCell(x4,y4));
}

void AbstractBlock::moveDown() {
    if (!Down()) return;
    std::vector<std::shared_ptr<Cell>> new_block;
    for (auto& a_block : block) {
        new_block.emplace_back(B->getCell(a_block->getX(), a_block->getY() + 1));
        new_block[new_block.size()-1]->setType(a_block->getType());
    }
    for (auto& a_block : block) {
        bool is_in = false;
        for (auto& b_block : new_block) {
            if (a_block->getX() == b_block->getX() && a_block->getY() == b_block->getY()) {
                is_in = true;
                break;
            }
        }
        if (!is_in) {
            a_block->setType('n');
        }
    }
    block = new_block;
    /*
    char t = block.at(3)->getType();
    int x4 = block.at(3)->getX();
    int y4 = block.at(3)->getY() + 1;
    block.at(3)->setType('n');
    int x3 = block.at(2)->getX();
    int y3 = block.at(2)->getY() + 1;
    block.at(2)->setType('n');
    int x2 = block.at(1)->getX();
    int y2 = block.at(1)->getY() + 1;
    block.at(1)->setType('n');
    int x1 = block.at(0)->getX();
    int y1 = block.at(0)->getY() + 1;
    block.at(0)->setType('n');
    block.pop_back();
    block.pop_back();
    block.pop_back();
    block.pop_back();
    B->getCell(x1,y1)->setType(t);
    B->getCell(x2,y2)->setType(t);
    B->getCell(x3,y3)->setType(t);
    B->getCell(x4,y4)->setType(t);
    block.emplace_back(B->getCell(x1,y1));
    block.emplace_back(B->getCell(x2,y2));
    block.emplace_back(B->getCell(x3,y3));
    block.emplace_back(B->getCell(x4,y4)); */
}

void AbstractBlock::move(std::string direction) {
    if (direction == "left") moveLeft();
    else if (direction == "right") moveRight();
    else if (direction == "down") moveDown();
    else if (direction == "drop") drop();
    else if (direction == "clockwise") rotate('c');
    else if (direction == "counterclockwise") rotate('a');
}

void AbstractBlock::drop() {
    while(Down()) moveDown();
}

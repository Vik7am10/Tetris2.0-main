#include "cell.h"

Cell::Cell(int x, int y, char type): x{x},y{y},type{type} {}

int Cell::getX() const { return x;}

int Cell::getY() const { return y;}

char Cell::getType() const {return type;}

void Cell::setType(char t) {type = t;}

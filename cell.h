#ifndef CELL_H_
#define CELL_H_

class Cell {
    int x,y;
    char type;
    public:
        Cell(int x, int y, char type = 'n');
        int getX() const;
        int getY() const;
        char getType() const;
        void setType(char t);
};

#endif

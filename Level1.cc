//#include "Level0.h"
#include "Level1.h"
#include "Level2.h"

Level1::Level1() : Level{ { {'S', 1}, {'Z', 1},
	{'L', 2 }, { 'I', 2 }, { 'J', 2 }, { 'O', 2 }, { 'T', 2 } } } { };

std::unique_ptr<Level> Level1::getNextLevel() const {
	return std::make_unique<Level2>();
}

std::unique_ptr<Level> Level1::getPrevLevel() const {
	return std::make_unique<Level1>(); //Level0();
}

int Level1::getLevel() const {
	return 1;
}



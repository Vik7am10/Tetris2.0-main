#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

Level2::Level2() : Level{ { {'S', 1}, {'Z', 1},
		{'L', 1}, { 'I', 1 }, { 'J', 1 }, { 'O', 1 }, { 'T', 1 } } } {};

std::unique_ptr<Level> Level2::getNextLevel() const {
	return std::make_unique<Level3>();
}

std::unique_ptr<Level> Level2::getPrevLevel() const {
	return std::make_unique<Level1>();
}

int Level2::getLevel() const {
	return 2;
}






#include "Level0.h"
#include "Level1.h"
#include <fstream>


Level0::Level0() {
	is_random = false;
}

void Level0::setRandom(bool random) {
	is_random = false;
}

std::unique_ptr<Level> Level0::getNextLevel() const {
	return std::make_unique<Level1>();
}

std::unique_ptr<Level> Level0::getPrevLevel() const {
	return std::make_unique<Level1>();
}

int Level0::getLevel() const {
	return 0;
}

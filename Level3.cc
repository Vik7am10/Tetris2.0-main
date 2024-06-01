#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

Level3::Level3() : Level{ { {'S', 2}, {'Z', 2},
		{'L', 1}, { 'I', 1 }, { 'J', 1 }, { 'O', 1 }, { 'T', 1 } } } {};

void Level3::move(AbstractBlock* currentBlock, std::string command) {
	heavyMove(currentBlock, command);
}

std::unique_ptr<Level> Level3::getNextLevel() const {
	return std::make_unique<Level4>();
}

std::unique_ptr<Level> Level3::getPrevLevel() const {
	return std::make_unique<Level2>();
}

int Level3::getLevel() const {
	return 3;
}


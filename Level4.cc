#include "Level3.h"
#include "Level4.h"
#include "middleblock.h"

Level4::Level4() : Level{ { {'S', 2}, {'Z', 2},
		{'L', 1}, { 'I', 1 }, { 'J', 1 }, { 'O', 1 }, { 'T', 1 } } } {};

void Level4::move(AbstractBlock* block, std::string command) {
	heavyMove(block, command);
	if (command == "drop") {
		block_count += 1;
		if (block_count % 5 == 0) {
			//addMiddleBlock();
		}
	}
}

std::unique_ptr<Level> Level4::getNextLevel() const {
	return std::make_unique<Level4>();
}

std::unique_ptr<Level> Level4::getPrevLevel() const {
	return std::make_unique<Level3>();
}

int Level4::getLevel() const {
	return 4;
}






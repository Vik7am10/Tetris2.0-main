#include "Level.h"
#include "abstractblock.h"
#include <iostream>
#include "sblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "iblock.h"
#include "tblock.h"
#include "zblock.h"

Level::Level() { }

Level::~Level() { } //delete block_file;}

Level::Level(std::map<char, int> weights) : curr_weights{ weights }, block_count{ 0 }, is_random{ true }, weight_sum{ 0 } {
	for (auto iter = weights.begin(); iter != weights.end(); iter++) {
		weight_sum += iter->second;
	}
}

void Level::updateBlockCount(bool cleared_row) {
	if (cleared_row) {
		block_count = 0;
	}
	else {
		block_count++;
	}
}

void Level::setFile(std::unique_ptr<std::ifstream> new_stream) {
	block_file = std::move(new_stream);
}

char Level::getTypeFromFile() const {
	char next_block;
	
	*block_file >> next_block;
	if (block_file->fail()) {
		// throw an exception
	}
	if (block_file->eof()) {
		block_file->clear();
		block_file->seekg(0, std::ios::beg);
		return getTypeFromFile();
	}
	return next_block;
}

void Level::move(AbstractBlock* currentBlock, std::string command) {	
	if (!currentBlock) {
		return;
	}
	currentBlock->move(command);
	//currentBlock->move("down");
}


void Level::heavyMove(AbstractBlock* currentBlock, std::string command) {
	if (!currentBlock) {
		return;
	}
	currentBlock->move(command);
	if (command == "left" || command == "right") {
		currentBlock->move("down");
		currentBlock->move("down");
	}
	
}

std::unique_ptr<Level> Level::getNextLevel() const {
	return std::make_unique<Level>();
}

std::unique_ptr<Level> Level::getPrevLevel() const {
	return std::make_unique<Level>();
}

int Level::getLevel() const {
	return 0;
}

int Level::getRandom() const {
	return (std::rand() % (weight_sum + 1));
}

char Level::sampleType() const {
	auto r = getRandom();
	char type = ' ';
	for (auto iter = curr_weights.begin(); iter != curr_weights.end(); iter++) {
		auto curr_weight = iter->second;
		auto curr_type = iter->first;
		if (r <= curr_weight) {
			type = curr_type;
			break;
		}
		r -= curr_weight;
	}
	return type;
}

std::unique_ptr<AbstractBlock> Level::createBlock(char type) const {
	switch (type) {
	case 'S':
		return std::make_unique<SBlock>();
		break;
	case 'Z':
		return std::make_unique<ZBlock>();
		break;
	case 'L':
		return std::make_unique<LBlock>();
		break;
	case 'I':
		return std::make_unique<IBlock>();
		break;
	case 'J':
		return std::make_unique<JBlock>();
		break;
	case 'O':
		return std::make_unique<OBlock>();
		break;
	case 'T':
		return std::make_unique<TBlock>();
		break;
	default:
		// throw exception
		return nullptr;
	}
}

std::unique_ptr<AbstractBlock> Level::getNextBlock() const {
	const auto type = is_random ? sampleType() : getTypeFromFile();
	auto block = createBlock(type);
	return block;
}


void Level::setRandom(bool random) {
	is_random = random;
}
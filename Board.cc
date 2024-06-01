#include "Board.h"
#include "cell.h"
#include "Level.h"
#include <cmath>


Board::Board(std::unique_ptr<Level> level) : level{ std::move(level) }, score{ 0 }, high_score{ 0 }, game_over{ false } {
	for (int i = 0; i < N_ROWS; i++) {
		std::vector<std::shared_ptr<Cell>> cell_row;
		for (int j = 0; j < N_COLS; j++) {
			cell_row.push_back(std::make_shared<Cell>(j, i));
		}
		cells.push_back(cell_row);
	}

	for (int i = 0; i < MAX_BLOCK_HEIGHT; i++) {
		std::vector<std::shared_ptr<Cell>> cell_row;
		for (int j = 0; j < MAX_BLOCK_HEIGHT; j++) {
			cell_row.push_back(std::make_shared<Cell>(j, i));
		}
		display_cells.push_back(cell_row);
	}

	auto block = getNextBlock();//this->level->getNextBlock();
	//block->setBoard(this);
	nextBlock = std::move(block);
	changeCurrentBlock();
}

bool Board::move(std::string command) {
	level->move(currentBlock.get(), command);
	if (command == "drop") {
		return drop();
	}
	else {
		return false;
	}
}

bool Board::heavyMove(std::string command) {
	level->move(currentBlock.get(), command);
	if (command == "left" || command == "right") {
		level->move(currentBlock.get(), "down");
		level->move(currentBlock.get(), "down");
	}
	if (command == "drop") {
		return drop();
	}
	else {
		return false;
	}
}


std::vector<std::vector<char>> Board::display() const {
	std::vector<std::vector<char>> output;
	for (int i = 0; i < N_ROWS; i++) {
		std::vector<char> row;
		for (int j = 0; j < N_COLS; j++) {
			row.push_back(cells[i][j]->getType());
		}
		output.push_back(row);
	}

	return output;
}

void Board::levelUp() {
	level = std::move(level->getNextLevel());
}

void Board::levelDown() {
	level = std::move(level->getPrevLevel());
}

int Board::getLevel() const {
	return level->getLevel();
}


void Board::changeCurrentBlock() {
	auto block = getNextBlock();
	clearDisplay();
	block->changeCells(display_cells);
	if (currentBlock) {
		blocks.push_back(std::move(currentBlock));
	}
	currentBlock = std::move(nextBlock);
	currentBlock->setBoard(this);
	nextBlock = std::move(block);
}

void Board::clearDisplay() {
	for (int i = 0; i < MAX_BLOCK_HEIGHT; i++) {
		for (int j = 0; j < MAX_BLOCK_HEIGHT; j++) {
			display_cells[i][j]->setType('n');
		}
	}
}

void Board::fall() {
	bool anything_moved = true;
	while (anything_moved) {
		anything_moved = false;
		for (auto& block : blocks) {
			if (block->Down()) {
				anything_moved = true;
			}
			block->move("down");
		}
	}
}

std::vector<int> Board::checkRowComplete() const {
	std::vector<int> output_rows;
	auto grid = display();
	for (int i = 0; i < N_ROWS; i++) {
		bool row_comp = true;
		for (int j = 0; j < N_COLS; j++) {
			if (grid[i][j] == 'n') {
				row_comp = false;
				break;
			}
		}
		if (row_comp) {
			output_rows.push_back(i);
		}
	}
	return output_rows;
}

std::unique_ptr<AbstractBlock> Board::getNextBlock() const {
	return level->getNextBlock();
}


bool Board::drop() {
	checkGameOver(currentBlock.get());
	auto completedRows = checkRowComplete();
	std::vector<int> block_levels;
	changeCurrentBlock();
	for (auto iter = blocks.begin(); iter != blocks.end();) {
		auto block = iter->get();
		block->removeRows(completedRows);
		if (block->isEmpty()) {
			block_levels.push_back(block->getLevel());
			iter = blocks.erase(iter);
		}
		else {
			iter++;
		}
	}

	if (completedRows.size() > 0) {
		level->updateBlockCount(true);
		updateScore(block_levels, completedRows.size());
		fall();
	}
	else {
		level->updateBlockCount(false);
	}

	if (completedRows.size() >= SPECIAL_ACTION_ROWS) {
		return true;
	}
	else {
		return false;
	}
}

void Board::checkGameOver(AbstractBlock* block) {
	bool only_reserve = true;
	for (auto cell : block->getCells()) {
		if (cell->getY() > RESERVE_ROWS) {
			only_reserve = false;
			break;
		}
	}
	if (only_reserve) {
		game_over = true;
	}
}

void Board::updateScore(std::vector<int> block_levels, int n_rows) {
	for (auto& level : block_levels) {
		score += std::pow((1 + level), 2);
	}
	score += std::pow((level->getLevel() + n_rows), 2);

	if (score > high_score) {
		high_score = score;
	}
}

int Board::getScore() const {
	return score;
}

int Board::getHighScore() const {
	return high_score;
}

int getMin(std::vector<int> vec) {
	int min = vec[0];
	for (auto val : vec) {
		if (val < min){
			min = val;
		}
	}
	return min;
}

std::vector<std::vector<char>> Board::displayNextBlock() const {
	
	std::vector<std::vector<char>> output;
	for (int i = 0; i < MAX_BLOCK_HEIGHT; i++) {
		std::vector<char> row;
		for (int j = 0; j < MAX_BLOCK_HEIGHT; j++) {
			row.push_back('n');
		}
		output.push_back(row);
	}
	
	// basically, normalize all the x and y values
	std::vector<int> xs;
	std::vector<int> ys;
	for (auto cell : nextBlock->getCells()) {
		xs.push_back(cell->getX());
		ys.push_back(cell->getY());
	}
	auto min_x = getMin(xs);
	auto min_y = getMin(ys);
	
	for (int i = min_y; i < MAX_BLOCK_HEIGHT; i++) {
		for (int j = min_x; j < MAX_BLOCK_HEIGHT; j++) {
			output[i- min_y][j- min_x] = display_cells[i][j]->getType();
		}
	}
	return output;
}

std::vector<std::vector<std::shared_ptr<Cell>>> Board::getGrid() {
	return cells;
}

void Board::restoreRandom() {
	level->setRandom(true);
}

void Board::setNoRandom(std::string file) {
	setFile(file);
	level->setRandom(false);
}

void Board::setSeed(int seed) {
	std::srand(seed);
}

void Board::setScriptFile(std::string file) {

}

void Board::setFile(std::string file) {
	auto new_file = std::make_unique<std::ifstream>(file);
	level->setFile(std::move(new_file));
}

bool Board::gameOver() const {
	return game_over;
}

void Board::forceCurrentBlock(char type) {
	auto block = level->createBlock(type);
	block->setBoard(this);
	currentBlock = std::move(block);
}

void Board::forceNextBlock(char type) {
	auto block = level->createBlock(type);
	block->setBoard(this);
	nextBlock = std::move(block);
}

std::shared_ptr<Cell> Board::getCell(int x, int y) {
	return cells[y][x];
}



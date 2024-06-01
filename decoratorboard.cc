#include "decoratorboard.h"

DecoratorBoard::DecoratorBoard(std::unique_ptr<AbstractBoard> board) : prev_board{ std::move(board) } { };

std::vector<std::vector<char>> DecoratorBoard::display() const {
	return prev_board->display();
}
std::vector<std::vector<char>> DecoratorBoard::displayNextBlock() const {
	return prev_board->displayNextBlock();
}

std::unique_ptr<AbstractBlock> DecoratorBoard::getNextBlock() const {
	return prev_board->getNextBlock();
}

bool DecoratorBoard::move(std::string command) {
	return prev_board->move(command);
}

bool DecoratorBoard::heavyMove(std::string command) {
	return prev_board->heavyMove(command);
}

void DecoratorBoard::levelUp() {
	prev_board->levelUp();
}
void DecoratorBoard::levelDown() {
	prev_board->levelDown();
}
int DecoratorBoard::getLevel() const {
	return prev_board->getLevel();
}

int DecoratorBoard::getScore() const {
	return prev_board->getScore();
}
int DecoratorBoard::getHighScore() const {
	return prev_board->getHighScore();
}

void DecoratorBoard::restoreRandom() {
	prev_board->restoreRandom();
}
void DecoratorBoard::setNoRandom(std::string file) {
	prev_board->setNoRandom(file);
}
void DecoratorBoard::setFile(std::string file) {
	prev_board->setFile(file);
}

void DecoratorBoard::changeCurrentBlock() {
	prev_board->changeCurrentBlock();
}
void DecoratorBoard::forceCurrentBlock(char block) {
	prev_board->forceCurrentBlock(block);
}
void DecoratorBoard::forceNextBlock(char block) {
	prev_board->forceNextBlock(block);
}
bool DecoratorBoard::gameOver() const {
	return prev_board->gameOver();
}

void DecoratorBoard::setSeed(int seed) {
	prev_board->setSeed(seed);
}
void DecoratorBoard::setScriptFile(std::string file) {
	prev_board->setScriptFile(file);
}

std::shared_ptr<Cell> DecoratorBoard::getCell(int x, int y) {
	return prev_board->getCell(x, y);
}
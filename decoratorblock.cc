#include "decoratorblock.h"

DecoratorBlock::~DecoratorBlock() {}

DecoratorBlock::DecoratorBlock(std::unique_ptr<AbstractBlock> b) : component{ std::move(b) } { };

void DecoratorBlock::move(std::string command) {
	component->move(command);
}

void DecoratorBlock::changeCells(std::vector<std::vector<std::shared_ptr<Cell>>> cells) {
	component->changeCells(cells);
}

void DecoratorBlock::drop() {
	component->drop();
}
 void DecoratorBlock::rotate(int direction) {
	 component->rotate(direction);
 }

 void DecoratorBlock::setBoard(Board* b) {
	 component->setBoard(b);
 }
 void DecoratorBlock::removeRows(std::vector<int> rows) {
	 component->removeRows(rows);
 }
 bool DecoratorBlock::isEmpty() {
	 return component->isEmpty();
 }
 std::vector<std::shared_ptr<Cell>> DecoratorBlock::getCells() {
	 return component->getCells();
 }
 int DecoratorBlock::getLevel() {
	 return component->getLevel();
 }

 void DecoratorBlock::setX(int x) {
	 component->setX(x);
 }
 void DecoratorBlock::setY(int y) {
	 return component->setY(y);
 }
 int DecoratorBlock::getX() {
	 return component->getX();
 }
 int DecoratorBlock::getY() {
	 return component->getY();
 }
 
#include "heavyblock.h"
#include "abstractblock.h"

HeavyBlock::HeavyBlock(std::unique_ptr<AbstractBlock> b) : DecoratorBlock{std::move(b)} {}

void HeavyBlock::move(std::string command) {
	component->move(command);
	component->move("down");
}

void HeavyBlock::rotate(int command){
	component->rotate(command);
	component->move("down");
}

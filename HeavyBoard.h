#ifndef HEAVYBOARD_H_
#define HEAVYBOARD_H_

#include "decoratorboard.h"
#include <memory>
#include <string>

class AbstractBlock;

class HeavyBoard : public DecoratorBoard {

public:
	HeavyBoard(std::unique_ptr<AbstractBoard>);
	std::unique_ptr<AbstractBlock> getNextBlock() const override;
	bool move(std::string) override;
};

#endif

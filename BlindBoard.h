#ifndef BLINDBOARD_H_
#define BLINDBOARD_H_
#include "decoratorboard.h"
#include <memory>

class AbstractBlock;
class BlindBoard : public DecoratorBoard {
	const int ROW_START = 3;
	const int ROW_END = 12;
	const int COL_START = 3;
	const int COL_END = 9;

public:
	BlindBoard(std::unique_ptr<AbstractBoard>);

	std::vector<std::vector<char>> display() const override;
};

#endif

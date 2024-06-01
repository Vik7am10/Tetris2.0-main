#include "HeavyBoard.h"
#include "abstractblock.h"
#include "heavyblock.h"
#include "Board.h"

HeavyBoard::HeavyBoard(std::unique_ptr<AbstractBoard> board) : DecoratorBoard{std::move(board)} { }

std::unique_ptr<AbstractBlock> HeavyBoard::getNextBlock() const {
	auto nextBlock = std::move(prev_board->getNextBlock());
	return std::make_unique<HeavyBlock>(std::move(nextBlock));
}

bool HeavyBoard::move(std::string command) {
	return heavyMove(command);
}

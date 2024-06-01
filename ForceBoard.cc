#include "ForceBoard.h"
#include "abstractblock.h"
#include "Board.h"

ForceBoard::ForceBoard(std::unique_ptr<AbstractBoard> board, char type) : DecoratorBoard{ std::move(board) } {
	prev_board->forceCurrentBlock(type);
};

#include "BlindBoard.h"
#include "abstractblock.h"
#include "Board.h"

BlindBoard::BlindBoard(std::unique_ptr<AbstractBoard> board) : DecoratorBoard{ std::move(board) } { };

std::vector<std::vector<char>> BlindBoard::display() const {
	auto output = prev_board->display();
	
	for (int i = ROW_START; i <= ROW_END; i++) {
		for (int j = COL_START; j <= COL_END; j++) {
			output[i][j] = ' ';
		}
	}
	return output;
}


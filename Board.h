#ifndef BOARD_H_
#define BOARD_H_
#include <map>
#include <vector>
#include <memory>
#include <string>

#include "subject.h"
#include "Level.h"
#include "abstractblock.h"
#include "abstractboard.h"
#include "cell.h"

// ok, now you need to use abstract board everywhere

class Board : public AbstractBoard, public Subject {

protected:
	std::vector<std::vector<std::shared_ptr<Cell>>> cells;
	std::vector<std::vector<std::shared_ptr<Cell>>> display_cells;

	std::vector<std::unique_ptr<AbstractBlock>> blocks;
	std::unique_ptr<AbstractBlock> currentBlock;
	std::unique_ptr<AbstractBlock> nextBlock;
	std::unique_ptr<Level> level;

	const int N_ROWS = 15;
	const int N_COLS = 11;
	const int START_ROW = 0;
	const int START_COL = 0;
	const int SPECIAL_ACTION_ROWS = 2;
	const int MAX_BLOCK_HEIGHT = 5;//10;
	const int RESERVE_ROWS = 4;

	int score;
	int high_score;
	bool game_over;

	bool drop();
	std::vector<int> checkRowComplete() const;
	void updateScore(std::vector<int>, int);
	void checkGameOver(AbstractBlock*);
	void fall();

	void clearDisplay();

	


public:
	Board(std::unique_ptr<Level>);
	// all of these should be override 
	virtual std::vector<std::vector<char>> display() const override;
	std::vector<std::vector<char>> displayNextBlock() const override;

	virtual std::unique_ptr<AbstractBlock> getNextBlock() const override;


	bool move(std::string) override;
	bool heavyMove(std::string) override;

	void levelUp() override;
	void levelDown() override;
	int getLevel() const override;

	int getScore() const override;
	int getHighScore() const override;

	void restoreRandom() override;
	void setNoRandom(std::string) override;
	void setFile(std::string) override;

	void changeCurrentBlock() override;
	void forceCurrentBlock(char) override;
	void forceNextBlock(char) override;
	bool gameOver() const override;

	void setSeed(int) override;
	void setScriptFile(std::string) override;

	std::vector<std::vector<std::shared_ptr<Cell>>> getGrid();
	std::shared_ptr<Cell> getCell(int, int) override;
};

#endif

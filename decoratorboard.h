#ifndef  DECORATORBOARD_H_
#define DECORATORBOARD_H_

#include "Board.h"
#include "abstractboard.h"
#include <memory>

class DecoratorBoard : public AbstractBoard {
protected:
	std::unique_ptr<AbstractBoard> prev_board;
	
public:
	DecoratorBoard(std::unique_ptr<AbstractBoard>);

	virtual std::vector<std::vector<char>> display() const override;
	virtual std::unique_ptr<AbstractBlock> getNextBlock() const override;

	std::vector<std::vector<char>> displayNextBlock() const override;

	virtual bool move(std::string) override;
	virtual bool heavyMove(std::string) override;
	
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

	std::shared_ptr<Cell> getCell(int, int) override;
};
#endif


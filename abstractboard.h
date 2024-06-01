#ifndef  ABSTRACTBOARD_H_
#define ABSTRACTBOARD_H_

#include <string>
#include <memory>
#include <vector>

class Cell;
class AbstractBlock;

class AbstractBoard {

protected:
	
public:
	virtual ~AbstractBoard();

	virtual std::vector<std::vector<char>> display() const = 0;
	virtual std::vector<std::vector<char>> displayNextBlock() const = 0;

	virtual std::unique_ptr<AbstractBlock> getNextBlock() const = 0;


	virtual bool move(std::string) = 0;
	virtual bool heavyMove(std::string) = 0;
	virtual void levelUp() = 0;
	virtual void levelDown() = 0;
	virtual int getLevel() const = 0;

	virtual int getScore() const = 0;
	virtual int getHighScore() const = 0;

	virtual void restoreRandom() = 0;
	virtual void setNoRandom(std::string) = 0;
	virtual void setFile(std::string) = 0;

	virtual void changeCurrentBlock() = 0;
	virtual void forceCurrentBlock(char) = 0;
	virtual void forceNextBlock(char) = 0;
	virtual bool gameOver() const = 0;

	virtual void setSeed(int) = 0;
	virtual void setScriptFile(std::string) = 0;

	virtual std::shared_ptr<Cell> getCell(int, int) = 0;
};

#endif // ! ABSTRACTBOARD_H_

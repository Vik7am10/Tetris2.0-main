#ifndef LEVEL_H_
#define LEVEL_H_

#include <map>
#include <memory>
#include <string>
#include <fstream>

class AbstractBlock;
class Level {
protected:
	std::string filename;
	

	int getRandom() const;
	char sampleType() const;
	char getTypeFromFile() const;
	

	int block_count;
	bool is_random;

public:
	std::unique_ptr<std::ifstream> block_file;
	std::map<char, int> curr_weights;
	int weight_sum = 0;

	// very temp
	Level();
	Level(std::map<char, int> weights);
	void updateBlockCount(bool);
	std::unique_ptr<AbstractBlock> createBlock(char) const;
	virtual std::unique_ptr<AbstractBlock> getNextBlock() const;
	virtual void move(AbstractBlock*, std::string);
	virtual void heavyMove(AbstractBlock*, std::string);
	virtual std::unique_ptr<Level> getNextLevel() const;
	virtual std::unique_ptr<Level> getPrevLevel() const;
	virtual int getLevel() const;

	virtual void setRandom(bool);
	void setFile(std::unique_ptr<std::ifstream>);
	virtual ~Level();
};

#endif

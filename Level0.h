#ifndef LEVEL0_H_
#define LEVEL0_H_
#include <map>
#include "Board.h"
#include <fstream>

class Level0 : public Level {

public:
	Level0();
	void setRandom(bool) override;
	std::unique_ptr<Level> getNextLevel() const override;
	std::unique_ptr<Level> getPrevLevel() const override;

	int getLevel() const override;
};
#endif

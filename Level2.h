#ifndef LEVEL2_H_
#define LEVEL2_H_
#include <map>
#include "Board.h"

class Level2 : public Level {
public:
	Level2();
	std::unique_ptr<Level> getNextLevel() const override;
	std::unique_ptr<Level> getPrevLevel() const override;

	int getLevel() const override;
};
#endif

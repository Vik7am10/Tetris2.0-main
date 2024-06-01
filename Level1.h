#ifndef LEVEL1_H_
#define LEVEL1_H_
#include <map>
#include <memory>
#include "Level.h"
#include "Board.h"

class Level1 : public Level {

public:
	Level1();
	std::unique_ptr<Level> getNextLevel() const override;
	std::unique_ptr<Level> getPrevLevel() const override;

	int getLevel() const override;
};
#endif

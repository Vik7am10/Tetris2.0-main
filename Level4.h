#ifndef LEVEL4_H_
#define LEVEL4_H_
#include <map>
#include <string>
#include "Board.h"
#include "abstractblock.h"

class Level4 : public Level {
public:
	Level4();
	void move(AbstractBlock*, std::string) override;
	std::unique_ptr<Level> getNextLevel() const override;
	std::unique_ptr<Level> getPrevLevel() const override;

	int getLevel() const override;
};

#endif

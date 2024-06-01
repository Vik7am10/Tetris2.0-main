#ifndef LEVEL3_H_
#define LEVEL3_H_
#include <map>
#include <string>
#include "Board.h"
#include "abstractblock.h"

class Level3 : public Level {
public:
	Level3();
	void move(AbstractBlock*, std::string) override;
	std::unique_ptr<Level> getNextLevel() const override;
	std::unique_ptr<Level> getPrevLevel() const override;

	int getLevel() const override;
};

#endif

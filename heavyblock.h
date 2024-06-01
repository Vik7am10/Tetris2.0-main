#ifndef HEAVYBLOCK_H_
#define HEAVYBLOCK_H_

#include "decoratorblock.h"
#include <string>

class AbstractBlock;
class HeavyBlock: public DecoratorBlock {
    public:
        HeavyBlock(std::unique_ptr<AbstractBlock> b);
        void move(std::string direction) override;
        void rotate(int) override;
};

#endif
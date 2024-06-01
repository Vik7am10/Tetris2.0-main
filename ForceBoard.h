#ifndef FORCEBOARD_H_
#define FORCEBOARD_H_
#include "decoratorboard.h"
#include <memory>

class AbstractBlock;
class ForceBoard : public DecoratorBoard {

public:
	ForceBoard(std::unique_ptr<AbstractBoard>, char);

};

#endif

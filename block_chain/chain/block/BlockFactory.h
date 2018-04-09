#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "Block.h"

class BlockFactory
{
    public:
        Block* createBlock(ElementObject* element);
};

#endif // BLOCKFACTORY_H

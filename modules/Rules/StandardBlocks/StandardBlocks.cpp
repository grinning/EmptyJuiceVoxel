#include "StandardBlocks.hpp"

#include <iostream>

namespace StandardBlocks
{
    void init()
    {
        BlockInfo* air         = new BlockInfo;
        BlockInfo* stone       = new BlockInfo;
        BlockInfo* grass       = new BlockInfo;
        BlockInfo* dirt        = new BlockInfo;
        BlockInfo* cobblestone = new BlockInfo;

        State& core = State::GET();

        BLOCK_AIR         = core.registerData(air);
        BLOCK_STONE       = core.registerData(stone);
        BLOCK_GRASS       = core.registerData(grass);
        BLOCK_DIRT        = core.registerData(dirt);
        BLOCK_COBBLESTONE = core.registerData(cobblestone);

        std::cout << "Loaded StandardBlocks" << std::endl;
    }
}

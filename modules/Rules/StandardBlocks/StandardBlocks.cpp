#include "StandardBlocks.hpp"

namespace StandardBlocks
{
    void init()
    {
        BlockInfo air;
        BlockInfo stone;
        BlockInfo grass;
        BlockInfo dirt;
        BlockInfo cobblestone;

        State& core = State::GET();

        BLOCK_AIR         = core.registerBlock(air);
        BLOCK_STONE       = core.registerBlock(stone);
        BLOCK_GRASS       = core.registerBlock(grass);
        BLOCK_DIRT        = core.registerBlock(dirt);
        BLOCK_COBBLESTONE = core.registerBlock(cobblestone);
    }
}

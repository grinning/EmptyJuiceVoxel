#ifndef STANDARDBLOCKS_INCLUDED
#define STANDARDBLOCKS_INCLUDED

#include "GlobalState.hpp"

using namespace EJV;

namespace StandardBlocks
{
    static State::ID BLOCK_AIR;
    static State::ID BLOCK_STONE;
    static State::ID BLOCK_GRASS;
    static State::ID BLOCK_DIRT;
    static State::ID BLOCK_COBBLESTONE;

    extern "C"
    {
        void init();

        void destroy() {}

        void tick(Action::Base* event) {}
    }
}

#endif // STANDARDBLOCKS_INCLUDED

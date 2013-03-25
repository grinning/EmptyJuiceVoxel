#ifndef STANDARDITEMS_INCLUDED
#define STANDARDITEMS_INCLUDED

#include "GlobalState.hpp"

using namespace EJV;

namespace StandardItems
{
    static State::ID ITEM_IRON_SHOVEL;
    static State::ID ITEM_IRON_PICKAXE;
    static State::ID ITEM_IRON_AXE;
    static State::ID ITEM_FLINT_AND_STEEL;
    static State::ID ITEM_APPLE;

    extern "C"
    {
        void init();

        void destroy() {}

        void tick(Action::Base* event) {}
    }
}

#endif // STANDARDITEMS_INCLUDED

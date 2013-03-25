#include "StandardItems.hpp"

namespace StandardItems
{
    void init()
    {
        ItemInfo ironShovel;
        ItemInfo ironPickaxe;
        ItemInfo ironAxe;
        ItemInfo flintSteel;
        ItemInfo apple;

        State& core = State::GET();

        ITEM_IRON_SHOVEL     = core.registerItem(ironShovel);
        ITEM_IRON_PICKAXE    = core.registerItem(ironPickaxe);
        ITEM_IRON_AXE        = core.registerItem(ironAxe);
        ITEM_FLINT_AND_STEEL = core.registerItem(flintSteel);
        ITEM_APPLE           = core.registerItem(apple);
    }
}

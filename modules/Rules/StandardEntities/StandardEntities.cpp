#include "StandardEntities.hpp"

namespace StandardEntities
{
    void init()
    {
        EntityInfo player;

        State& core = State::GET();

        ENTITY_PLAYER = core.registerEntity(player);
    }
}

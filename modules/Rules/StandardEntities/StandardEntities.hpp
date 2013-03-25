#ifndef STANDARDENTITIES_INCLUDED
#define STANDARDENTITIES_INCLUDED

#include "GlobalState.hpp"

using namespace EJV;

namespace StandardEntities
{
    static State::ID ENTITY_PLAYER;

    extern "C"
    {
        void init();

        void destroy() {}

        void tick(Action::Base* event) {}
    }
}

#endif // STANDARDENTITIES_INCLUDED

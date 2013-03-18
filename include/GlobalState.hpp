/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef GLOBALSTATE_INCLUDED
#define GLOBALSTATE_INCLUDED

#include "Chunk.hpp"

#include <map>

#include <cstring>

/**
 * @file Storage for the global state
 *
 */

namespace EJV
{
	struct World
	{
		typedef std::map<std::pair<int, int>, Chunk*> ChunkMap; // Temporary

		ChunkMap loadedChunks;
	};

	class State
	{
        private:
		// Singleton
		static State *_singleton;

		// Private constructors / destructors
		State() {}
		State(const State& orig) {}
		virtual ~State() {}
		State& operator=(const State& orig) { return *this; }

        public:
		typedef std::map<const std::string, World*> WorldMap; // Temporary

		WorldMap loadedWorlds;

		inline static State &GET()
		{
			return _singleton ? *_singleton : *(_singleton = new State);
		}
	};
}

#endif // GLOBALSTATE_H

/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef GLOBALSTATE_INCLUDED
#define GLOBALSTATE_INCLUDED

#include "Chunk.hpp"
#include "Action.hpp"

#include <map>
#include <queue>
#include <list>
#include <vector>

#include <cstring>

/**
 * @file Storage for the global state
 *
 */

namespace EJV
{
    struct Point3D
    {
        int x, y, z;

        virtual bool operator<(const Point3D& point) const
        {
            return x < point.x && y < point.y && z < point.z;
        }
    };

	struct World
	{
		typedef std::map<Point3D, Chunk*> ChunkMap;

		typedef std::queue<std::pair<Point3D, Chunk*> > ChunkUpdatesList;

		ChunkMap loadedChunks;

		ChunkUpdatesList chunkUpdates;

        /** \brief Fetches a chunk and updates the cache
         *
         * Takes care of loading and generating chunks
         *
         */
		Chunk* getChunk(const Point3D& point);

		/** Loads a chunk from the disk (Discards any unsaved changes) */
		Chunk* loadChunk(const Point3D& point);

		/** Unloads and saves chunk */
		void unloadChunk(const Point3D& point);

        /** Saves world to disk */
        void saveWorld() const;

        /** Updates chunks */
        void updateChunks();
	};

	/** Stores information about a block */
	struct BlockInfo
	{
	    // WIP

	    double hardness;
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

        protected:
            typedef std::vector<BlockInfo> BlockList;

            BlockList _registeredBlocks;

            bool gameTick();

		public:
            typedef std::map<const std::string, World*> WorldMap;
            typedef std::list<Action::Base*> ActionList;

            WorldMap loadedWorlds;
            ActionList actions;

            inline static State &GET()
            {
                return _singleton ? *_singleton : *(_singleton = new State);
            }

            void run()
            {
                while (1) if (gameTick()) return;
            }

            // BLOCK INFORMATION
            BlockInfo& getBlockInfo(const unsigned short index) { return _registeredBlocks.at(index); }

            const BlockInfo& getBlockInfo(const unsigned short index) const { return _registeredBlocks.at(index); }

            unsigned short registerBlock(const BlockInfo& info);

            unsigned short getNumRegisteredBlocks() const { return _registeredBlocks.size(); }

            bool isRegistered(const unsigned short index) const { return index < _registeredBlocks.size(); }
	};
}

#endif // GLOBALSTATE_H

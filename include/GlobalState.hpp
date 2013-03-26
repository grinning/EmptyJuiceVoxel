/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef GLOBALSTATE_INCLUDED
#define GLOBALSTATE_INCLUDED

#include "Chunk.hpp"
#include "Action.hpp"

#include "Metadata.hpp"

#include "Module.hpp"

// STL
#include <map>
#include <queue>
#include <list>
#include <vector>

// C
#include <cstring>

// C++11
#include <chrono>
#include <thread>

/**
 * @file Storage for the global state
 *
 */

namespace EJV
{
    struct Point3D
    {
        Point3D() {}
        Point3D(int _x, int _y, int _z) : x(_x), y(_y), z (_x) {}

        int x, y, z;

        virtual bool operator<(const Point3D& point) const
        {
            return x < point.x && y < point.y && z < point.z;
        }
    };

    struct Entity : public Metadata
    {
        unsigned short type;

        // TODO: Dynamic ownership

        double posX, posY, posZ;
    };

	struct World : public Metadata
	{
	    // Name

	    std::string worldName;

		// Entities

		typedef std::list<Entity*> EntityList;

		EntityList entities;

		// Chunks

		typedef std::map<Point3D, Chunk*> ChunkMap;

		typedef std::list<std::pair<Point3D, Chunk*> > ChunkUpdatesList;

		ChunkMap loadedChunks;

		ChunkUpdatesList chunkUpdates;

		// Modules

		GeneratorModule* generator;

		LoaderModule* loader;

		// Time

		uint64_t ticks;

		// Functions

		/** Sets the world's name. */
		World(const std::string& name) : worldName(name) {}

		/** Initializes the loader/generator.*/
        void initProviders();

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
        void update();

        /** Updates a block */
        void updateBlock(Chunk* chunk, const Point3D& point);
	};

	struct Location
	{
	    World* world;

	    int x, y, z;
	};

	/** Stores information about a block */
	struct BlockInfo
	{
	    typedef void (*UpdateFunction)(World* world, const Point3D& position, BlockInfo& info);

	    UpdateFunction updateFunc; // If null, use standard block update function

	    double hardness;

	    BlockInfo() {}

	    BlockInfo(const double& _hardness) : hardness(_hardness) {}
	};

	/** Stores information about an item */
	struct ItemInfo
	{
	    typedef void (*UpdateFunction)(ItemInfo& info);

	    UpdateFunction updateFunc; // If null, use the standard item update function

	    double maxDurability;

	    double attackStrength;

	    ItemInfo() {}

	    ItemInfo(const double& _maxDurability,
                 const double& _attackStrength) : maxDurability(_maxDurability), attackStrength(_attackStrength) {}
	};

	/** Stores information about an entity */
	struct EntityInfo
	{
	    typedef void (*UpdateFunction)(World* world, Entity* entity, EntityInfo& info);

	    UpdateFunction updateFunc; // If null, use the standard item update function

	    double maxHealth;

	    double attackStrength;

	    EntityInfo() {}
	};

	class State : public Metadata
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
            typedef std::list<RuleModule*> RuleModuleList;
            typedef std::list<UIModule*>   UIModuleList;

            RuleModuleList _rules;
            UIModuleList   _uis;

            // Timing

            unsigned int _tickDuration;

            uint64_t _ticks;

            std::chrono::steady_clock::time_point _before;

            // Functions

            bool gameTick();

		public:
            typedef std::vector<World*> WorldList;
            typedef std::list<Action::Base*> ActionList;

            typedef unsigned short ID;

            WorldList loadedWorlds;
            ActionList actions;

            // MUST NOT BE INLINED
            static State &GET();

            void run();

            // MODULES
            void registerRuleModule(RuleModule* module);
            void registerUIModule(UIModule* module);

            // SIMULATION SPEED
            unsigned int getTickDuration() const { return _tickDuration; }
            double       getTickDurationSeconds() const { return _tickDuration / 1000.0; }

            void setTickDuration(const unsigned int& speed)  { _tickDuration = speed; }
            void setTickDurationSeconds(const double& speed) { _tickDuration = speed * 1000.0; }

            uint64_t getTicks() const { return _ticks; }
	};
}

#endif // GLOBALSTATE_H

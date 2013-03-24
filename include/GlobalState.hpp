/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef GLOBALSTATE_INCLUDED
#define GLOBALSTATE_INCLUDED

#include "Chunk.hpp"
#include "Action.hpp"

#include "Module.hpp"

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

    struct Entity
    {
        unsigned short type;

        // TODO: Dynamic ownership

        double posX, posY, posZ;
    };

	struct World
	{
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
	};

	/** Stores information about a block */
	struct BlockInfo
	{
	    typedef void (*UpdateFunction)(World* world, const Point3D& position, BlockInfo& info);

	    UpdateFunction updateFunc; // If null use standard block update function

	    double hardness;
	};

	/** Stores information about an item */
	struct ItemInfo
	{
	    typedef void (*UpdateFunction)(ItemInfo& info);

	    UpdateFunction updateFunc; // If null, use the standard item update function

	    double maxDurability;

	    double attackStrength;
	};

	/** Stores information about an entity */
	struct EntityInfo
	{
	    typedef void (*UpdateFunction)(World* world, Entity* entity, EntityInfo& info);

	    UpdateFunction updateFunc; // If null, use the standard item update function

	    double maxHealth;

	    double attackStrength;
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
            typedef std::vector<BlockInfo>  BlockList;
            typedef std::vector<ItemInfo>   ItemList;
            typedef std::vector<EntityInfo> EntityList;

            BlockList  _registeredBlocks;
            ItemList   _registeredItems;
            EntityList _registeredEntities;

            typedef std::list<RuleModule*> RuleModuleList;
            typedef std::list<UIModule*>   UIModuleList;

            RuleModuleList _rules;
            UIModuleList   _uis;

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

            // MODULES
            void registerRuleModule(RuleModule* module);
            void registerUIModule(UIModule* module);

            // INFORMATION
            BlockInfo& getBlockInfo(const unsigned short index) { return _registeredBlocks.at(index); }
            const BlockInfo& getBlockInfo(const unsigned short index) const { return _registeredBlocks.at(index); }

            ItemInfo& getItemInfo(const unsigned short index) { return _registeredItems.at(index); }
            const ItemInfo& getItemInfo(const unsigned short index) const { return _registeredItems.at(index); }

            EntityInfo& getEntityInfo(const unsigned short index) { return _registeredEntities.at(index); }
            const EntityInfo& getEntityInfo(const unsigned short index) const { return _registeredEntities.at(index); }

            unsigned short registerBlock(const BlockInfo& info);
            unsigned short registerItem(const ItemInfo& info);
            unsigned short registerEntity(const EntityInfo& info);

            unsigned short getNumRegisteredBlocks() const { return _registeredBlocks.size(); }
            unsigned short getNumRegisteredItems() const { return _registeredItems.size(); }
            unsigned short getNumRegisteredEntities() const { return _registeredEntities.size(); }

            bool isBlockRegistered(const unsigned short index) const { return index < _registeredBlocks.size(); }
            bool isItemRegistered(const unsigned short index) const { return index < _registeredItems.size(); }
            bool isEntityRegistered(const unsigned short index) const { return index < _registeredEntities.size(); }
	};
}

#endif // GLOBALSTATE_H

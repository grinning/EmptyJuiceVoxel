/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef RULES_INCLUDED
#define RULES_INCLUDED

#include <string>

#include "Action.hpp"
#include "Chunk.hpp"
#include "Metadata.hpp"
#include "Menu.hpp"

/**
 * @file Interface for rules modules
 *
 */

namespace EJV {
    /**
     * Ticks each rules module. Used for simulation/physics.

     * @param act List of actions that players have taken.
     */
	void tick(action *act);

	/**
	 * Call used by rules to get a chunk.
	 * Will generate if not found in loader.
	 *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return Chunk at those coords.
	 */
	chunk *getChunk(int x,int y,int z); //external
	/**
	 * Call used by rules to set a chunk
	 *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @param c Chunk to set.
	 */
	void setChunk(int x,int y,int z,chunk *c); //external


    /**
     * Call used by rules to get the metadata
     * of the world.
     *
     * @param which Name of metadata's module.
     * @return Metadata of that module.
     */
	metadata *getMetadata(std::string which); //external
	/**
	 * Call used by rules to set the metadata
	 * of the world.
	 *
	 * @param which Name of metadata's module.
	 * @param data Metadata to set.
	 */
	void setMetadata(std::string which,metadata* data); //external

	/**
	 * Call used by rules to display a menu to a player.
	 *
	 * @param m Menu to display.
	 * @param playerName name of the player to show the menu.
	 */
	void displayMenu(menu *m, std::string playerName); //external
}

#endif //RULES_INCLUDED

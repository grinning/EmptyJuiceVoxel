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

extern "C"
{
	/**
	 * Run when the module is loaded.
	 * This allows for the module to
	 * initialize based on configurations.
	 */
	void init();

	/**
	 * Run when the module is unloaded.
	 * This allows modules to close files,
	 * end connections, and clean up.
	 */
	void destroy();

	/**
	 * Ticks each rules module. Used for simulation/physics.

	 * @param act List of actions that players have taken.
	 */
	void tick(EJV::Action::Base *act);
}

// EXTERNAL

/**
 * Call used by rules to get a chunk.
 * Will generate if not found in loader.
 *
 * @param x X chunk coord.
 * @param y Y chunk coord.
 * @param z Z chunk coord.
 * @return Chunk at those coords.
 */
extern "C" EJV::Chunk *getChunk(int x, int y, int z);

/**
 * Call used by rules to set a chunk
 *
 * @param x X chunk coord.
 * @param y Y chunk coord.
 * @param z Z chunk coord.
 * @param c Chunk to set.
 */
extern "C" void setChunk(int x, int y, int z, EJV::Chunk *c);

/**
 * Call used by rules to get the metadata
 * of the world.
 *
 * @param which Name of metadata's module.
 * @return Metadata of that module.
 */
extern "C" EJV::Metadata *getMetadata(const std::string& which);

/**
 * Call used by rules to set the metadata
 * of the world.
 *
 * @param which Name of metadata's module.
 * @param data Metadata to set.
 */
extern "C" void setMetadata(const std::string& which, EJV::Metadata* data);

/**
 * Call used by rules to display a menu to a player.
 *
 * @param m Menu to display.
 * @param playerName name of the player to show the menu.
 */
//extern "C" void displayMenu(EJV::Menu *m, const std::string& playerName); // I think a pointer to a player structure would be more suitable -Andrew

#endif //RULES_INCLUDED

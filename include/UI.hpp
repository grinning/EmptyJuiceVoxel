/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef UI_INCLUDED
#define UI_INCLUDED

#include "Chunk.hpp"
#include "Action.hpp"
#include "Menu.hpp"

/**
 * @file Interface for UI modules
 *
 */
namespace EJV
{
    /**
     * Updates a chunk for the UI/network connections.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return Updated chunk.
     */
	extern "C" void updateChunk(int x, int y, int z, Chunk *c);

    /**
     * Call used by UI to get a chunk.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return The chunk at that position.
     */
	Chunk *getChunk(int x, int y, int z); //external

	/**
	 * Call used by UI to push a user action.
	 *
	 * @param act An action the player mad.
	 */
	void userAction(Action* act); //external

    /**
     * Shows the user a menu.
     *
     * @param m Menu to display.
     * @param playerName Name of Player to show menu.
     */
    extern "C" void displayMenu(Menu *m, const std::string& playerName); // I think a pointer to a player structure would be more suitable -Andrew

}

#endif //UI_INCLUDED
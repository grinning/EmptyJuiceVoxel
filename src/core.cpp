/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#include <iostream>
#include <map>
#include <queue>

#include "Loader.hpp"
#include "Generator.hpp"
#include "Rules.hpp"
#include "UI.hpp"

// TO BE REMOVED

int main(int argc, char *argv[])
{
    EJV::Action *nextAction;

    while(1)
    {
        if (actions.empty()) nextAction = 0;
        else
        {
            nextAction = actions.front();
            actions.pop();
        }

        tick(nextAction);

        for(; !changedChunks.empty(); changedChunks.pop())
        {
            ChunkWithCoord cwc = changedChunks.front();

            updateChunk(cwc.x, cwc.y, cwc.z, cwc.c);
        }
    }
}

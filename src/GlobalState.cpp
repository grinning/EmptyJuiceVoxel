#include "GlobalState.hpp"

// Temp headers
#include "Loader.hpp"
#include "Generator.hpp"

namespace EJV
{
    Chunk* World::getChunk(const Point3D& point) const
    {
        Chunk*& chunk = loadedChunks[point];

        if (chunk) return temp;

        // If chunk isn't loaded, try to load it
        chunk = loadChunk(point);

        // If chunk doesn't exist, generate it
        if (!chunk) chunk = generateChunk(point);

        return chunk;
    }

    Chunk* loadChunk(const Point3D& point)
    {
        Chunk*& chunk = loadedChunks[point];

        chunk = loadChunk(point);

        // If chunk doesn't exist, generate it
        if (!chunk) chunk = generateChunk(point);

        return chunk;
    }

    void World::unloadChunk(const Point3D& point)
    {
        ChunkMap::iterator it = loadedChunks.find(point);

        // Make sure chunk is laoded
        if (it == loadedChunks.end()) return;

        // Save chunk to disk
        putChunk(point.x, point.y, point.z, chunk);

        // Unload chunk
        delete *it;

        loadedChunks.erase(it);
    }

    void World::saveWorld() const
    {
        for (ChunkMap::const_iterator it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
        {
            putChunk(it->first.x, it->first.y, it->first.z, it->second);
        }
    }

    void World::updateChunks()
    {
        // Call module methods
    }

    bool State::gameTick()
    {
        // Update chunks
        for (WorldList::iterator it = loadedWorlds.begin(); it != loadedWorlds.end(); ++it)
        {
            (*it)->updateChunks();
        }

        // Pass control to modules
        for (ActionList::iterator it = actions.begin(); it != actions.end(); ++it)
        {
            tick(*it);
        }

        actions.clear();
    }
}

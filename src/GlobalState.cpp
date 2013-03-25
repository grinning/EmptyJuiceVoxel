#include "GlobalState.hpp"

// Temp headers
#include "Loader.hpp"
#include "Generator.hpp"
#include "Rules.hpp"

namespace EJV
{
    State *State::_singleton = 0;

    State& State::GET()
    {
        return _singleton ? *_singleton : *(_singleton = new State);
    }

    void World::initProviders() {
        generator->setWorldName(worldName);
        loader->setWorldName(worldName);
    }

    Chunk* World::getChunk(const Point3D& point)
    {
        Chunk*& chunk = loadedChunks[point];

        if (chunk) return chunk;

        // If chunk isn't loaded, try to load it
        chunk = loader->loadChunk(point.x, point.y, point.z);

        // If chunk doesn't exist, generate it
        if (!chunk) chunk = generator->generateChunk(point.x, point.y, point.z);

        return chunk;
    }

    Chunk* World::loadChunk(const Point3D& point)
    {
        Chunk*& chunk = loadedChunks[point];

        chunk = loader->loadChunk(point.x, point.y, point.z);

        // If chunk doesn't exist, generate it
        if (!chunk) chunk = generator->generateChunk(point.x, point.y, point.z);

        return chunk;
    }

    void World::unloadChunk(const Point3D& point)
    {
        ChunkMap::iterator it = loadedChunks.find(point);

        // Make sure chunk is loded
        if (it == loadedChunks.end()) return;

        // Save chunk to disk
        loader->putChunk(point.x, point.y, point.z, it->second);

        // Unload chunk
        delete it->second;

        loadedChunks.erase(it);
    }

    void World::saveWorld() const
    {
        for (ChunkMap::const_iterator it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
        {
            loader->putChunk(it->first.x, it->first.y, it->first.z, it->second);
        }
    }

    void World::update()
    {
        // Update blocks
        for (ChunkUpdatesList::iterator it = chunkUpdates.begin(); it != chunkUpdates.end(); ++it)
        {
            Chunk*& chunk = it->second;

            // Make sure that the chunk is valid
            if (!chunk) continue;

            // Fetch block information
            BlockInfo& info = State::GET().getBlockInfo(chunk->blocks[it->first.x][it->first.y][it->first.z]);

            // Update block
            if (info.updateFunc)
            {
                info.updateFunc(this, it->first, info);
            }
        }

        // Update entities
        for (EntityList::iterator it = entities.begin(); it != entities.end(); ++it)
        {
            // Fetch entity information
            EntityInfo& info = State::GET().getEntityInfo((*it)->type);

            // Update entity
            if (info.updateFunc)
            {
                info.updateFunc(this, *it, info);
            }
        }
    }

    bool State::gameTick()
    {
        // Update worlds
        for (WorldMap::iterator it = loadedWorlds.begin(); it != loadedWorlds.end(); ++it)
        {
            ++it->second->ticks;

            it->second->update();
        }

        // Pass control to modules
        for (ActionList::iterator it = actions.begin(); it != actions.end(); ++it)
        {
            for (RuleModuleList::iterator mod = _rules.begin(); mod != _rules.end(); ++mod)
            {
                (*mod)->tick(*it);
            }
        }

        actions.clear();

        return true;
    }

    void State::run()
    {
        while (gameTick())
        {
            ++_ticks;

            // Get current time
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();

            // Calculate delta time
            std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(now - _before);

            double dt = time_span.count();

            // Wait
            //if (dt < _tickDuration) std::thread::sleep_for();

            _before = std::chrono::steady_clock::now();
        }
    }

    void State::registerRuleModule(RuleModule* module)
    {
        if (!module) return;

        _rules.push_back(module);
    }

    void State::registerUIModule(UIModule* module)
    {
        if (!module) return;

        _uis.push_back(module);
    }

    State::ID State::registerBlock(const BlockInfo& info)
    {
        _registeredBlocks.push_back(info);

        return _registeredBlocks.size() - 1;
    }

    State::ID State::registerItem(const ItemInfo& info)
    {
        _registeredItems.push_back(info);

        return _registeredItems.size() - 1;
    }

    State::ID State::registerEntity(const EntityInfo& info)
    {
        _registeredEntities.push_back(info);

        return _registeredEntities.size() - 1;
    }
}

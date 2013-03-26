#include "GlobalState.hpp"

#include <iostream>

#include <dlfcn.h>

using namespace EJV;

int main()
{
    // TODO: Add configuration files

    RuleModule* standardBlocks = new RuleModule;
    LoaderModule* anvil = new LoaderModule;
    GeneratorModule* flatland = new GeneratorModule;
    UIModule* gfx = new UIModule;

    if (!standardBlocks->load("bin/libStandardBlocks.so"))
    {
        std::cout << "Unable to load module libStandardBlocks.so" << std::endl;
        std::cout << "Error: " << dlerror() << std::endl;
        return -1;
    }

    standardBlocks->loadFunctions();

    if (!standardBlocks->init || !standardBlocks->destroy || !standardBlocks->tick)
    {
        std::cout << "Unable to load libStandardBlock.so's functions" << std::endl;
        std::cout << "Error: " << dlerror() << std::endl;
        return -1;
    }

    standardBlocks->init();

    // Initialize world
    State& CORE = State::GET();

    CORE.registerRuleModule(standardBlocks);
    CORE.registerUIModule(gfx);

    World* mainWorld = new World("main");

    mainWorld->loader = anvil;
    mainWorld->generator = flatland;

    CORE.loadedWorlds["main"] = mainWorld;

    // Reguest chunk
    //mainWorld->loadChunk(Point3D(0, 0, 0));

    std::cout << "Number of registered blocks:   " << CORE.getNumRegisteredBlocks() << std::endl;
    std::cout << "Number of registered items:    " << CORE.getNumRegisteredItems() << std::endl;
    std::cout << "Number of registered entities: " << CORE.getNumRegisteredEntities() << std::endl;

    CORE.run();

    standardBlocks->destroy();
}

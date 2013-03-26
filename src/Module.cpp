#include "Module.hpp"

#include <dlfcn.h>

namespace EJV
{
    bool SharedLibrary::load(const std::string& path)
    {
        _handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);

        return _handle;
    }

    void SharedLibrary::unload()
    {
        if (_handle)
            dlclose(_handle);
    }

    void* SharedLibrary::fetchFunctionPointer(const std::string& name)
    {
        return _handle ? dlsym(_handle, name.c_str()) : 0;
    }

    void Module::loadFunctions()
    {
        init = (InitFunc) fetchFunctionPointer("init");
        destroy = (DestroyFunc) fetchFunctionPointer("destroy");
    }

    void RuleModule::loadFunctions()
    {
        Module::loadFunctions();

        tick = (TickFunc) fetchFunctionPointer("tick");
    }

    void UIModule::loadFunctions()
    {
        Module::loadFunctions();

        updateChunk = (UpdateChunkFunc) fetchFunctionPointer("updateChunk");
        displayMenu = (DisplayMenuFunc) fetchFunctionPointer("displayMenu");
    }

    void LoaderModule::loadFunctions()
    {
        Module::loadFunctions();

        loadChunk = (LoadChunkFunc) fetchFunctionPointer("loadChunk");
        putChunk = (PutChunkFunc) fetchFunctionPointer("putChunk");
        releaseChunk = (ReleaseChunkFunc) fetchFunctionPointer("releaseChuk");

        setWorldName = (SetWorldNameFunc) fetchFunctionPointer("setWorldName");

        getMetadata = (GetMetadataFunc) fetchFunctionPointer("getMetadata");
        setMetadata = (SetMetadataFunc) fetchFunctionPointer("setMetadata");
    }

    void GeneratorModule::loadFunctions()
    {
        Module::loadFunctions();

        generateChunk = (GenerateChunkFunc) fetchFunctionPointer("generateChunk");
        setWorldName = (SetWorldNameFunc) fetchFunctionPointer("setWorldName");
    }
}

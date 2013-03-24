#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include <cstring>
#include <string>

#include "Action.hpp"
#include "Chunk.hpp"
#include "Menu.hpp"

namespace EJV
{
    // POSIX-only for now

    class SharedLibrary
    {
        protected:
            void* _handle;

        public:
            SharedLibrary() : _handle(0) {}

            virtual ~SharedLibrary() {}

            bool load(const std::string& path);

            void unload();

            void* fetchFunctionPointer(const std::string& name);
    };

    struct Module : public SharedLibrary
    {
        typedef void (*InitFunc)();
        typedef void (*DestroyFunc)();

        InitFunc init;
        DestroyFunc destroy;

        virtual void loadFunctions();
    };

    struct RuleModule : public Module
    {
        typedef void (*TickFunc)(Action::Base*);

        TickFunc tick;

        virtual void loadFunctions();
    };

    struct UIModule : public Module
    {
        typedef void (*UpdateChunkFunc)(int x, int y, int z, Chunk *c);
        typedef void (*DisplayMenuFunc)(Menu::Base *m, const std::string& playerName);

        UpdateChunkFunc updateChunk;
        DisplayMenuFunc displayMenu;

        virtual void loadFunctions();
    };

    struct LoaderModule : public Module
    {
        typedef Chunk* (*LoadChunkFunc)(int x, int y, int z);
        typedef void (*PutChunkFunc)(int x, int y, int z, Chunk*);
        typedef void (*ReleaseChunkFunc)(int x, int y, int z, Chunk*);

        LoadChunkFunc loadChunk;
        PutChunkFunc putChunk;
        ReleaseChunkFunc releaseChunk;

        virtual void loadFunctions();
    };

    struct GeneratorModule : public Module
    {
        typedef Chunk* (*GenerateChunkFunc)(int x, int y, int z);

        GenerateChunkFunc generateChunk;

        virtual void loadFunctions();
    };
}

#endif // MODULE_INCLUDED

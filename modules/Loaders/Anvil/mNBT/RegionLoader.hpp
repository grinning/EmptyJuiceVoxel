/*#**************************************************#*
 * mNBT  :  NBT manipulation system by Manearrior     *
 *#**************************************************#*/

/**
 * @file
 * Holds the region loading class.
 */
#ifndef REGIONLOADER_H_INCLUDED
#define REGIONLOADER_H_INCLUDED

#include <map>
#include <queue>
#include <string>
#include <vector>

#include "Block.h"
#include "Tag.h"

/// mNBT system namespace.
namespace mNBT
{
    /**
     * Region file loader. This provides timestamps
     * and generates Tag structures representing chunks.
     * Stores all chunks compressed data and will create
     * empty chunks. Not. Thread. Safe. Recommendable to
     * use a threaded holding class/function.
     */
    class RegionLoader : public Block
    {
        private:
            /// THOU SHALT NOT CREATE AN UNINITIALIZED REGION LOADER.
            RegionLoader() {}

        protected:
            /// All actual X >> 9; actual Z >> 9. Position of region.
            int xpos;
            /// Same as xpos. Silly Doxygen.
            int zpos;
            /// Both the path to the world and the world's name.
            std::string path;
            /// Vector of chunk data. chunks[X >> 9][Z >> 9][INDEX].
            std::vector<char> chunks[32][32];
            /// Vector of timestamps. [X >> 9][Z >> 9]
            int timestamps[32][32];

            /// Temporary block of memory for NBT R/W.
            std::vector<char> IOBlock;
            /// Index for temporary block of memory for NBT R/W. -1 when not in use.
            int IOBlockIndex;

        public:

            /*-----------------Con/De-structor-----------------*/
            /**
             * Initializes the region. Will call load().
             *
             * If region does not exist, will fail to
             * load (all chunks will be empty.)
             * @todo Add a link to a document describing the region system.
             *
             * @param world Name (path to) world.
             * @param x x position of region. (chunkX >> 5; x >> 9).
             * @param z z position of region. (chunkZ >> 5; z >> 9).
             */
            RegionLoader(std::string world,int x, int z);

            /**
             * Basic destructor. Does not call save().
             *
             * Will free all memory blocks associated with
             * chunks.
             */
            virtual ~RegionLoader();

            /*-----------------Basic getter/setters-----------------*/
            /**
             * Gets the X position of the region.
             *
             * X positions of regions are proper X >> 9.
             * There are 16 blocks / chunk, and 32 chunks / region.
             *
             * @return X position of region. (X >> 9.)
             */
            int getXPos() const;

            /**
             * Gets the Z position of the region.
             *
             * Z positions of regions are proper Z >> 9.
             * There are 16 blocks / chunk, and 32 chunks / region.
             *
             * @return Z position of region. (Z >> 9.)
             */
            int getZPos() const;

            /**
             * Gets the path/world name that the region belongs to.
             *
             * @return name of world / path to world file.
             */
            std::string getWorld() const;

            /*-----------------File I/O functions-----------------*/
            /**
             * Attempts to read in (update) the file system's region
             * file.
             *
             * If file does not exist, this sets all chunks to
             * default (empty.) This will not decompress, only read
             * in and store all of the data in a region file. (this
             * makes all the data available to getChunk().
             *
             * @throw Error if region file is invalid.
             */
            void load() throw(NBTErr);

            /**
             * Attempts to save out (update) the file system's region
             * file.
             *
             * Will override old one. This deals with all 1024
             * chunks and should work in the proper format.
             *
             * @throw Error if file I/O problem.
             */
            void save() throw(NBTErr);

            /*-----------------Chunk/Timestamp interface-----------------*/
            /**
             * Returns the NBT structure associated with the given chunk.
             *
             * This decompresses the stored blocks. If chunk is not
             * yet available, this will return an empty chunk structure.
             * All made of air. Timestamp will be 0.
             *
             * @param x X position of the chunk.
             * @param z Z position of the chunk.
             * @throw Error if corrupt block of memory.
             * @return pointer to chunk's NBT structure.
             */
            Tag* getChunk(int x, int z) throw(NBTErr);

            /**
             * Returns the saved timestamp for the chunk.
             *
             * If chunk is not yet generated, this will be 0.
             *
             * @param x X position of the chunk.
             * @param z Z position of the chunk.
             * @return timeStamp for last edit.
             */
            int getChunkTimestamp(int x, int z) const;

            /**
             * Writes out the tag to a block, compresses, and updates
             * the timestamp.
             *
             * @param inChunk Pointer to chunk's NBT structure.
             * @param x x of the chunk. (x >> 9)
             * @param z z of the chunk. (z >> 9)
             * @param timestamp timestamp (defaults to current time.)
             * @throw Throws if nbt writing/compression error.
             */
            void putChunk(Tag* inChunk, int x, int z, int timestamp=0) throw(NBTErr);

            /**
             * Sets the timestamp to current time.
             *
             * @param x x of chunk. (x >> 9)
             * @param z z of chunk. (z >> 9)
             */
            void updateTimestamp(int x, int z);

            /*-----------------Base Block Functions-----------------*/

            /**
             * Reads one byte from the current chunk.
             *
             * Required for NBT::Block interface.
             *
             * @return Next byte.
             * @throw Error if OOR.
             */
            char readByte() throw(NBTErr);

            /**
             * Peeks the next byte from the current chunk.
             *
             * Required for NBT::Block interface.
             *
             * @throw Error if OOR.
             * @return Next byte.
             */
            char peekByte() throw(NBTErr);

            /**
             * Writes one byte to the current chunk.
             *
             * Required for NBT::Block interface.
             *
             * @param out Byte to write out.
             */
            void writeByte(const char out) throw(NBTErr);

            /*-----------------Misc-----------------*/

            /**
             * Returns an empty (uninitialized) chunk
             * NBT structure.
             *
             * Default one sets chunk to air.
             *
             * @param x X position of chunk.
             * @param z Z position of chunk.
             */
            virtual Tag* getEmptyChunkNBT(int x, int z);
    };
}

#endif // REGIONLOADER_H_INCLUDED

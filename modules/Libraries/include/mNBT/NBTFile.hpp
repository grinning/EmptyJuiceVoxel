/*#**************************************************#*
 * mNBT  :  NBT manipulation system by Manearrior     *
 *#**************************************************#*/

/**
 * @file
 * Holds regular NBTFile loader.
 *
 */
#ifndef NBTFILE_H_INCLUDED
#define NBTFILE_H_INCLUDED

#include <vector>

#include "Block.h"
#include "Tag.h"

/// mNBT system namespace.
namespace mNBT
{
    /**
     * Basic NBT file loader.
     *
     * Loads and saves zlib zipped NBT files.
     * This includes .schematic and .dat files.
     * Implements Block to allow Tags to read/write.
     *
     * @see Block
     */
    class NBTFile : public Block
    {
        protected:
            ///Byte block that holds the data. Used for both I/O.
            std::vector<char> data;
            ///Index for reading. All writting is done to back of data.
            unsigned int index;
        public:

            /*-----------------Con/De-structor-----------------*/
            /**
             * Constructor, sets index to 0.
             */
            NBTFile(): index(0) {}

            /**
             * Constructor, automatically attempts to load file.
             * @param in Name of file to load in.
             * @throw Error if zlib inflate failure/file problem.
             */
            NBTFile(const std::string in) throw(NBTErr) {loadFile(in);}

            /**
             * Basic destructor.
             *
             * vector<char> cleans up after itself.
             */
            virtual ~NBTFile() {}

            /*-----------------Base functions-----------------*/

            /**
             * Reads next byte from the uncompressed file.
             *
             * @throw Error if OOR.
             * @return byte at index.
             */
            char readByte() throw(NBTErr);

            /**
             * Peeks next byte from uncompressed file.
             *
             * @throw Error if OOR.
             * @return byte at index.
             */
            char peekByte() throw(NBTErr);

            /**
             * Writes one byte to the end of data block.
             *
             * @throw Nothing. Simply inherited from interface.
             * @param out Character to write.
             */
            void writeByte(const char out) throw(NBTErr);

            /*-----------------File I/O Functions-----------------*/
            /**
             * Loads a zipped NBT file into the data block.
             *
             * Allows Tags to read in. Automatically decompresses.
             *
             * @throw Error if file input or ZLIB error.
             * @param in Path of file to load.
             */
            void loadFile(const std::string &in) throw(NBTErr);

            /**
             * Saves current data block into compressed file.
             *
             * @throw Error if file output or ZLIB error.
             * @param out Path of file location to save to.
             */
            void saveFile(const std::string &out) throw(NBTErr);

            /**
             * Clears the data block and resets index.
             */
            void clear();
    };
}
#endif // NBTFILE_H_INCLUDED

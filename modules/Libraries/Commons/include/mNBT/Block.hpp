/*#**************************************************#*
 * mNBT  :  NBT manipulation system by Manearrior     *
 *#**************************************************#*/

/**
 * @file
 * NBT I/O block interface.
 *
 * Provides an interface for the NBT tags to read/write
 * bytes from. Automatically corrects from NBT's big-endian
 * to whatever endian the containing system implements.
 *
 * @see NBT/NBTFile.h
 */
#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <stdint.h>

#include "NBTErr.hpp"

/// mNBT system namespace.
namespace mNBT
{
	/**
	 * Data block interface for NBT tag reading/writing.
	 *
	 * Provides for basic read/write/peek functions, otherwise
	 * bare. Includes >> and << operators for different
	 * datatypes based on the readByte and writeByte methods.
	 * NBTFile is a basic implementation of this.
	 *
	 * @see NBTFile
	 * @see RegionLoader
	 */
	class Block
	{
		public:

			/*-----------------Con/De-structor-----------------*/
			/**
			 * Initializes a block.
			 */
			Block() {}

			/**
			 * Destroys a block.
			 */
			virtual ~Block() {}

			/*-----------------Base functions-----------------*/
			/**
			 * Reads one byte from the block.
			 * Required for >> operators to function.
			 *
			 * @return Next byte.
			 * @throw Error if OOR.
			 */
			virtual char readByte() throw(NBTErr) =0;

			/**
			 * Peeks the next byte from the block.
			 *
			 * Required for certain Tags. (Compound, for
			 * one.) Required for implementations.
			 *
			 * @throw Error if OOR.
			 * @return Next byte.
			 */
			virtual char peekByte() throw(NBTErr)=0;

			/**
			 * Writes one byte to the output stream.
			 *
			 * The implementation is unregulated. Required for
			 * implementations, as is base of operator<<.
			 *
			 * @param out Byte to write out.
			 */
			virtual void writeByte(const char out) throw(NBTErr)=0;

			/*-----------------Reading functions-----------------*/

			/**
			 * Reads one byte to the given character reference.
			 *
			 * To save time while coding Block implementations,
			 * this uses the readByte method.
			 *
			 * @param out Character to write next byte out to.
			 * @throw Error if getByte throws, usually due to OOR.
			 */
			void operator>>(char &out) throw(NBTErr);

			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses getByte().
			 *
			 * @param out int16_t to write out to.
			 * @throw Error if getByte throws, usually due to OOR.
			 */
			void operator>>(int16_t &out) throw(NBTErr);
			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses getByte().
			 *
			 * @param out int32_t to write out to.
			 * @throw Error if getByte throws, usually due to OOR.
			 */
			void operator>>(int32_t &out) throw(NBTErr);
			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses getByte().
			 *
			 * @param out int64_t to write out to.
			 * @throw Error if getByte throws, usually due to OOR.
			 */
			void operator>>(int64_t &out) throw(NBTErr);

			/**
			 * Reads a float. Runs operator>>(int32_t) and then casts
			 * to a float.
			 *
			 * @param out Float to write out to.
			 */
			void operator>>(float &out) throw(NBTErr);
			/**
			 * Reads a float. Runs operator>>(int64_t) and then casts
			 * to a float.
			 *
			 * @param out Double to write out to.
			 */
			void operator>>(double &out) throw(NBTErr);

			/**
			 * Uses getByte and >>(Short) to read in NBT style
			 * strings.
			 *
			 * @param out String to write to.
			 */
			void operator>>(std::string &out) throw (NBTErr);

			/*-----------------Writing functions-----------------*/

			/**
			 * Writes one byte from the given character reference.
			 *
			 * To save time while coding Block implementations,
			 * this uses the writeByte method.
			 *
			 * @param in Character to write out.
			 * @throw Error if writeByte throws, usually very bad.
			 */
			void operator<<(const char &in) throw(NBTErr);

			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses writeByte().
			 */
			void operator<<(const int16_t &in) throw(NBTErr);
			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses writeByte().
			 */
			void operator<<(const int32_t &in) throw(NBTErr);
			/**
			 * Automatically compensates for big-endian
			 * NBT format. Uses writeByte().
			 */
			void operator<<(const int64_t &in) throw(NBTErr);
			/**
			 * Writes a float. Casts then runs operator<<(int32_t).
			 */
			void operator<<(const float &in) throw(NBTErr);
			/**
			 * Writes a float. Casts then runs operator<<(int64_t).
			 */
			void operator<<(const double &in) throw(NBTErr);

			/**
			 * Uses <<(short) and writeByte() to write NBT style
			 * strings.
			 */
			void operator<<(const std::string &in) throw(NBTErr);
	};
}
#endif // BLOCK_H_INCLUDED

/*#**************************************************#*
 * mNBT  :  NBT manipulation system by Manearrior     *
 *#**************************************************#*/

/**
 * @file
 * Holds NBTErr, the basic MNBT exception.
 *
 * Used for all library exceptions. Includes
 * reason for failure.
 */
#ifndef NBTERR_H_INCLUDED
#define NBTERR_H_INCLUDED

#include <string>

/// mNBT system namespace.
namespace mNBT
{
	/**
	 * Basic MNBT specific exception.
	 *
	 * Failures usually are caused by OOR problems
	 * on reading/writing tags or reading/writing files.
	 * Methods that throw should write an error message.
	 * Used by Block, Tag, and NBTFile.
	 */
	class NBTErr
	{
		private:
			/**
			 * THOU SHALT NOT MAKE A NAMELESS EXCEPTION.
			 */
			NBTErr() {}

		protected:
			///Reason for exception.
			std::string msg;

		public:

			/*-----------------Con/De-structor-----------------*/
			/**
			 * Basic constructor. Requires a reason for
			 * the exception.
			 *
			 * @param reason Reason for the exceptoin.
			 */
			NBTErr(std::string reason=""): msg(reason) {}

			/**
			 * Basic destructor.
			 *
			 * -Probably- unnecessary to be virtual.
			 * Still, THOU SHALT NOT MAKE NON-VIRTUAL
			 * DESTRUCTORS.
			 */
			virtual ~NBTErr() {}

			/*-----------------Reason function.-----------------*/
			/**
			 * Gives the reason for an exception.
			 *
			 * @return Reason for exception.
			 */
			std::string getReason() const {return msg;}
	};

}
#endif // NBTERR_H_INCLUDED

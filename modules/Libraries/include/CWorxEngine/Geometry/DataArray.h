/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Data Array : Array to store arbitrary data of an
 arbitrary data type in shared memory.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __DATA_ARRAY_H__
#define __DATA_ARRAY_H__

#include "Hardware/HardwareBuffer.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Array to store arbitrary data of any arbitrary type on the GPU
        class CWE_DLL DataArray : private Hardware::Buffer
        {
            //-----------------------------------------------------------------------
            protected:
                // Properties
                const unsigned short _elementSize; // in bytes

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param elementSize   Size of a single elements in bytes.
                 * \param bufferType    The type of buffer to use internally.
                 * \param bufferUsage   The usage of the buffer to use internally.
                 *
                 * Allocates no memory on the GPU at construction.
                 *
                 ***********************************************/
                DataArray(unsigned short elementSize, const Type &bufferType, const Usage &bufferUsage = USAGE_STATIC_WRITE);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param elementSize   Size of a single elements in bytes.
                 * \param numElements   The number of elements to allocate.
                 * \param bufferType    The type of buffer to use internally.
                 * \param bufferUsage   The usage of the buffer to use internally.
                 *
                 * Directly allocates memory on the GPU.
                 *
                 ***********************************************/
                DataArray(unsigned short elementSize, unsigned int numElements, const Type &bufferType, const Usage &bufferUsage = USAGE_STATIC_WRITE);

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                DataArray(DataArray &array);

                /********************************************//**
                 * \brief Fetch the type of the hardware buffer in use
                 *
                 * \return Type of the buffer in use.
                 *
                 ***********************************************/
                const Buffer::Type &getBufferType() const;

                /********************************************//**
                 * \brief Fetch the usage of the hardware buffer in use
                 *
                 * \return Usage of the buffer in use.
                 *
                 ***********************************************/
                const Buffer::Usage &getBufferUsage() const;

                /********************************************//**
                 * \brief Fetch the size of a single element in bytes
                 *
                 * \return Size of a single element in bytes
                 *
                 ***********************************************/
                unsigned short getElementSize() const;

                /********************************************//**
                 * \brief Fetch the number of elements stored
                 *
                 * \return The number of elements stored.
                 *
                 ***********************************************/
                unsigned int getNumElements() const;

                /********************************************//**
                 * \brief Fetch the number of bytes stored
                 *
                 * \return The number of bytes stored.
                 *
                 ***********************************************/
                unsigned int getNumBytes() const;

                /********************************************//**
                 * \brief Reads data from the array
                 *
                 * \param data          A pointer to the data to fill with the read data.
                 * \param numElements   The number of elements to read (0 = to end of array).
                 * \param offset        The offset (in elements) to read from.
                 * \return The number of elements read.
                 *
                 ***********************************************/
                unsigned int read(void *data, unsigned int numElements = 0, unsigned int offset = 0);

                /********************************************//**
                 * \brief Writes data to the array.
                 *
                 * \param data          A pointer to the data to write.
                 * \param numElements   The number of elements to write (0 = to end of array).
                 * \param offset        The offset in the buffer (in elements) to write to.
                 * \return The number of elements written.
                 *
                 ***********************************************/
                unsigned int write(const void *data, unsigned int numElements = 0, unsigned int offset = 0);

                /********************************************//**
                 * \brief Copies the data to another array
                 *
                 * \param dest          The buffer to copy data to (may be itself).
                 * \param numElements   The number of elements to copy (0 = to end of array).
                 * \param readOffset    The offset within this array (in elements) to read from.
                 * \param writeOffset   The offset within dest (in elements of dest) to write to.
                 * \return The number of elements copied.
                 *
                 * Copies data from this array to the given array, both the pointers will be disabled.
                 * The given array may be this array as long as the read and write ranges don't overlap.
                 *
                 ***********************************************/
                unsigned int copy(DataArray &dest, unsigned int numElements = 0, unsigned int readOffset = 0, unsigned int writeOffset = 0);

                /********************************************//**
                 * \brief Enables a mapped pointer to the array to directly read/write
                 *
                 * \param access        Access specifier to map the pointer with.
                 * \param numElements   The length to map to the pointer, in elements (= 0 indicates the entire buffer).
                 * \param offset        The offset in the array to begin mapping, in elements.
                 * \return The pointer pointing to the mapped buffer, can be 0 if failed.
                 *
                 * Allows the user to iterate over the array as if it were a regular C array.
                 *
                 ***********************************************/
                void *enablePointer(const Access &access = ACCESS_WRITE_READ, unsigned int numElements = 0, unsigned int offset = 0);

                /********************************************//**
                 * \brief Returns the mapped pointer to the array
                 *
                 * \return The pointer pointing to the mapped array, can be 0 if inactive.
                 *
                 ***********************************************/
                void *getPointer();

                /********************************************//**
                 * \brief Disables the mapped pointer
                 *
                 * \return void
                 *
                 ***********************************************/
                void disablePointer();

                /********************************************//**
                 * \brief Reallocates memory with a new size and usage
                 *
                 * \param numElements   The number of elements to allocate.
                 * \param usage         The usage of the buffer to use internally.
                 * \return Whether the memory could be allocated or not.
                 *
                 * Reallocates the internal buffer with a new size and usage, all old data is lost.
                 *
                 ***********************************************/
                bool reallocate(unsigned int numElements, const Usage &usage = USAGE_CURRENT);

                /********************************************//**
                 * \brief Fetch the hardware buffer the data array is located in
                 *
                 * \return The hardware buffer the data array is located in (0 if no hardware buffer is in use).
                 *
                 ***********************************************/
                inline const CWE::Hardware::Buffer &getBuffer() const { return static_cast<const Buffer&>(*this); }
                inline CWE::Hardware::Buffer &getBuffer() { return static_cast<Buffer&>(*this); }
        };
    }
}

#endif

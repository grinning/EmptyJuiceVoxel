/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Buffer : Buffer stored in the GPU

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_BUFFER_H__
#define __HARDWARE_BUFFER_H__

#include "CWorxConsole.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Buffer to store arbitrary data on the GPU
        class CWE_DLL Buffer : public HardwareBase
        {
            //-----------------------------------------------------------------------
            public:
                // Define possible buffer types
                enum Type
                {
                    TYPE_INDEX_BUFFER       = GL_ELEMENT_ARRAY_BUFFER,
                    TYPE_VERTEX_BUFFER      = GL_ARRAY_BUFFER,
                    TYPE_ATTRIBUTE_BUFFER   = GL_ARRAY_BUFFER
                };

                // Define possible buffer usages
                enum Usage
                {
                    USAGE_DYNAMIC_COPY  = GL_DYNAMIC_COPY,
                    USAGE_DYNAMIC_READ  = GL_DYNAMIC_READ,
                    USAGE_DYNAMIC_WRITE = GL_DYNAMIC_DRAW,

                    USAGE_STATIC_COPY   = GL_STATIC_COPY,
                    USAGE_STATIC_READ   = GL_STATIC_READ,
                    USAGE_STATIC_WRITE  = GL_STATIC_DRAW,

                    USAGE_STREAM_COPY   = GL_STREAM_COPY,
                    USAGE_STREAM_READ   = GL_STREAM_READ,
                    USAGE_STREAM_WRITE  = GL_STREAM_DRAW,

                    // For reallocating
                    USAGE_CURRENT = 0
                };

                // Define possible buffer access methods
                enum Access
                {
                    ACCESS_WRITE                = GL_MAP_WRITE_BIT,
                    ACCESS_WRITE_INVALIDATE     = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT,
                    ACCESS_WRITE_INVALIDATE_ALL = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT,
                    ACCESS_WRITE_READ           = GL_MAP_WRITE_BIT | GL_MAP_READ_BIT,
                    ACCESS_READ                 = GL_MAP_READ_BIT
                };

            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Type _type;
                unsigned int _size;
                Usage _usage;

                // Mapping
                void *_bufferPntr;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type  The type to generate.
                 * \param usage How the user is going to use the buffer (cannot be USAGE_CURRENT).
                 *
                 * Constructs the buffer without allocating memory.
                 *
                 ***********************************************/
                Buffer(const Type &type, const Usage &usage = USAGE_STATIC_READ);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type  The type to generate.
                 * \param size  Size of the buffer in bytes.
                 * \param data  Data to put in the buffer.
                 * \param usage How the user is going to use the buffer (cannot be USAGE_CURRENT).
                 *
                 * Constructs the buffer with a specific fixed size. Data input is optional.
                 *
                 ***********************************************/
                Buffer(const Type &type, unsigned int size, const void *data = 0, const Usage &usage = USAGE_STATIC_READ);

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                Buffer(Buffer &buff);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Buffer();

                /********************************************//**
                 * \brief Reallocates memory with a new size and usage
                 *
                 * \param size  Size of the buffer in bytes.
                 * \param data  Data to put in the buffer.
                 * \param usage How the user is going to use the buffer (use USAGE_CURRENT to set it to the current usage).
                 * \return Whether the memory could be allocated or not.
                 *
                 * Reallocates the buffer with a new size and usage, all old data is lost.
                 *
                 ***********************************************/
                bool reallocate(unsigned int size, const void *data = 0, const Usage &usage = USAGE_CURRENT);

                /********************************************//**
                 * \brief Fetch whether memory is allocated or not
                 *
                 * \return Whether memory is allocatd or not.
                 *
                 ***********************************************/
                bool isAllocated() const;

                /********************************************//**
                 * \brief Manually bind the buffer
                 *
                 * \return void
                 *
                 * Binds the buffer as the active buffer to read from while rendering.
                 *
                 ***********************************************/
                void bind() const;

                /*******************************************//**
                 * \brief Fetch the type of the buffer
                 *
                 * \return The type of the buffer.
                 *
                 ***********************************************/
                const Type &getType() const;

                /********************************************//**
                 * \brief Fetch the size of the buffer in bytes
                 *
                 * \return The size of the buffer in bytes.
                 *
                 ***********************************************/
                unsigned int getSize() const;

                /********************************************//**
                 * \brief Fetch the usage of the buffer
                 *
                 * \return The usage of the buffer.
                 *
                 ***********************************************/
                const Usage &getUsage() const;

                /********************************************//**
                 * \brief Reads data from the buffer
                 *
                 * \param size      The size of the data to read in bytes.
                 * \param data      A pointer to the data to fill with the buffer.
                 * \param offset    The offset in bytes to read from.
                 * \return The number of bytes read.
                 *
                 * Fills a user defined array with specified data from the buffer, the pointer will be disabled.
                 *
                 ***********************************************/
                unsigned int read(unsigned int size, void *data, unsigned int offset = 0);

                /********************************************//**
                 * \brief Writes data to the buffer
                 *
                 * \param size      The size of the data in bytes.
                 * \param data      A pointer to the data to fill the buffer with.
                 * \param offset    The offset in bytes to write to.
                 * \return The number of bytes written.
                 *
                 * Fills a specified area of the buffer with a user defined array, the pointer will be disabled.
                 *
                 ***********************************************/
                unsigned int write(unsigned int size, const void *data, unsigned int offset = 0);

                /********************************************//**
                 * \brief Copies the data to another buffer
                 *
                 * \param size          The size of the data in bytes.
                 * \param dest          The buffer to copy data to (may be itself).
                 * \param readOffset    The offset within this buffer to read from.
                 * \param writeOffset   The offset within dest to write to.
                 * \return The number of bytes copied.
                 *
                 * Copies data from this buffer to the given buffer, both the pointers will be disabled.
                 * The given buffer may be this buffer as long as the read and write ranges don't overlap.
                 *
                 ***********************************************/
                unsigned int copy(unsigned int size, Buffer &dest, unsigned int readOffset = 0, unsigned int writeOffset = 0);

                /********************************************//**
                 * \brief Enables a mapped pointer to the buffer object to directly read/write
                 *
                 * \param access    Access specifier to map the pointer with.
                 * \param length    The length to map to the pointer, in bytes (= 0 indicates the entire buffer).
                 * \param offset    The offset in the buffer to begin mapping.
                 * \return The pointer pointing to the mapped buffer, can be 0 if failed.
                 *
                 * Allows the user to iterate over the buffer as if it were a regular array.
                 *
                 ***********************************************/
                void *enablePointer(const Access &access = ACCESS_WRITE_READ, unsigned int length = 0, unsigned int offset = 0);

                /********************************************//**
                 * \brief Returns the mapped pointer to the buffer object
                 *
                 * \return The pointer pointing to the mapped buffer, can be 0 if inactive.
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
        };
    }
}

#endif

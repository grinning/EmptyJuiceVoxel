/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Object : Stores all the states to draw an object
 in the GPU, independent of the shading program.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_OBJECT_H__
#define __HARDWARE_OBJECT_H__

#include "Hardware/HardwareBuffer.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Stores all the states to draw an object independent of the shading
        class CWE_DLL Object : public HardwareBase
        {
            //-----------------------------------------------------------------------
            public:
                // Define (vertex) Attribute data types
                enum AttributeType
                {
                    BYTE            = GL_BYTE,
                    SHORT           = GL_SHORT,
                    INT             = GL_INT,
                    UNSIGNED_BYTE   = GL_UNSIGNED_BYTE,
                    UNSIGNED_SHORT  = GL_UNSIGNED_SHORT,
                    UNSIGNED_INT    = GL_UNSIGNED_INT,
                    FLOAT           = GL_FLOAT,
                    DOUBLE          = GL_DOUBLE
                };

                // Returns the size of an attribute type
                static unsigned short getAttributeTypeSize(const AttributeType &type);

                //-----------------------------------------------------------------------
                // Define Primitive types
                enum PrimitiveType
                {
                    PRIMITIVE_POINTS            = GL_POINTS,

                    PRIMITIVE_LINES             = GL_LINES,
                    PRIMITIVE_LINE_STRIP        = GL_LINE_STRIP,
                    PRIMITIVE_LINE_LOOP         = GL_LINE_LOOP,

                    PRIMITIVE_TRIANGLES         = GL_TRIANGLES,
                    PRIMITIVE_TRIANGLE_STRIP    = GL_TRIANGLE_STRIP,
                    PRIMITIVE_TRIANGLE_FAN      = GL_TRIANGLE_FAN,

                    // For primitive picking
                    PRIMITIVE_ANY = 0
                };

                // Define Index data types
                enum IndexType
                {
                    INDEX_UNSIGNED_BYTE     = GL_UNSIGNED_BYTE,
                    INDEX_UNSIGNED_SHORT    = GL_UNSIGNED_SHORT,
                    INDEX_UNSIGNED_INT      = GL_UNSIGNED_INT
                };

                // Returns the size of an index type
                static unsigned short getIndexTypeSize(const IndexType &type);

            //-----------------------------------------------------------------------
            protected:
                // Define Geometry (draw command)
                struct Geometry
                {
                    // Primitives
                    PrimitiveType primitiveType;

                    // Indices
                    IndexType indexType;
                    unsigned int count;  // elements
                    unsigned int offset; // bytes
                };

                // Define a list of primitives
                typedef std::list<Geometry> GeometryList;

                // Define Geometry ordered by id
                typedef std::map<const unsigned int, GeometryList> GeometryMap;

                //-----------------------------------------------------------------------
                // Stored Geometry
                GeometryMap _geometry;
                Buffer *_indexBuffer;

            //-----------------------------------------------------------------------
            private:
                // Private Copy Constructor to prevent it
                Object(const Object &obj);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                Object();

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Object();

                /********************************************//**
                 * \brief Adds a (vertex) attribute to the object
                 *
                 * \param location  The location to attach to the attribute.
                 * \param buff      The vertex buffer that stores this attribute.
                 * \param size      The size of the attribute in components, must be between 1 and 4.
                 * \param type      Attribute Type of every single component.
                 * \param stride    Byte offset of consecutive attributes.
                 * \param offset    Offset of the first attribute (in bytes).
                 * \return Whether the attribute was successfully added or not.
                 *
                 * Tells the Object where to find a specific attribute in a specific buffer.
                 *
                 ***********************************************/
                bool addAttribute(unsigned int location, const Buffer &buff, unsigned short size, const AttributeType &type, unsigned short stride = 0, unsigned int offset = 0);

                /********************************************//**
                 * \brief Fetch the size of an attribute
                 *
                 * \param location  The location of the attribute to search for.
                 * \return The size of the attribute in components, between 1 and 4.
                 *
                 ***********************************************/
                unsigned short getAttributeSize(unsigned int location) const;

                /********************************************//**
                 * \brief Fetch the type of an attribute
                 *
                 * \param location  The location of the attribute to search for.
                 * \return The attribute type of every single component.
                 *
                 ***********************************************/
                AttributeType getAttributeType(unsigned int location) const;

                /********************************************//**
                 * \brief Fetch the stride of an attribute
                 *
                 * \param location  The location of the attribute to search for.
                 * \return The byte offset of consecutive attributes.
                 *
                 ***********************************************/
                unsigned short getAttributeStride(unsigned int location) const;

                /********************************************//**
                 * \brief Fetch whether it has a given attribute or not
                 *
                 * \param location  The location of the attribute to search for.
                 * \return Whether the attribute was found or not.
                 *
                 ***********************************************/
                bool hasAttribute(unsigned int location) const;

                /********************************************//**
                 * \brief Removes a (vertex) attribute from the object
                 *
                 * \param location  The location of the attribute to remove.
                 * \return Whether the attribute was successfully removed or not.
                 *
                 ***********************************************/
                bool removeAttribute(unsigned int location);

                /********************************************//**
                 * \brief Adds geometry to the object
                 *
                 * \param id        The id to put this geometry under.
                 * \param type      The type of the geometry to render.
                 * \param indexType Type of indices to read from the index buffer.
                 * \param count     The number of elements to render.
                 * \param offset    The offset in the index buffer to start at (in bytes).
                 * \return Whether the geometry was successfully added or not.
                 *
                 ***********************************************/
                bool addGeometry(unsigned int id, const PrimitiveType &type, const IndexType &indexType, unsigned int count, unsigned int offset = 0);

                /********************************************//**
                 * \brief Returns whether a certain geometry id exists
                 *
                 * \param id    The id to search for.
                 * \return Whether the geometry exists or not.
                 *
                 ***********************************************/
                bool hasGeometry(unsigned int id) const;

                /********************************************//**
                 * \brief Returns the number of geometry calls within an id
                 *
                 * \param id    The id to count.
                 * \return The number of geometry found under the specific id.
                 *
                 ***********************************************/
                unsigned int getNumGeometry(unsigned int id) const;

                /********************************************//**
                 * \brief Returns the number of geometry ids (not geometry itself)
                 *
                 * \return Number of geometry IDs counted.
                 *
                 ***********************************************/
                unsigned int getNumGeometryIDs() const;

                /********************************************//**
                 * \brief Removes all geometry from a certain id
                 *
                 * \param id    The id to remove.
                 * \return Whether the geometry ID was successfully removed or not.
                 *
                 ***********************************************/
                bool removeGeometry(unsigned int id);

                /********************************************//**
                 * \brief Draws a given geometry ID
                 *
                 * \param id    The id to draw.
                 * \param prim  Primitive type to exclusively render, use PRIMITIVE_ANY to render all types.
                 * \return Whether the ID was successfully drawn or not.
                 *
                 ***********************************************/
                bool drawGeometryID(unsigned int id, const PrimitiveType &prim = PRIMITIVE_ANY) const;

                /********************************************//**
                 * \brief Binds the index buffer to use (indices to attributes)
                 *
                 * \param buff  The buffer to use as index buffer.
                 * \return Whether the buffer was successfully bound or not.
                 *
                 ***********************************************/
                bool bindIndexBuffer(const Buffer &buff);
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Mesh : Stores all the states and data to draw a geometry
 mesh in the GPU.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MESH_H__
#define __MESH_H__

#include "Geometry/DataArray.h"
#include "Hardware/HardwareObject.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Stores all the states to draw polygons
        class CWE_DLL Mesh : private Hardware::Object
        {
            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Object::IndexType _indexType;
                DataArray *_indexArray;
                DataArray *_vertexArray;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param numVertices       The number of vertices to store.
                 * \param vertexByteSize    Size of a single vertex in bytes.
                 * \param numIndices        The number of indices to store.
                 * \param indexType         The type of the indices to store.
                 * \param dynamicVertices   If true, vertex buffer storage is assumed to be written to often.
                 * \param dynamicIndices    If true, index buffer storage is assumed to be written to often.
                 *
                 ***********************************************/
                Mesh(unsigned int numVertices, unsigned short vertexByteSize, unsigned int numIndices, const Object::IndexType &indexType,
                     bool dynamicVertices = false, bool dynamicIndices = false);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Mesh();

                /********************************************//**
                 * \brief Fetch the size of a single vertex in bytes
                 *
                 * \return The size of a single vertex in bytes.
                 *
                 ***********************************************/
                inline unsigned short getVertexByteSize() const { return _vertexArray->getElementSize(); }

                /********************************************//**
                 * \brief Fetch the number of vertices
                 *
                 * \return The number of vertices.
                 *
                 ***********************************************/
                inline unsigned int getNumVertices() const { return _vertexArray->getNumElements(); }

                /********************************************//**
                 * \brief Fetch the number of indices
                 *
                 * \return The number of indices.
                 *
                 ***********************************************/
                inline unsigned int getNumIndices() const { return _indexArray->getNumElements(); }

                /********************************************//**
                 * \brief Fetch the type of the indices stored
                 *
                 * \return The type of indices stored.
                 *
                 ***********************************************/
                inline const Hardware::Object::IndexType &getIndexType() const { return _indexType; }

                /********************************************//**
                 * \brief Add (vertex) attribute to the mesh
                 *
                 * \param location  The location of the attribute (should be defined by shaders).
                 * \param size      The size of the attribute in components.
                 * \param type      Type of every single component.
                 * \param offset    Offset of the first attribute in a single vertex (in bytes).
                 * \return Whether the attribute could be added or not.
                 *
                 ***********************************************/
                bool addAttribute(unsigned int location, unsigned short size, const Object::AttributeType &type, unsigned short offset);

                /********************************************//**
                 * \brief Removes a (vertex) attribute from the mesh
                 *
                 * \param location  The location of the attribute to remove (should be defined by shaders).
                 * \return Whether the attribute could be removed or not.
                 *
                 ***********************************************/
                inline bool removeAttribute(unsigned int location) { return Object::removeAttribute(location); }

                /********************************************//**
                 * \brief Adds geometry assigned to a id to render
                 *
                 * \param id        Which id the geometry falls under (determines its shader).
                 * \param type      The type of the geometry to render.
                 * \param count     The number of elements to render.
                 * \param offset    The offset in the index buffer to start at (in elements).
                 * \return Whether the geometry could be added or not.
                 *
                 ***********************************************/
                bool addGeometry(unsigned int id, const Object::PrimitiveType &type, unsigned int count, unsigned int offset = 0);

                /********************************************//**
                 * \brief Returns whether a certain geometry ID exists
                 *
                 * \param id      The ID to search for.
                 * \return Whether the given ID exists.
                 *
                 ***********************************************/
                inline bool hasGeometry(unsigned int id) const { return Object::hasGeometry(id); }

                /********************************************//**
                 * \brief Fetch the number of geometry calls within an ID
                 *
                 * \param id    Geometry ID to search in.
                 * \return Number of geometry calls.
                 *
                 ***********************************************/
                inline unsigned int getNumGeometry(unsigned int id) const { return Object::getNumGeometry(id); }

                /********************************************//**
                 * \brief Fetch the number of geometry IDs
                 *
                 * \return Number of geometry IDs
                 *
                 ***********************************************/
                inline unsigned int getNumGeometryIDs() const { return Object::getNumGeometryIDs(); }

                /********************************************//**
                 * \brief Removes all geometry from a certain id to render
                 *
                 * \param id  The id to remove.
                 * \return Whether the geometry could be removed or not.
                 *
                 ***********************************************/
                inline bool removeGeometry(unsigned int id) { return Object::removeGeometry(id); }

                /********************************************//**
                 * \brief Draws a given geometry ID
                 *
                 * \param id    The given ID.
                 * \param prim  Primitive type to exclusively render, use PRIMITIVE_ANY to render all types.
                 * \return Whether the ID was successfully drawn or not.
                 *
                 ***********************************************/
                inline bool drawGeometryID(unsigned int id, const Object::PrimitiveType &prim = Object::PRIMITIVE_ANY)
                    { return Object::drawGeometryID(id, prim); }

                /********************************************//**
                 * \brief Fetch the index array
                 *
                 * \return A reference to the index array.
                 *
                 ***********************************************/
                inline DataArray &indexArray() { return *_indexArray; }

                /********************************************//**
                 * \brief Fetch the vertex array
                 *
                 * \return A reference to the vertex array.
                 *
                 ***********************************************/
                inline DataArray &vertexArray() { return *_vertexArray; }
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Primitive : Generates a Mesh with a predefined 'primitive'
 shape by choice.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "Geometry/Mesh.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Generates a Mesh with a predefind primitive shape
        class CWE_DLL Primitive : public Geometry::Mesh
        {
            //-----------------------------------------------------------------------
            public:
                // Define possible primitve types
                enum Type
                {
                    TYPE_PLANE,
                    TYPE_GRID,
                    TYPE_CUBE,
                    TYPE_SPHERE
                };

            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Type _type;

                /********************************************//**
                 * \brief Fetch the amount of vertices
                 *
                 * \param type      The type of primitive to generate.
                 * \param normals   Whether to generate normals or not.
                 * \param precision Optional factor for some primitives.
                 * \return Amount of vertices.
                 *
                 ***********************************************/
                static unsigned int getNumVertices(const Type &type, bool normals, bool texcoords, unsigned short precision);

                /********************************************//**
                 * \brief Fetch the amount of indices
                 *
                 * \param type      The type of primitive to generate.
                 * \param precision Optional factor for some primitives.
                 * \return Amount of indices.
                 *
                 ***********************************************/
                static unsigned int getNumIndices(const Type &type, unsigned short precision);

                /********************************************//**
                 * \brief Fetch the bytesize of a single vertex
                 *
                 * \param normals   Whether to generate normals nor not.
                 * \param texcoords Whether to generate textur coordinates or not.
                 * \param tangent   Whether to generate tangent space or not (only has effect if normals is true).
                 * \return Vertex byte size.
                 *
                 ***********************************************/
                static unsigned short getVertexByteSize(bool normals, bool texcoords, bool tangent);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type          The type of primitive to generate.
                 * \param normals       Whether to generate normals or not.
                 * \param tangent       Whether to generate tangent space or not (only has effect if normals is true).
                 * \param textureScale  If 0, no texture coords are generated, if higher, scale will be applied.
                 * \param texcoords     Wether to generate texture coordinates or not.
                 * \param precision     Optional factor for some primitives.
                 *
                 ***********************************************/
                Primitive(const Type &type, bool normals = false, bool tangent = false, const float textureScale = 0.0f, unsigned short precision = 2);

                /********************************************//**
                 * \brief Fetch the type of the primitive
                 *
                 * \return The type of the primitive.
                 *
                 ***********************************************/
                const Type &getType() const;
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 OBJFile : Interface to parse Wavefront .obj files and
 construct a mesh from it.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __OBJ_FILE_H__
#define __OBJ_FILE_H__

#include "External/File.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // External namespace
    namespace External
    {
        //! Interface to parse Wavefront .obj files and construct a Mesh or Object
        class CWE_DLL OBJFile : public File
        {
            //-----------------------------------------------------------------------
            protected:
                // Define a face (single element = v,t,n, n = normal/tangent/bitangent)
                typedef std::vector<Math::vec3i> Face;

                // Define a render group
                struct RenderGroup
                {
                    std::string materialFile;
                    std::string materialName;
                    unsigned int start; // Start index in faces
                    unsigned int size;  // Num idices
                };

                //-----------------------------------------------------------------------
                // Storage
                std::vector<Math::vec3f> _vertices;
                std::vector<Math::vec2f> _textures;
                std::vector<Math::vec3f> _normals;
                std::vector<Math::vec3f> _tangents;
                std::vector<Math::vec3f> _bitangents;

                std::vector<Face> _faces;
                std::vector<RenderGroup> _groups;

                // Parses the file
                void parse();

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param file  The file to be parsed.
                 *
                 ***********************************************/
                OBJFile(const std::string &file);

                /********************************************//**
                 * \brief Generates normals for the mesh
                 *
                 * \param tangent       If true, tangent space vectors will be generated.
                 * \param smooth        If true, normals will be smoothed afterwards.
                 * \param smoothTexture If false, texture seems won't be smoothed.
                 * \return void
                 *
                 ***********************************************/
                void generateNormals(bool tangent = false, bool smooth = true, bool smoothTexture = true);

                /********************************************//**
                 * \brief Smooths the normals
                 *
                 * \param smoothTexture If false, texture seems won't be smoothed.
                 * \return void
                 *
                 ***********************************************/
                void smoothNormals(bool smoothTexture = true);

                /********************************************//**
                 * \brief Parses the stored content to a usable mesh
                 *
                 * \return The parsed mesh instance.
                 *
                 * Parses the stored content to a usable mesh instance, the instance will be dynamically allocated!
                 *
                 ***********************************************/
                Geometry::Mesh *getMesh() const;

                /********************************************//**
                 * \brief Parses the stored content to a usable object
                 *
                 * \return The parsed object instance.
                 *
                 * Parses the stored content to a usable object instance,
                 * the instance, its mesh and all its materials will be dynamically allocated!
                 *
                 ***********************************************/
                Object *getObject() const;
        };
    }
}

#endif

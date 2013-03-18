/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 MTLFile : Interface to parse Wavefront .mtl files and
 construct materials from it.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MTL_FILE_H__
#define __MTL_FILE_H__

#include "External/File.h"
#include "Geometry/Material.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // External namespace
    namespace External
    {
        //! Interface to parse Wavefront .mtl files and construct a Material
        class CWE_DLL MTLFile : public File
        {
            //-----------------------------------------------------------------------
            protected:
                // Define a Wavefront Texture
                struct WavTexture
                {
                    // Properties
                    std::string file;
                    unsigned int unit;

                    bool horizontalBlend;
                    bool verticalBlend;
                    bool clamp;
                };

                // Define a Wavefront Material
                struct WavMaterial
                {
                    // Properties
                    std::string name;
                    unsigned int config; // For material

                    Math::vec3f diffuse;
                    Math::vec3f specular;

                    float transparent;
                    float specularCoeff;

                    // Textures
                    std::list<WavTexture> textures;
                };

                // Define a list of materials
                typedef std::list<WavMaterial*> WavMaterialList;

                //-----------------------------------------------------------------------
                // Storage
                WavMaterialList _materials;

                // Gets rid of current materials
                void clear();

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
                MTLFile(const std::string &file);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~MTLFile();

                /********************************************//**
                 * \brief Parses the stored content to a usable material
                 *
                 * \param name          The name of the material to construct.
                 * \param smoothMipmap  If true, mipmaps will be avaraged.
                 * \return The parsed Material instance.
                 *
                 * Parses the stored content to a usable material instance, the instance will be dynamically allocated!
                 *
                 ***********************************************/
                Geometry::Material *getMaterial(const std::string &name, bool smoothMipmap = true) const;
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Materials : describes a collection of shaders to shade
 a certain object under any circumstances.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Geometry/Shader.h"
#include "Hardware/HardwareTexture.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! A collection of shaders to shade an object under any circumstances
        class CWE_DLL Material
        {
            //-----------------------------------------------------------------------
            protected:
                // Define the base for a property (which is actually stored)
                struct PropertyBase
                {
                    /********************************************//**
                     * \brief Destructor
                     ***********************************************/
                    virtual ~PropertyBase() {}

                    /********************************************//**
                     * \brief Bind the property to a shader
                     *
                     * \param uni   Uniform to bind it at.
                     * \param shad  Shader to bind it to.
                     * \return void
                     *
                     ***********************************************/
                    virtual void bind(const std::string &uni, const Shader::Shader &shad) const {}
                };

                //-----------------------------------------------------------------------
                // Define an actual property
                template <typename _type>
                struct Property : public PropertyBase
                {
                    //-----------------------------------------------------------------------
                    protected:
                        // Storage
                        const _type value;

                    //-----------------------------------------------------------------------
                    public:
                        /********************************************//**
                         * \brief Constructor
                         *
                         * \param val   Value to store.
                         *
                         ***********************************************/
                        Property(const _type &val) : value(val) {}

                        /********************************************//**
                         * \brief Destructor
                         ***********************************************/
                        virtual ~Property() {}

                        /********************************************//**
                         * \brief Bind the property to a shader
                         *
                         * \param uni   Uniform to bind it at.
                         * \param shad  Shader to bind it to.
                         * \return void
                         *
                         ***********************************************/
                        virtual void bind(const std::string &uni, const Shader::Shader &shad) const { shad.setUniform(uni, value); }
                };

                //-----------------------------------------------------------------------
                // Define a property pointing to a value
                template <typename _type>
                struct PropertyPointer : public PropertyBase
                {
                    //-----------------------------------------------------------------------
                    protected:
                        // Storage
                        const _type *value;

                    //-----------------------------------------------------------------------
                    public:
                        /********************************************//**
                         * \brief Constructor
                         *
                         * \param val   Value to store (pointer to value).
                         *
                         ***********************************************/
                        PropertyPointer(const _type *val) : value(val) {}

                        /********************************************//**
                         * \brief Destructor
                         ***********************************************/
                        virtual ~PropertyPointer() {}

                        /********************************************//**
                         * \brief Bind the property to a shader
                         *
                         * \param uni   Uniform to bind it at.
                         * \param shad  Shader to bind it to.
                         * \return void
                         *
                         ***********************************************/
                        virtual void bind(const std::string &uni, const Shader::Shader &shad) const { shad.setUniform(uni, *value); }
                };

            //-----------------------------------------------------------------------
            public:
                // Define a shader pointer, so stored pointers will automatically update
                struct Pointer
                {
                    // Material and actual pointer
                    const Material &material;
                    const Shader::Shader *shader; // Use material.use(*shader) to bind shader and material properties

                    /********************************************//**
                     * \brief Constructor
                     *
                     * \param mat   The material this pointer belongs to.
                     * \param pntr  The shader to point to.
                     *
                     ***********************************************/
                    inline Pointer(const Material &mat, const Shader::Shader *pntr) : material(mat), shader(pntr) {}

                    /********************************************//**
                     * \brief Sort two pointers in a container
                     *
                     * \param pntr  The other pointer to sort against.
                     * \return True if this precedes pntr.
                     *
                     ***********************************************/
                    bool operator<(const Pointer &pntr) const;
                };

            //-----------------------------------------------------------------------
            protected:
                // Define a list of shader pointers sorted by pass
                typedef std::map<const Shader::Pass, Pointer*> ShaderMap;

                // Define a list of properties sorted by locations
                typedef std::map<const std::string, PropertyBase*> PropertyMap;

                // Define a regular list of textures stored by unit
                typedef std::map<const unsigned int, Hardware::Texture*> TextureMap;

                // Other Properties
                ShaderMap _shaders; // The shader pointers never change once they exist!
                PropertyMap _properties;
                TextureMap _textures;

                // Material currently in use
                static Material *_inUse;

                //-----------------------------------------------------------------------
                // Define a list of texture files
                typedef std::map<const std::string, Hardware::Texture*> TextureFileMap;

                /********************************************//**
                 * \brief Loads and/or fetches a texture file to use in a shader
                 *
                 * \param file  The file to load from.
                 * \return The loaded texture, 0 if it could not be loaded.
                 *
                 ***********************************************/
                static Hardware::Texture *getTextureFile(const std::string &file);

                // Loaded textures
                static TextureFileMap _textureFiles;

                //-----------------------------------------------------------------------
                // Define a list of unique shaders
                typedef std::set<Shader::Shader*, Shader::Shader::sort> UniqueShaderMap;

                // Unique shaders and loaded Textures
                static UniqueShaderMap _uniqueShaders;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Material();

                /********************************************//**
                 * \brief Attach a shader directly for a certain pass in the material
                 *
                 * \param shad  Shader to use.
                 * \return True if it successfully attached the shader.
                 *
                 ***********************************************/
                bool attachShader(Shader::Shader &shad);

                /********************************************//**
                 * \brief Adopt a shader for a certain pass in the material
                 *
                 * \param shad  Shader to use.
                 * \return True if it successfully adopted the shader.
                 *
                 * Adopt a shader for a certain pass in the material, this will check
                 * if any equivalent shaders are stored, so no duplicates will occur.
                 * If no equivalent was found, it will store a new copy, it will never use the user passed shader.
                 *
                 ***********************************************/
                bool adoptShader(const Shader::Shader &shad);

                /********************************************//**
                 * \brief Removes a shader of a certain pass
                 *
                 * \return Whether the shader was successfully removed.
                 *
                 * Removes a shader of a certain pass, which includes textures.
                 *
                 ***********************************************/
                bool removeShader(const Shader::Pass &pass);

                /********************************************//**
                 * \brief Fetch a ShaderPointer container
                 *
                 * \param pass  The pass to fetch the ShaderPointer from.
                 * \return The ShaderPointer of the shader.
                 *
                 * Fetch a ShaderPointer container to store independent from the current shader in use.
                 * If the pass didn't exist yet it will create a default.
                 * Note this ShaderPointer should not be deleted!
                 *
                 ***********************************************/
                const Pointer *getPointer(const Shader::Pass &pass);

                /********************************************//**
                 * \brief Uses the given shader and bind the material's properties to it
                 *
                 * \param shad  The given shader to use.
                 * \return void
                 *
                 * Uses the given shader and bind the material's properties to it,
                 * meshes shall use this shader when being drawn.
                 *
                 ***********************************************/
                void use(const Shader::Shader &shad) const;

                /********************************************//**
                 * \brief Returns the configuration of a specific shader
                 *
                 * \param pass  The pass to fetch the configuration from.
                 * \return The configuration of the shader.
                 *
                 ***********************************************/
                unsigned int getConfiguration(const Shader::Pass &pass) const;

                /********************************************//**
                 * \brief Fetches whether a shader has specific configuration bits
                 *
                 * \param pass      Pass to check the configuration of.
                 * \param config    Configuration to check for.
                 * \return True if all the bits in config are set.
                 *
                 ***********************************************/
                bool hasConfiguration(const Shader::Pass &pass, unsigned int config) const;

                /********************************************//**
                 * \brief Sets the configuration of a specific shader
                 *
                 * \param pass      Passes to set the configuration for.
                 * \param config    Configuration to set.
                 * \return Whether all the configurations could be set or not.
                 *
                 * Sets the configuration for a specific shader pass. Any attached shader will be detached, unless the configuration does not change.
                 * If you want to set the configuration of an attached shader, set it through that shader directly.
                 *
                 * Note: this is expensive because of recompiling and what not!
                 *
                 ***********************************************/
                bool setConfiguration(unsigned int pass, unsigned int config);

                /********************************************//**
                 * \brief Adds a configuration to a specific shader
                 *
                 * \param pass      Passes to set the configuration for.
                 * \param config    Configuration to add.
                 * \return Whether all the configurations could be added or not.
                 *
                 * Note: this is expensive because of recompiling and what not!
                 *
                 ***********************************************/
                bool addConfiguration(unsigned int pass, unsigned int config);

                /********************************************//**
                 * \brief Removes a configuration to a specific shader
                 *
                 * \param pass      Passes to set the configuration for.
                 * \param config    Configuration to remove.
                 * \return Whether the all the configurations could be removed or not.
                 *
                 * Note: this is expensive because of recompiling and what not!
                 *
                 ***********************************************/
                bool removeConfiguration(unsigned int pass, unsigned int config);

                /********************************************//**
                 * \brief Toggles a configuration of a specific shader
                 *
                 * \param pass      Passes to set the configuration for.
                 * \param config    Configuration to toggle.
                 * \return Whether the all the configurations could be toggled or not.
                 *
                 * Note: this is expensive because of recompiling and what not!
                 *
                 ***********************************************/
                bool toggleConfiguration(unsigned int pass, unsigned int config);

                /********************************************//**
                 * \brief Sets a property of the material
                 *
                 * \param location  The property's location to set.
                 * \param value     The value to set it to.
                 * \return void
                 *
                 ***********************************************/
                template <typename _type>
                inline void setProperty(const std::string &location, _type value)
                {
                    // Create property
                    Property<_type> *prop = new Property<_type>(value);

                    // Delete any existing property of this type
                    removeProperty(location);

                    // Add new
                    _properties[location] = prop;

                    // Need to rebind
                    if(_inUse == this) _inUse = 0;
                }

                /********************************************//**
                 * \brief Sets a property of the material to point towards a value
                 *
                 * \param location  The property's location to set.
                 * \param pointer   The pointer to use.
                 * \return void
                 *
                 ***********************************************/
                template <typename _type>
                inline void setPropertyPointer(const std::string &location, _type *value)
                {
                    // Create property
                    PropertyPointer<_type> *prop = new PropertyPointer<_type>(value);

                    // Delete any existing property of this type
                    removeProperty(location);

                    // Add new
                    _properties[location] = prop;

                    // Need to rebind
                    if(_inUse == this) _inUse = 0;
                }

                /********************************************//**
                 * \brief Returns whether a certain property exists
                 *
                 * \param location  The location of the property to search for.
                 * \return Whether it has the specified property or not.
                 *
                 ***********************************************/
                bool hasProperty(const std::string &location) const;

                /********************************************//**
                 * \brief Removes a certain property
                 *
                 * \param location  The location of the property to remove.
                 * \return Whether the specified property could be removed or not.
                 *
                 ***********************************************/
                bool removeProperty(const std::string &location);

                /********************************************//**
                 * \brief Adds a texture to the material
                 *
                 * \param unit      The unit of texture to set.
                 * \param texture   The actual texture to set it to.
                 * \return Whether the texture could be added or not.
                 *
                 ***********************************************/
                bool addTexture(unsigned int unit, Hardware::Texture &texture);

                /********************************************//**
                 * \brief Adds a texture to the material
                 *
                 * \param unit  The unit of texture to set.
                 * \param file  The path and name of the file to load.
                 * \return Whether the texture could be added or not.
                 *
                 ***********************************************/
                bool addTexture(unsigned int unit, const std::string &file);

                /********************************************//**
                 * \brief Fetch whether a certain texture exists
                 *
                 * \param unit  The unit of the texture to search for.
                 * \return Whether it has the specified texture.
                 *
                 ***********************************************/
                bool hasTexture(unsigned int unit) const;

                /********************************************//**
                 * \brief Fetch the hardware texture used by the material
                 *
                 * \param unit  The unit of the texture to search for.
                 * \return The texture used for that texture unit.
                 *
                 ***********************************************/
                Hardware::Texture *getTexture(unsigned int unit) const;

                /********************************************//**
                 * \brief Removes a certain texture
                 *
                 * \param unit  The unit of the texture to remove.
                 * \return Whether the texture could be removed or not.
                 *
                 ***********************************************/
                bool removeTexture(unsigned int unit);
        };
    }
}

#endif

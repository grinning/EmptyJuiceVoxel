/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Shader : Generates GLSL shaders describing the render
 process using a type and configuration for a specific
 render pass.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __SHADER_H__
#define __SHADER_H__

#include "Hardware/HardwareProgram.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Shader namespace
    namespace Shader
    {
        //-----------------------------------------------------------------------
        // Define write/read targets (a.k.a indices)
        enum Target
        {
            // Geometry Buffers
            G_BUFFER_DIFFUSE,   // Index 0
            G_BUFFER_SPECULAR,  // Index 1
            G_BUFFER_NORMAL,    // ...

            // Light accumulator (must be last)
            LIGHT_ACCUMULATOR,

            // Count
            TARGET_COUNT
        };

        // Define different material passes
        enum Pass
        {
            PASS_GEOMETRY       = 1 << 0,
            PASS_LIGHT          = 1 << 1,
            PASS_FLAT           = 1 << 2,
            PASS_DEPTH          = 1 << 3,
            PASS_DEPTH_CUBEMAP  = 1 << 4,

            // Count
            PASS_COUNT          = 1 << 5
        };

        /********************************************//**
         * \brief Creates a default shader of a certain pass and configuration
         *
         * \param pass      The pass to create a default shader for.
         * \param config    The configuration to use.
         * \return A dynamically allocated default shader.
         *
         ***********************************************/
        CWE_DLL Shader *createDefault(const Pass &pass, unsigned int config);

        //! Base class to generate a GLSL program
        class CWE_DLL Shader : private Hardware::Program
        {
            //-----------------------------------------------------------------------
            public:
                // Define some global uniforms
                static const std::string UNIFORM_MATRIX_CAMERA;
                static const std::string UNIFORM_MATRIX_PROJECTION;
                static const std::string UNIFORM_MATRIX_NDC_TO_CLIP;
                static const std::string UNIFORM_VIEWPORT_DIMENSIONS;

            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Pass _pass;
                const unsigned int _configWidth; // Stores what bits may be set, to prevent shaders being unequal because of invalid configurations
                unsigned int _config;

                /********************************************//**
                 * \brief Sets an attribute location beforehand
                 *
                 * \param location  The location to set.
                 * \param attribute The attribute to set it to.
                 * \return Whether the location was successfully set or not.
                 *
                 * Fixes a certain attribute at a location, should be used in the compile() method.
                 * This must be done if multiple meshes should be able to use the same shader.
                 *
                 ***********************************************/
                inline bool setAttributeLocation(unsigned int location, const std::string &attribute)
                    { return Program::setAttributeLocation(location, attribute); }

                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const = 0;

                /********************************************//**
                 * \brief Fetch the #define string for a specific configuration bit.
                 *
                 * \param config    Configuration bit to fetch the string for, must be a power of 2.
                 * \return The #define string for the given configuration bit.
                 *
                 ***********************************************/
                virtual std::string getConfigDefine(unsigned int config) const = 0;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 ***********************************************/
                Shader(const Pass &pass, unsigned int configWidth, unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                Shader(const Shader &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Shader() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 * Clones the polymorphic object, up to derived classes to implement this.
                 *
                 ***********************************************/
                virtual Shader *clone() const = 0;

                /********************************************//**
                 * \brief Fetch the pass the shader participates in
                 *
                 * \return The pass the shader participates in.
                 *
                 ***********************************************/
                const Pass &getPass() const;

                /********************************************//**
                 * \brief Returns the configuration of the shader
                 *
                 * \return The configuration of the shader.
                 *
                 ***********************************************/
                unsigned int getConfiguration() const;

                /********************************************//**
                 * \brief Sets the configuration of the shader
                 *
                 * \param config    Configuration to set.
                 * \return void
                 *
                 * Sets the configuration of the shader, needs recompiling afterwards!
                 *
                 ***********************************************/
                void setConfiguration(unsigned int config);

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 * Compiles the program according to the current type and configuration, also sets attribute locations and default uniforms.
                 * Derived Shaders should set their attributes before calling base compile()
                 * and their uniforms after calling base compile().
                 *
                 ***********************************************/
                virtual bool compile();

                /********************************************//**
                 * \brief Fetch whether the shader is compiled or not.
                 *
                 * \return Whether the shader is compiled or not.
                 *
                 ***********************************************/
                bool isCompiled() const;

                /********************************************//**
                 * \brief Manually bind the shader
                 *
                 * \return Whether the shader is bound or not.
                 *
                 * Binds the shader as the active shader to use while rendering.
                 *
                 ***********************************************/
                inline bool bind() const { return Program::bind(); }

                /********************************************//**
                 * \brief Fetch whether this shader is bound or not
                 *
                 * \return Whether this shader is bound or not.
                 *
                 ***********************************************/
                bool isBound() const { return Program::isBound(); }

                /********************************************//**
                 * \brief Fetch the location of a given (vertex) attribute
                 *
                 * \param attribute The given (vertex) attribute.
                 * \return The location of the attribute, -1 if the attribute does not exist.
                 *
                 * Fetches the location of a given (vertex) attribute within the compiled program.
                 *
                 ***********************************************/
                inline int getAttributeLocation(const std::string &attribute) const
                    { return Program::getAttributeLocation(attribute); }

                /********************************************//**
                 * \brief Sets the value of an attribute
                 *
                 * \param attr  The attribute to set.
                 * \param value The value to set it to.
                 * \return Whether the attribute could be set or not.
                 *
                 ***********************************************/
                template <typename _type>
                inline void setAttribute(const unsigned int attr, _type value) const
                    { Program::setAttribute(attr, value); }

                /********************************************//**
                 * \brief Sets the value of a uniform
                 *
                 * \param uni       The uniform to set.
                 * \param value     The value to set it to.
                 * \return Whether the uniform could be set or not.
                 *
                 ***********************************************/
                template <typename _type>
                inline void setUniform(const std::string &uni, _type value) const
                    { Program::setUniform(getUniformLocation(uni), value); }

                /********************************************//**
                 * \brief Sets the value of a uniform to a matrix
                 *
                 * \param uni       The uniform to set.
                 * \param value     The value to set it to.
                 * \param transpose Whether to transpose the matrix or not.
                 * \return Whether the uniform could be set or not.
                 *
                 ***********************************************/
                template <typename _type>
                inline void setUniform(const std::string &uni, _type value, bool transpose) const
                    { Program::setUniform(getUniformLocation(uni), value, transpose); }

                /********************************************//**
                 * \brief Sort unique shaders in a container
                 *
                 * \param s1    First shader.
                 * \param s2    Second shader.
                 * \return True if s1 precedes s2.
                 *
                 * Does not take null pointers!
                 *
                 ***********************************************/
                struct sort { bool operator()(const Shader *s1, const Shader *s2) const; };
        };

        //! Generates a shader to render depth
        class CWE_DLL Depth : public Shader
        {
            //-----------------------------------------------------------------------
            public:
                // Define depth configuration
                enum DepthConfiguration
                {
                    CONFIG_ALPHA            = 1 << 0,
                    CONFIG_TEXTURE_ALPHA    = 1 << 1,

                    DEPTH_CONFIG_COUNT      = 1 << 2
                };

                //-----------------------------------------------------------------------
                // Define depth attributes
                enum DepthAttribute
                {
                    ATTRIBUTE_POSITION,
                    ATTRIBUTE_TEXCOORD,

                    DEPTH_ATTRIBUTE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define depth texture units
                enum DepthTexture
                {
                    TEXTURE_ALPHA = 1,

                    DEPTH_TEXTURE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define uniforms
                static const std::string UNIFORM_ALPHA;
                static const std::string UNIFORM_TEXTURE_ALPHA;
                static const std::string UNIFORM_ALPHA_THRESHOLD;

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Generates a string for each attribute
                 *
                 * \param attr  The attribute to generate a string for.
                 * \return The generated string.
                 *
                 ***********************************************/
                static std::string getString(const DepthAttribute &attr);

                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const;

                /********************************************//**
                 * \brief Fetch the #define string for a specific configuration bit.
                 *
                 * \param config    Configuration bit to fetch the string for, must be a power of 2.
                 * \return The #define string for the given configuration bit.
                 *
                 ***********************************************/
                virtual std::string getConfigDefine(unsigned int config) const;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param config    Configuration of the shader.
                 *
                 * Constructs the Depth Shader to be of PASS_DEPTH.
                 *
                 ***********************************************/
                Depth(unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                Depth(const Depth &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Depth() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 ***********************************************/
                virtual Shader *clone() const;

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 ***********************************************/
                virtual bool compile();

            //-----------------------------------------------------------------------
            protected:

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 * Constructs the Depth Shader with an unknown type, for possible inheritance.
                 *
                 ***********************************************/
                Depth(const Pass &pass, unsigned int configWidth, unsigned int config);
        };

        //! Generates a shader to render depth to a cubemap
        class CWE_DLL DepthCubemap : public Depth
        {
            //-----------------------------------------------------------------------
            public:
                // Define rotational matrices for each camera in cubemap
                static const Math::mat4f MATRIX_POSITIVE_X;
                static const Math::mat4f MATRIX_NEGATIVE_X;
                static const Math::mat4f MATRIX_POSITIVE_Y;
                static const Math::mat4f MATRIX_NEGATIVE_Y;
                static const Math::mat4f MATRIX_POSITIVE_Z;
                static const Math::mat4f MATRIX_NEGATIVE_Z;

                //-----------------------------------------------------------------------
                // Define depth cubemap configuration
                enum DepthCubemapConfiguration
                {
                    DEPTH_CUBEMAP_CONFIG_COUNT = DEPTH_CONFIG_COUNT
                };

                //-----------------------------------------------------------------------
                // Define depth cubemap attributes
                enum DepthCubemapAttribute
                {
                    DEPTH_CUBEMAP_ATTRIBUTE_COUNT = DEPTH_ATTRIBUTE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define depth cubemap texture units
                enum DepthCubemapTexture
                {
                    DEPTH_CUBEMAP_TEXTURE_COUNT = DEPTH_TEXTURE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define cube map matrices
                static const std::string UNIFORM_MATRIX_CUBEMAP;
                static const std::string UNIFORM_MATRIX_POSITIVE_X;
                static const std::string UNIFORM_MATRIX_NEGATIVE_X;
                static const std::string UNIFORM_MATRIX_POSITIVE_Y;
                static const std::string UNIFORM_MATRIX_NEGATIVE_Y;
                static const std::string UNIFORM_MATRIX_POSITIVE_Z;
                static const std::string UNIFORM_MATRIX_NEGATIVE_Z;

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param config    Configuration of the shader.
                 *
                 * Constructs the Depth Cubemap Shader to be of PASS_DEPTH_CUBEMAP.
                 *
                 ***********************************************/
                DepthCubemap(unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                DepthCubemap(const DepthCubemap &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~DepthCubemap() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 ***********************************************/
                virtual Shader *clone() const;

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 ***********************************************/
                virtual bool compile();

            //-----------------------------------------------------------------------
            protected:

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 * Constructs the Depth Shader with an unknown type, for possible inheritance.
                 *
                 ***********************************************/
                DepthCubemap(const Pass &pass, unsigned int configWidth, unsigned int config);
        };

        //! Generates a shader to render unlit objects
        class CWE_DLL Flat : public Depth
        {
            //-----------------------------------------------------------------------
            public:
                // Define flat configuration
                enum FlatConfiguration
                {
                    CONFIG_DIFFUSE                  = DEPTH_CONFIG_COUNT << 0,
                    CONFIG_TEXTURE_DIFFUSE          = DEPTH_CONFIG_COUNT << 1,
                    CONFIG_TEXTURE_DIFFUSE_ALPHA    = DEPTH_CONFIG_COUNT << 2,
                    CONFIG_ALPHA_THRESHOLD          = DEPTH_CONFIG_COUNT << 3,

                    FLAT_CONFIG_COUNT               = DEPTH_CONFIG_COUNT << 4
                };

                //-----------------------------------------------------------------------
                // Define depth attributes
                enum FlatAttribute
                {
                    FLAT_ATTRIBUTE_COUNT = DEPTH_ATTRIBUTE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define flat texture units
                enum FlatTexture
                {
                    TEXTURE_DIFFUSE = DEPTH_TEXTURE_COUNT,

                    FLAT_TEXTURE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define uniforms
                static const std::string UNIFORM_DIFFUSE;
                static const std::string UNIFORM_TEXTURE_DIFFUSE;

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const;

                /********************************************//**
                 * \brief Fetch the #define string for a specific configuration bit.
                 *
                 * \param config    Configuration bit to fetch the string for, must be a power of 2.
                 * \return The #define string for the given configuration bit.
                 *
                 ***********************************************/
                virtual std::string getConfigDefine(unsigned int config) const;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param config    Configuration of the shader.
                 *
                 * Constructs the Flat Shader to be of PASS_FLAT.
                 *
                 ***********************************************/
                Flat(unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                Flat(const Flat &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Flat() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 ***********************************************/
                virtual Shader *clone() const;

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 ***********************************************/
                virtual bool compile();

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 * Constructs the Flat Shader with an unknown type, for possible inheritance.
                 *
                 ***********************************************/
                Flat(const Pass &pass, unsigned int configWidth, unsigned int config);
        };

        //! Generates a shader to render lit objects
        class CWE_DLL Geometry : public Flat
        {
            //-----------------------------------------------------------------------
            public:
                // Define geometry configuration
                enum GeometryConfiguration
                {
                    CONFIG_SPECULAR                 = FLAT_CONFIG_COUNT << 0,
                    CONFIG_MULT_SPECULAR_DIFFUSE    = FLAT_CONFIG_COUNT << 1,
                    CONFIG_GLOSS                    = FLAT_CONFIG_COUNT << 2,
                    CONFIG_TEXTURE_SPECULAR         = FLAT_CONFIG_COUNT << 3,
                    CONFIG_TEXTURE_SPECULAR_GLOSS   = FLAT_CONFIG_COUNT << 4,
                    CONFIG_TEXTURE_GLOSS            = FLAT_CONFIG_COUNT << 5,
                    CONFIG_TEXTURE_NORMAL           = FLAT_CONFIG_COUNT << 6,

                    GEOMETRY_CONFIG_COUNT           = FLAT_CONFIG_COUNT << 7
                };

                //-----------------------------------------------------------------------
                // Define geometry attributes
                enum GeometryAttribute
                {
                    ATTRIBUTE_NORMAL = FLAT_ATTRIBUTE_COUNT,
                    ATTRIBUTE_TANGENT,
                    ATTRIBUTE_BITANGENT,

                    GEOMETRY_ATTRIBUTE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define geometry texture units
                enum GeometryTexture
                {
                    TEXTURE_SPECULAR = FLAT_TEXTURE_COUNT,
                    TEXTURE_GLOSS,
                    TEXTURE_NORMAL,

                    GEOMETRY_TEXTURE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define uniforms
                static const std::string UNIFORM_MATRIX_NORMAL;
                static const std::string UNIFORM_SPECULAR;
                static const std::string UNIFORM_GLOSS;
                static const std::string UNIFORM_GLOSS_RANGE;
                static const std::string UNIFORM_TEXTURE_SPECULAR;
                static const std::string UNIFORM_TEXTURE_GLOSS;
                static const std::string UNIFORM_TEXTURE_NORMAL;

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Generates a string for each attribute
                 *
                 * \param attr  The attribute to generate a string for.
                 * \return The generated string.
                 *
                 ***********************************************/
                static std::string getString(const GeometryAttribute &attr);

                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const;

                /********************************************//**
                 * \brief Fetch the #define string for a specific configuration bit.
                 *
                 * \param config    Configuration bit to fetch the string for, must be a power of 2.
                 * \return The #define string for the given configuration bit.
                 *
                 ***********************************************/
                virtual std::string getConfigDefine(unsigned int config) const;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param config    Configuration of the shader.
                 *
                 * Constructs the Geometry Shader to be of PASS_GEOMETRY.
                 *
                 ***********************************************/
                Geometry(unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                Geometry(const Geometry &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Geometry() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 ***********************************************/
                virtual Shader *clone() const;

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 ***********************************************/
                virtual bool compile();

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 * Constructs the Geometry Shader with an unknown type, for possible inheritance.
                 *
                 ***********************************************/
                Geometry(const Pass &pass, unsigned int configWidth, unsigned int config);
        };

        //! Generates a shader to render a light
        class CWE_DLL Light : public Shader
        {
            //-----------------------------------------------------------------------
            public:
                // Define the texture bias matrix
                static const Math::mat4f MATRIX_TEXTURE_BIAS;

                //-----------------------------------------------------------------------
                // Define light configuration
                enum LightConfiguration
                {
                    CONFIG_POINT_LIGHT          = 1 << 0, // If false, it is directional
                    CONFIG_ANGLE_MASK           = 1 << 1,
                    CONFIG_SHADOW_MAP           = 1 << 2,
                    CONFIG_SHADOW_NO_BLEED      = 1 << 3,

                    LIGHT_CONFIG_COUNT          = 1 << 4
                };

                //-----------------------------------------------------------------------
                // Define light attributes
                enum LightAttribute
                {
                    ATTRIBUTE_POSITION,

                    LIGHT_ATTRIBUTE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define light texture units
                enum LightTexture
                {
                    TEXTURE_G_BUFFER_DIFFUSE = 1,
                    TEXTURE_G_BUFFER_SPECULAR,
                    TEXTURE_G_BUFFER_NORMAL,
                    TEXTURE_ANGLE_MASK,
                    TEXTURE_SHADOW,

                    LIGHT_TEXTURE_COUNT
                };

                //-----------------------------------------------------------------------
                // Define light properties
                static const std::string UNIFORM_LIGHT_INTENSITY;
                static const std::string UNIFORM_LIGHT_POSITION;
                static const std::string UNIFORM_LIGHT_DIRECTION;
                static const std::string UNIFORM_LIGHT_ATTENUATION;

                // Define other uniforms
                static const std::string UNIFORM_MATRIX_SHADOW;
                static const std::string UNIFORM_SHADOW_BIAS;
                static const std::string UNIFORM_TEXTURE_G_BUFFER_DIFFUSE;
                static const std::string UNIFORM_TEXTURE_G_BUFFER_SPECULAR;
                static const std::string UNIFORM_TEXTURE_G_BUFFER_NORMAL;
                static const std::string UNIFORM_TEXTURE_ANGLE_MASK;
                static const std::string UNIFORM_TEXTURE_SHADOW;

            //-----------------------------------------------------------------------
            protected:
                /********************************************//**
                 * \brief Generates a string for each attribute
                 *
                 * \param attr  The attribute to generate a string for.
                 * \return The generated string.
                 *
                 ***********************************************/
                static std::string getString(const LightAttribute &attr);

                /********************************************//**
                 * \brief Generates the source for the current type and configuration
                 *
                 * \param vertexStr     Generated vertex source.
                 * \param fragmentStr   Generated fragment source.
                 * \param geometryStr   Generated geometry source.
                 * \return void
                 *
                 * Generates the source, note the configuration defines are already in the given strings.
                 *
                 ***********************************************/
                virtual void generateSource(std::string &vertexStr, std::string &fragmentStr, std::string &geometryStr) const;

                /********************************************//**
                 * \brief Fetch the #define string for a specific configuration bit.
                 *
                 * \param config    Configuration bit to fetch the string for, must be a power of 2.
                 * \return The #define string for the given configuration bit.
                 *
                 ***********************************************/
                virtual std::string getConfigDefine(unsigned int config) const;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * \param config    Configuration of the shader.
                 *
                 * Constructs the Light Shader to be of PASS_LIGHT.
                 *
                 ***********************************************/
                Light(unsigned int config);

                /********************************************//**
                 * \brief Copy Constructor
                 *
                 * Copies the pass and configuration, will not compile!
                 *
                 ***********************************************/
                Light(const Light &shad);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Light() {}

                /********************************************//**
                 * \brief Clones the polymorphic object
                 *
                 * \return A dynamically allocated copy.
                 *
                 ***********************************************/
                virtual Shader *clone() const;

                /********************************************//**
                 * \brief Compiles the program according to the current type and configuration.
                 *
                 * \return Whether the program could be compiled or not.
                 *
                 ***********************************************/
                virtual bool compile();

            //-----------------------------------------------------------------------
            protected:

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass          Pass the shader participates in.
                 * \param configWidth   Configuration Width, should store what bits are allowed to be set.
                 * \param config        Configuration of the shader.
                 *
                 * Constructs the Light Shader with an unknown type, for possible inheritance.
                 *
                 ***********************************************/
                Light(const Pass &pass, unsigned int configWidth, unsigned int config);
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Program : Program stored in the GPU to shade
 rendered objects.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_PROGRAM_H__
#define __HARDWARE_PROGRAM_H__

#include "Hardware/HardwareShader.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Program stored in the GPU to shade rendered objects
        class CWE_DLL Program : public HardwareBase
        {
            //-----------------------------------------------------------------------
            protected:
                // Properties
                bool _compiled;

                // Bound program
                static Program *_bound;

            //-----------------------------------------------------------------------
            private:
                // Private Copy Constructor to prevent it
                Program(const Program &obj);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                Program();

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Program();

                /********************************************//**
                 * \brief Manually bind the program
                 *
                 * \return Whether the program is bound or not.
                 *
                 * Binds the program as the active program to use while rendering.
                 *
                 ***********************************************/
                bool bind() const;

                /********************************************//**
                 * \brief Fetch whether this program is bound or not
                 *
                 * \return Whether this program is bound or not.
                 *
                 ***********************************************/
                bool isBound() const;

                /********************************************//**
                 * \brief Sets a shader of the program
                 *
                 * \param shader    The shader to add.
                 * \return Whether the shader was successfully added or not.
                 *
                 * Adds a shader for compiling, must be set before compiling! (or after decompiling).
                 *
                 ***********************************************/
                bool addShader(Shader &shader);

                /********************************************//**
                 * \brief Removes a shader from the program
                 *
                 * \param shader    The shader to remove.
                 * \return Whether the shader was successfully removed or not.
                 *
                 * Removes a shader before compiling, must be removed before compiling! (or after decompiling).
                 *
                 ***********************************************/
                bool removeShader(const Shader &shader);

                /********************************************//**
                 * \brief Sets an attribute location beforehand
                 *
                 * \param location  The location to set.
                 * \param attribute The attribute to set it to.
                 * \return Whether the location was successfully set or not.
                 *
                 * Fixes a certain attribute at a location, must be set before compiling! (or after decompiling).
                 *
                 ***********************************************/
                bool setAttributeLocation(unsigned int location, const std::string &attribute);

                /********************************************//**
                 * \brief Compiles the program
                 *
                 * \return Whether the program was successfully compiled or not.
                 *
                 ***********************************************/
                bool compile();

                /********************************************//**
                 * \brief Decompiles the program
                 *
                 * \return void
                 *
                 * Will remove all shaders and attributes added, need to re-add them before compiling again!
                 *
                 ***********************************************/
                void decompile();

                /********************************************//**
                 * \brief Fetch whether this program is compiled or not
                 *
                 * \return Whether the program is compiled or not.
                 *
                 ***********************************************/
                bool isCompiled() const;

                /********************************************//**
                 * \brief Fetch the location of a given (vertex) attribute
                 *
                 * \param attribute The given (vertex) attribute.
                 * \return The location of the attribute, -1 if the attribute does not exist.
                 *
                 * Fetches the location of a given (vertex) attribute within the compiled program.
                 *
                 ***********************************************/
                int getAttributeLocation(const std::string &attribute) const;

                /********************************************//**
                 * \brief Fetch the location of a given uniform
                 *
                 * \param uniform   The given uniform.
                 * \return The location of the uniform, -1 if the uniform does not exist.
                 *
                 * Fetches the location of a given uniform within the compiled program.
                 *
                 ***********************************************/
                int getUniformLocation(const std::string &uniform) const;

                /********************************************//**
                 * \brief Sets the value of an attribute at a location
                 *
                 * \param location  The location to set.
                 * \param value     The value to set it to.
                 * \return Whether the attribute was successfully set or not.
                 *
                 ***********************************************/
                void setAttribute(unsigned int location, const short value) const;
                void setAttribute(unsigned int location, const Math::vec2s &value) const;
                void setAttribute(unsigned int location, const Math::vec3s &value) const;
                void setAttribute(unsigned int location, const Math::vec4s &value) const;
                void setAttribute(unsigned int location, const int value) const;
                void setAttribute(unsigned int location, const Math::vec2i &value) const;
                void setAttribute(unsigned int location, const Math::vec3i &value) const;
                void setAttribute(unsigned int location, const Math::vec4i &value) const;
                void setAttribute(unsigned int location, const unsigned int value) const;
                void setAttribute(unsigned int location, const Math::vec2ui &value) const;
                void setAttribute(unsigned int location, const Math::vec3ui &value) const;
                void setAttribute(unsigned int location, const Math::vec4ui &value) const;
                void setAttribute(unsigned int location, const float value) const;
                void setAttribute(unsigned int location, const Math::vec2f &value) const;
                void setAttribute(unsigned int location, const Math::vec3f &value) const;
                void setAttribute(unsigned int location, const Math::vec4f &value) const;
                void setAttribute(unsigned int location, const double value) const;
                void setAttribute(unsigned int location, const Math::vec2d &value) const;
                void setAttribute(unsigned int location, const Math::vec3d &value) const;
                void setAttribute(unsigned int location, const Math::vec4d &value) const;

                /********************************************//**
                 * \brief Sets the value of a uniform at a location
                 *
                 * \param location  The location to set.
                 * \param value     The value to set it to.
                 * \param transpose Whether to transpose the matrix or not.
                 * \return Whether the uniform was successfully set or not.
                 *
                 ***********************************************/
                void setUniform(unsigned int location, const int value) const;
                void setUniform(unsigned int location, const Math::vec2i &value) const;
                void setUniform(unsigned int location, const Math::vec3i &value) const;
                void setUniform(unsigned int location, const Math::vec4i &value) const;
                void setUniform(unsigned int location, const unsigned int value) const;
                void setUniform(unsigned int location, const Math::vec2ui &value) const;
                void setUniform(unsigned int location, const Math::vec3ui &value) const;
                void setUniform(unsigned int location, const Math::vec4ui &value) const;
                void setUniform(unsigned int location, const float value) const;
                void setUniform(unsigned int location, const Math::vec2f &value) const;
                void setUniform(unsigned int location, const Math::vec3f &value) const;
                void setUniform(unsigned int location, const Math::vec4f &value) const;
                void setUniform(unsigned int location, Math::mat2f &value, bool transpose = false) const;
                void setUniform(unsigned int location, Math::mat3f &value, bool transpose = false) const;
                void setUniform(unsigned int location, Math::mat4f &value, bool transpose = false) const;
        };
    }
}

#endif

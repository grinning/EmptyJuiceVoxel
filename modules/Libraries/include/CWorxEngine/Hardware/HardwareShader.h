/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Shader : Shader stored in the GPU

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_SHADER_H__
#define __HARDWARE_SHADER_H__

#include "CWorxConsole.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Shader stored on the GPU to participate in a Program
        class CWE_DLL Shader : public HardwareBase
        {
            //-----------------------------------------------------------------------
            public:
                // Define possible shader types
                enum Type
                {
                    TYPE_VERTEX_SHADER      = GL_VERTEX_SHADER,
                    TYPE_GEOMETRY_SHADER    = GL_GEOMETRY_SHADER,
                    TYPE_FRAGMENT_SHADER    = GL_FRAGMENT_SHADER
                };

            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Type _type;

            //-----------------------------------------------------------------------
            private:
                // Private Copy Constructor to prevent it
                Shader(const Shader &obj);

            //-----------------------------------------------------------------------
            public:
                // To attach shader to program
                friend class Program;

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type  The shader type to generate.
                 * \param src   The source 'code' for the shader.
                 *
                 * Constructs a shader with a specific type and a source
                 *
                 ***********************************************/
                Shader(const Type &type, const std::string &src);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Shader();

                /********************************************//**
                 * \brief Fetch the type of the shader
                 *
                 * \return The type of the shader.
                 *
                 ***********************************************/
                const Type &getType() const;

                /********************************************//**
                 * \brief Overwrites the source code
                 *
                 * \param src   The source 'code' for the shader.
                 * \return Whether the source is successfully set or not.
                 *
                 ***********************************************/
                bool setSource(const std::string &src);

                /********************************************//**
                 * \brief Returns the source code
                 *
                 * \return The source of the shader.
                 *
                 ***********************************************/
                std::string getSource() const;

                /********************************************//**
                 * \brief Compiles the shader, rendering any non constant method invalid.
                 *
                 * \return Whether the shader was successfully compiled or not.
                 *
                 * Compiles the shader and adds the shader to the compiled shader list.
                 *
                 ***********************************************/
                bool compile();

                /********************************************//**
                 * \brief Fetch whether this shader is compiled or not
                 *
                 * \return Whether the shader is compiled or not.
                 *
                 ***********************************************/
                bool isCompiled() const;
        };
    }
}

#endif

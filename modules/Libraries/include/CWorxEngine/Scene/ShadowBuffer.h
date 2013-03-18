/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 ShadowBuffer : Holds depth buffers accompanied by
 camera and shaders to perform shadow rendering.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __SHADOW_BUFFER_H__
#define __SHADOW_BUFFER_H__

#include "Geometry/RenderQueue.h"
#include "Geometry/Viewport.h"
#include "Scene/Light.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! Holds a depth buffer to render from a light's perspective
    class CWE_DLL ShadowBuffer : private Geometry::Viewport
    {
        //-----------------------------------------------------------------------
        protected:
            // Properties
            unsigned int _resolution; // Of the cube map
            Hardware::Texture _cube;

            // Shadow Casters
            Geometry::RenderQueue _queue;

            /********************************************//**
             * \brief Binds the buffer's properties to a given shader through a render queue callback
             *
             * \param light The Light to take properties from.
             * \param rend  Renderable of the render queue callback
             * \param shad  Shader of the render queue callback.
             * \return void
             *
             * Binds the buffer's properties to a given shader, for example light properties.
             *
             ***********************************************/
            virtual void bindProperties(const Light &light, const Geometry::Renderable &rend, const Shader::Shader &shad);

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param cube          Cube texture resolution per face.
             * \param directional   Directional texture resolution.
             *
             ***********************************************/
            ShadowBuffer(unsigned int cube, const Math::vec2ui &directional);

            /********************************************//**
             * \brief Sets the resolution of the cube depth textures
             *
             * \param resolution    Cube texture resolution per face.
             * \return Whethert it could set the resolution or not.
             *
             ***********************************************/
            void setCubeResolution(unsigned int resolution);

            /********************************************//**
             * \brief Sets the resolution of the directional depth texture
             *
             * \param resolution    Directional texture resolution.
             * \return Whethert it could set the resolution or not.
             *
             ***********************************************/
            void setDirectionalResolution(const Math::vec2ui &resolution);

            /********************************************//**
             * \brief Fetch the resolution of the cube depth textures
             *
             * \return The resolution of the depth textures.
             *
             ***********************************************/
            unsigned int getCubeResolution() const;

            /********************************************//**
             * \brief Fetch the resolution of the directional depth texture
             *
             * \return The resolution of the depth textures.
             *
             ***********************************************/
            const Math::vec2ui &getDirectionalResolution() const;

            /********************************************//**
             * \brief Adds a shadow caster as to the shadow buffer
             *
             * \param rend  The renderable to add.
             * \return void
             *
             ***********************************************/
            void addShadowCaster(Geometry::Renderable &rend);

            /********************************************//**
             * \brief Returns whether it has a specified shadow caster
             *
             * \param rend  The specified renderable.
             * \return Whether it has the specified renderable or not.
             *
             ***********************************************/
            bool hasShadowCaster(const Geometry::Renderable &rend) const;

            /********************************************//**
             * \brief Fetch the amount of shadow casters
             *
             * \return The amount of shadow casters.
             *
             ***********************************************/
            unsigned int getNumShadowCasters() const;

            /********************************************//**
             * \brief Removes a shadow caster from the shadow buffer
             *
             * \param rend  The renderable to remove.
             * \return Whether the shadow caster could be removed or not.
             *
             ***********************************************/
            bool removeShadowCaster(const Geometry::Renderable &rend);

            /********************************************//**
             * \brief Updates the stored shadow casters
             *
             * \return void
             *
             ***********************************************/
            void update();

            /********************************************//**
             * \brief Renders the depth of the shadow casters to the depth texture
             *
             * \param light     The light to render for.
             * \param modifiers Modifiers to use while binding the viewport.
             * \return Whether it was successfully rendered or not.
             *
             * Renders the depth of the shadow casters to the depth texture.
             * Binds this texture to the shadow texture unit (defined in the light shader).
             *
             ***********************************************/
            bool render(const Light &light, unsigned short modifiers = 0);
    };
}

#endif

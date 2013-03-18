/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Scene : Contains all the data to render a complete scene
 through a camera.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "Scene/Camera.h"
#include "Scene/ShadowBuffer.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! Contains all the data to render a complete scene
    class CWE_DLL Scene
    {
        //-----------------------------------------------------------------------
        protected:
            // Properties
            Camera *_camera;
            ShadowBuffer *_shadow;

            // Render queues
            Geometry::RenderQueue _geometryQueue;
            Geometry::RenderQueue _lightQueue;
            Geometry::RenderQueue _flatQueue;
            Geometry::RenderQueue _overlayQueue;

            /********************************************//**
             * \brief Render passes
             *
             * \param port  The viewport to render to.
             * \return void
             *
             * All the render passes, call them in the order they're defined for correct output!
             *
             ***********************************************/
            void geometryPass (Geometry::Viewport &port);
            void lightPass    (Geometry::Viewport &port);
            void flatPass     (Geometry::Viewport &port);
            void overlayPass  (Geometry::Viewport &port);

            /********************************************//**
             * \brief Shadow pass through render queue callback
             *
             * \param port  The viewport to render to.
             * \param rend  Renderable of the render queue callback
             * \param shad  Shader of the render queue callback.
             * \return void
             *
             * Shadow pass, must be during light pass!
             * 'activeShadowPort' must be set for anything to happen.
             *
             ***********************************************/
            void shadowPass(Geometry::Viewport &port, const Geometry::Renderable &rend, const Shader::Shader &shad);

            /********************************************//**
             * \brief Binds the scene's properties to a given shader through a render queue callback
             *
             * \param port  The viewport to take properties from.
             * \param rend  Renderable of the render queue callback
             * \param shad  Shader of the render queue callback.
             * \return void
             *
             * Binds the scene's properties to a given shader, for example camera properties.
             *
             ***********************************************/
            virtual void bindProperties(Geometry::Viewport &port, const Geometry::Renderable &rend, const Shader::Shader &shad);

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param camera    The camera to render through.
             *
             ***********************************************/
            Scene(Camera &camera);

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Scene();

            /********************************************//**
             * \brief Sets the camera to use
             *
             * \param camera    New camera to use.
             * \return void
             *
             ***********************************************/
            void setCamera(Camera &camera);

            /********************************************//**
             * \brief Fetch the camera in use
             *
             * \return The camera in use.
             *
             ***********************************************/
            Camera &getCamera() const;

            /********************************************//**
             * \brief Resizes the camera
             *
             * \param size  The new width and height.
             * \return void
             *
             ***********************************************/
            void resize(const Math::vec2ui &size);

            /********************************************//**
             * \brief Resizes the camera
             *
             * \param width     The new width.
             * \param height    The new height.
             * \return void
             *
             ***********************************************/
            void resize(const unsigned int width, const unsigned int height);

            /********************************************//**
             * \brief Enable/disable shadows
             *
             * \param shadow        If true, shadows will be enabled.
             * \param cube          The resolution of the cube maps.
             * \param directional   Resolution of the directional map.
             * \return Whether it has successfully changed shadow state or not.
             *
             * Enable/Disable shadows, when disabled, all shadow casters will be removed,
             * Need to re-add shadow casters when enabling again, also the resolutions cannot be 0.
             *
             ***********************************************/
            bool castShadows(bool shadow, unsigned int cube, const Math::vec2ui &directional);

            /********************************************//**
             * \brief Fetch whether shadows are enabled
             *
             * \return Whether shadows are enabled or not.
             *
             ***********************************************/
            bool castShadows() const;

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
             * \return Whether it has the specified shadow caster or not.
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
             * \return Whether it could remov the shadow caster or not.
             *
             ***********************************************/
            bool removeShadowCaster(const Geometry::Renderable &rend);

            /********************************************//**
             * \brief Fetch the shadow buffer
             *
             * \return The shadow buffer.
             *
             ***********************************************/
            ShadowBuffer *getShadowBuffer() const;

            /********************************************//**
             * \brief Adds a renderable of a specific shader pass to the scene
             *
             * \param pass          The shader pass to participate in.
             * \param rend          The renderable to add.
             * \param castShadow    Whether to add it as a shadow caster or not.
             * \return Whether it could add the renderable or not.
             *
             ***********************************************/
            bool addRenderable(const Shader::Pass &pass, Geometry::Renderable &rend, bool castShadow = true);

            /********************************************//**
             * \brief Returns whether it has the specified renderable
             *
             * \param rend  The specified renderable.
             * \return Whether it has the specified renderable or not.
             *
             ***********************************************/
            bool hasRenderable(const Geometry::Renderable &rend) const;

            /********************************************//**
             * \brief Fetch the amount of renderables
             *
             * \return The amount of renderables.
             *
             ***********************************************/
            unsigned int getNumRenderables() const;

            /********************************************//**
             * \brief Removes a renderable from the scene
             *
             * \param rend  The renderable to remove.
             * \return Whether it could remove the renderable or not.
             *
             ***********************************************/
            bool removeRenderable(const Geometry::Renderable &rend);

            /********************************************//**
             * \brief Adds a light to the scene
             *
             * \param light The light to add.
             * \return void
             *
             ***********************************************/
            void addLight(Light &light);

            /********************************************//**
             * \brief Returns whether it has the specified light
             *
             * \param light The specified light.
             * \return Whether it has the specified light or not.
             *
             ***********************************************/
            bool hasLight(const Light &light) const;

            /********************************************//**
             * \brief Fetch the amount of lights
             *
             * \return The amount of lights.
             *
             ***********************************************/
            unsigned int getNumLights() const;

            /********************************************//**
             * \brief Removes a light from the scene
             *
             * \param light The light to remove.
             * \return Whether it could remove the light or not.
             *
             ***********************************************/
            bool removeLight(const Light &light);

            /********************************************//**
             * \brief Adds a renderable as overlay to the scene
             *
             * \param rend  The renderable to add.
             * \return void
             *
             ***********************************************/
            void addOverlay(Geometry::Renderable &rend);

            /********************************************//**
             * \brief Returns whether it has a specified renderable as overlay
             *
             * \param rend  The specified renderable.
             * \return Whether it has the specified renderable or not.
             *
             ***********************************************/
            bool hasOverlay(const Geometry::Renderable &rend) const;

            /********************************************//**
             * \brief Fetch the amount of overlays
             *
             * \return The amount of overlays.
             *
             ***********************************************/
            unsigned int getNumOverlays() const;

            /********************************************//**
             * \brief Removes a renderable as overlay from the scene
             *
             * \param rend  The renderable to remove.
             * \return Whether the renderable could be removed or not.
             *
             ***********************************************/
            bool removeOverlay(const Geometry::Renderable &rend);

            /********************************************//**
             * \brief Updates the scene
             *
             * \return void
             *
             ***********************************************/
            void update();

            /********************************************//**
             * \brief Renders the scene
             *
             * \param port  The viewport to render to.
             * \return void
             *
             * Will render the entire scene, and update it beforehand.
             *
             ***********************************************/
            virtual void render(Geometry::Viewport &port);
    };
}

#endif

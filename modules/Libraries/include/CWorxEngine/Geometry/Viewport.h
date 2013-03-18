/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Viewport : Holds a renderable target and a number of
 color and depth buffers.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "Hardware/HardwareRenderTarget.h"
#include "Hardware/HardwareTexture.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Holds a render target and a number of textures
        class CWE_DLL Viewport : private Hardware::RenderTarget
        {
            //-----------------------------------------------------------------------
            protected:
                // Define a list of textures
                typedef std::vector<Hardware::Texture*> TextureList;

                // Properties
                Hardware::Texture *_depth;
                TextureList _colorBuffers;
                Math::vec2ui _size;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Sets the depth test to use everywhere
                 *
                 * \param depth Test to use.
                 * \return void
                 *
                 ***********************************************/
                static void setDepthTest(const RenderTarget::DepthTest &test);

                /********************************************//**
                 * \brief Sets the blending factors
                 *
                 * \param src   Factor for incoming components.
                 * \param dst   Factor for existing components.
                 * \return void
                 *
                 ***********************************************/
                static void blendFactor(const RenderTarget::BlendFactor &src, const RenderTarget::BlendFactor &dst);

                /********************************************//**
                 * \brief Sets the blending factor for RGB and Alpha seperately
                 *
                 * \param srcRGB    Factor for incoming R,G,B components.
                 * \param srcAlpha  Factor for incoming A component.
                 * \param dstRGB    Factor for existing R,G,B components.
                 * \param dstAlpha  Factor for existing A component.
                 * \return void
                 *
                 ***********************************************/
                static void blendFactorSeperate(const BlendFactor &srcRGB, const BlendFactor &srcAlpha, const BlendFactor &dstRGB, const BlendFactor &dstAlpha);

                /********************************************//**
                 * \brief Sets the blend equation to use everywhere
                 *
                 * \param blend Equation to use.
                 * \return void
                 *
                 ***********************************************/
                static void setBlendEquation(const RenderTarget::BlendEquation &blend);

                /********************************************//**
                 * \brief Sets render state modifiers to render with
                 *
                 * \param modifiers Modifiers to change the render state.
                 * \return void
                 *
                 ***********************************************/
                static void setModifiers(unsigned short modifiers);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param size              Width and height of the viewport.
                 * \param numColorBuffers   Number of color buffers to create.
                 * \param depth             If true, depth buffer will be created.
                 *
                 ***********************************************/
                Viewport(const Math::vec2ui &size, unsigned short numColorBuffers = 1, bool depth = true);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Viewport();

                /********************************************//**
                 * \brief Creates all color buffers
                 *
                 * \param numColor  Number of color buffers to create.
                 * \return void
                 *
                 ***********************************************/
                void createColorBuffers(unsigned short numColor);

                /********************************************//**
                 * \brief Destroys all color buffers
                 *
                 * \return void
                 *
                 ***********************************************/
                void destroyColorBuffers();

                /********************************************//**
                 * \brief Fetch the number of color buffers
                 *
                 * \return The number of color buffers.
                 *
                 ***********************************************/
                unsigned short getNumColorBuffers() const;

                /********************************************//**
                 * \brief Creates the depth buffer
                 *
                 * \return void
                 *
                 ***********************************************/
                void createDepthBuffer();

                /********************************************//**
                 * \brief Destroys the depth buffer
                 *
                 * \return void
                 *
                 ***********************************************/
                void destroyDepthBuffer();

                /********************************************//**
                 * \brief Fetch whether it has a depth buffer or not
                 *
                 * \return Whether it has a depth buffer or not.
                 *
                 ***********************************************/
                bool hasDepthBuffer() const;

                /********************************************//**
                 * \brief Resizes the viewport
                 *
                 * \param size  New width and height.
                 * \return void
                 *
                 ***********************************************/
                void resize(const Math::vec2ui &size);

                /********************************************//**
                 * \brief Resizes the viewport
                 *
                 * \param width     New width.
                 * \param height    New height.
                 * \return void
                 *
                 ***********************************************/
                void resize(unsigned int width, unsigned int height);

                /********************************************//**
                 * \brief Fetch the size of the viewport
                 *
                 * \return The size of the viewport.
                 *
                 ***********************************************/
                const Math::vec2ui &getSize() const;

                /********************************************//**
                 * \brief Sets the internal depth buffer as active
                 *
                 * \return Whether it could use the internal depth buffer or not.
                 *
                 ***********************************************/
                bool useDepth();

                /********************************************//**
                 * \brief Sets the active depth buffer to an external texture
                 *
                 * \param tex       The texture to attach.
                 * \param mipmap    The mipmap level to bind.
                 * \param face      What face of a cubemap to attach.
                 * \return Whether it could use the given depth buffer or not.
                 *
                 ***********************************************/
                bool useDepth(Hardware::Texture &tex, unsigned int mipmap = 0, const Hardware::Texture::Face &face = Hardware::Texture::FACE_ALL);

                /********************************************//**
                 * \brief Sets this viewport as the active render target
                 *
                 * \param size      If not zero, will use this render area instead.
                 * \param modifiers Modifiers to use while binding this viewport.
                 * \return Whether it could use this viewport as active render target or not.
                 *
                 * Sets this viewport as the active render target, all drawn meshes will be drawn onto this viewport.
                 *
                 ***********************************************/
                bool use(const Math::vec2ui &size, unsigned short modifiers);

                /********************************************//**
                 * \brief Sets this viewport as the active render target
                 *
                 * \param size      If not zero, will use this render area instead.
                 * \param index     The index to write to ( < 0 means do not write to any).
                 * \param modifiers Modifiers to use while binding this viewport.
                 * \return Whether it could use this viewport as active render target or not.
                 *
                 * Sets this viewport as the active render target, all drawn meshes will be drawn onto this viewport.
                 *
                 ***********************************************/
                bool use(const Math::vec2ui &size, int index, unsigned short modifiers);

                /********************************************//**
                 * \brief Sets this viewport as the active render target
                 *
                 * \param size          If not zero, will use this render area instead.
                 * \param startIndex    Start index to count up from.
                 * \param numIndices    Number of color buffers to set as draw targets.
                 * \param modifiers     Modifiers to use while binding this viewport.
                 * \return Whether it could use this viewport as active render target or not.
                 *
                 * Sets this viewport as the active render target, all drawn meshes will be drawn onto this viewport.
                 *
                 ***********************************************/
                bool use(const Math::vec2ui &size, unsigned int startIndex, unsigned int numIndices, unsigned short modifiers);

                /********************************************//**
                 * \brief Blits a buffer to another hardware render target
                 *
                 * \param index     Index of the buffer to blit.
                 * \param dest      The render destination to blit to (0 = screen).
                 * \param offset    Offset from 0,0 of target.
                 * \param size      Width/Height of target.
                 * \param target    Which target to blit.
                 * \return Whether the data was successfully blit or not.
                 *
                 ***********************************************/
                bool blit(unsigned short index, RenderTarget *dest, const Math::vec2i &offset, const Math::vec2ui &size,
                          const RenderTarget::Target &target = RenderTarget::TARGET_COLOR);

                /********************************************//**
                 * \brief Fetch a color texture
                 *
                 * \param index Index of the color buffer to return.
                 * \return The color texture attached to the given index.
                 *
                 ***********************************************/
                Hardware::Texture *getColorTexture(unsigned short index) const;

                /********************************************//**
                 * \brief Fetch the depth texture
                 *
                 * \return The depth texture.
                 *
                 ***********************************************/
                Hardware::Texture *getDepthTexture() const;

                /********************************************//**
                 * \brief Fetch the hardware render target
                 *
                 * \return The hardware render target.
                 *
                 ***********************************************/
                const RenderTarget &getHardwareRenderTarget() const;
        };
    }
}

#endif

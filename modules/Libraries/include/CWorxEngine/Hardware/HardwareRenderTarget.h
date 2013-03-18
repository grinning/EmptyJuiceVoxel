/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Render Target : Object to hold either textures
 or render buffers to render to.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_RENDER_TARGET_H__
#define __HARDWARE_RENDER_TARGET_H__

#include "Hardware/HardwareTexture.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Object to hold textures to render to
        class CWE_DLL RenderTarget : public HardwareBase
        {
            //-----------------------------------------------------------------------
            public:
                // Define target points
                enum Target
                {
                    TARGET_COLOR    = GL_COLOR_ATTACHMENT0,
                    TARGET_DEPTH    = GL_DEPTH_ATTACHMENT
                };

                // Define rendering modifiers
                enum Modifier
                {
                    MOD_CULL_ON         = 0b0000000000000001,
                    MOD_CULL_OFF        = 0b0000000000000010,
                    MOD_CULL_FRONT      = 0b0000000000000100,
                    MOD_CULL_BACK       = 0b0000000000001000,
                    MOD_CULL_CW         = 0b0000000000010000,
                    MOD_CULL_CCW        = 0b0000000000100000,

                    MOD_DEPTH_ON        = 0b0000000001000000,
                    MOD_DEPTH_OFF       = 0b0000000010000000,
                    MOD_DEPTH_WRITE_ON  = 0b0000000100000000,
                    MOD_DEPTH_WRITE_OFF = 0b0000001000000000,

                    MOD_BLEND_ON        = 0b0000010000000000,
                    MOD_BLEND_OFF       = 0b0000100000000000,

                    MOD_CLEAR_COLOR     = 0b0001000000000000,
                    MOD_CLEAR_DEPTH     = 0b0010000000000000,
                    MOD_CLEAR_STENCIL   = 0b0100000000000000
                };

                // Define possible depth tests
                enum DepthTest
                {
                    DEPTH_ALWAYS        = GL_ALWAYS,
                    DEPTH_EQUAL         = GL_EQUAL,
                    DEPTH_LESS          = GL_LESS,
                    DEPTH_LESS_EQUAL    = GL_LEQUAL,
                    DEPTH_GREATER       = GL_GREATER,
                    DEPTH_GREATER_EQUAL = GL_GEQUAL,
                    DEPTH_NEVER         = GL_NEVER,
                    DEPTH_UNEQUAL       = GL_NOTEQUAL
                };

                // Define possible blending factors
                enum BlendFactor
                {
                    BLEND_FACTOR_ZERO                   = GL_ZERO,
                    BLEND_FACTOR_ONE                    = GL_ONE,
                    BLEND_FACTOR_SATURATE               = GL_SRC_ALPHA_SATURATE,

                    BLEND_FACTOR_DST_ALPHA              = GL_DST_ALPHA,
                    BLEND_FACTOR_DST_COLOR              = GL_DST_COLOR,
                    BLEND_FACTOR_SRC_ALPHA              = GL_SRC_ALPHA,
                    BLEND_FACTOR_SRC_COLOR              = GL_SRC_COLOR,
                    BLEND_FACTOR_ONE_MINUS_DST_ALPHA    = GL_ONE_MINUS_DST_ALPHA,
                    BLEND_FACTOR_ONE_MINUS_DST_COLOR    = GL_ONE_MINUS_DST_COLOR,
                    BLEND_FACTOR_ONE_MINUS_SRC_ALPHA    = GL_ONE_MINUS_SRC_ALPHA,
                    BLEND_FACTOR_ONE_MINUS_SRC_COLOR    = GL_ONE_MINUS_SRC_COLOR,

                    BLEND_FACTOR_CONST_ALPHA            = GL_CONSTANT_ALPHA,
                    BLEND_FACTOR_CONST_COLOR            = GL_CONSTANT_COLOR,
                    BLEND_FACTOR_ONE_MINUS_CONST_ALPHA  = GL_ONE_MINUS_CONSTANT_ALPHA,
                    BLEND_FACTOR_ONE_MINUS_CONST_COLOR  = GL_ONE_MINUS_CONSTANT_COLOR,
                };

                // Define possible blending equations
                enum BlendEquation
                {
                    BLEND_ADD               = GL_FUNC_ADD,
                    BLEND_SUBTRACT          = GL_FUNC_SUBTRACT,
                    BLEND_SUBTRACT_REVERSE  = GL_FUNC_REVERSE_SUBTRACT,
                    BLEND_MIN               = GL_MIN,
                    BLEND_MAX               = GL_MAX
                };

            //-----------------------------------------------------------------------
            protected:
                // Bound target
                static RenderTarget *_bound;

                /********************************************//**
                 * \brief Returns a buffer bit from target
                 *
                 * \param target    Target to convert.
                 * \return Buffer bit converted from the given target.
                 *
                 ***********************************************/
                static GLbitfield getBitfield(const Target &target);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Blits a render target onto another
                 *
                 * \param src       Source target (0 = screen).
                 * \param dst       Destination target (0 = screen).
                 * \param srcOffset Offset from 0,0 of source.
                 * \param srcSize   Width/Height of source.
                 * \param dstOffset Offset from 0,0 of destination.
                 * \param dstSize   Width/Height of destination.
                 * \param target    Which target to blit.
                 * \return Whether the blit was successful or not.
                 *
                 ***********************************************/
                static bool blit(RenderTarget *src, RenderTarget *dst,
                                 const Math::vec2i &srcOffset, const Math::vec2ui &srcSize,
                                 const Math::vec2i &dstOffset, const Math::vec2ui &dstSize,
                                 const Target &target = TARGET_COLOR);

                /********************************************//**
                 * \brief Sets render state modifiers to render with
                 *
                 * \param modifiers Modifiers to change the render state.
                 * \return void
                 *
                 ***********************************************/
                static void setModifiers(unsigned short modifiers);

                /********************************************//**
                 * \brief Sets the depth test
                 *
                 * \param depth The test to use.
                 * \return void
                 *
                 ***********************************************/
                static void depthTest(const DepthTest &depth = DEPTH_LESS_EQUAL);

                /********************************************//**
                 * \brief Sets the depth range
                 *
                 * \param near  Mapping of near clip plane.
                 * \param far   Mapping of far clip plane.
                 * \return void
                 *
                 ***********************************************/
                static void depthRange(double near = 0.0, double far = 1.0);

                /********************************************//**
                 * \brief Sets the blending factors
                 *
                 * \param src   Factor for incoming components.
                 * \param dst   Factor for existing components.
                 * \return void
                 *
                 ***********************************************/
                static void blendFactor(const BlendFactor &src = BLEND_FACTOR_ONE, const BlendFactor &dst = BLEND_FACTOR_ZERO);

                /********************************************//**
                 * \brief Sets the blending factor for RGB and Alpha separately
                 *
                 * \param srcRGB    Factor for incoming R,G,B components.
                 * \param srcAlpha  Factor for incoming A component.
                 * \param dstRGB    Factor for existing R,G,B components.
                 * \param dstAlpha  Factor for existing A component.
                 * \return void
                 *
                 ***********************************************/
                static void blendFactorSeperate(const BlendFactor &srcRGB   = BLEND_FACTOR_ONE,
                                                const BlendFactor &srcAlpha = BLEND_FACTOR_ONE,
                                                const BlendFactor &dstRGB   = BLEND_FACTOR_ZERO,
                                                const BlendFactor &dstAlpha = BLEND_FACTOR_ZERO);

                /********************************************//**
                 * \brief Sets the blending equation
                 *
                 * \param blend The equation to use.
                 * \return void
                 *
                 ***********************************************/
                static void blendEquation(const BlendEquation &blend = BLEND_ADD);

                /********************************************//**
                 * \brief Sets blending colors
                 *
                 * \param r The red component.
                 * \param g The green component.
                 * \param b The blue component.
                 * \param a The alpha component.
                 * \return void
                 *
                 ***********************************************/
                static void blendColor(const Math::vec4f &color = Math::vec4f(0.0f));

                /********************************************//**
                 * \brief Clears the currently bound target
                 *
                 * \param color     If true, color buffers will be cleared.
                 * \param depth     If true, depth buffer will be cleared.
                 * \param stencil   If true, stencil buffer will be cleared.
                 * \return void
                 *
                 ***********************************************/
                static void clear(bool color = true, bool depth = true, bool stencil = true);

                /********************************************//**
                 * \brief Sets clear values
                 *
                 * \param color     Color clear value.
                 * \param depth     Depth clear value.
                 * \param stencil   Stencil clear value.
                 * \return void
                 *
                 ***********************************************/
                static void clearValues(const Math::vec4f &color = Math::vec4f(0.0f), double depth = 1.0, int stencil = 0);

                /********************************************//**
                 * \brief Binds the screen
                 *
                 * \return void
                 *
                 ***********************************************/
                static void bindScreen();

            //-----------------------------------------------------------------------
            private:
                // Private Copy Constructor to prevent it
                RenderTarget(const RenderTarget &obj);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                RenderTarget();

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~RenderTarget();

                /********************************************//**
                 * \brief Manually bind the target
                 *
                 * \param size  Size of the render area.
                 * \return Whether the target is bound or not.
                 *
                 ***********************************************/
                bool bind(const Math::vec2ui &size) const;

                /********************************************//**
                 * \brief Manually bind the target
                 *
                 * \return Whether the target is bound or not.
                 *
                 ***********************************************/
                bool bind() const;

                /********************************************//**
                 * \brief Manually unbind the target
                 *
                 * \return void
                 *
                 ***********************************************/
                void unbind() const;

                /********************************************//**
                 * \brief Fetch whether this target is bound or not
                 *
                 * \return Whether this target is bound or not.
                 *
                 ***********************************************/
                bool isBound() const;

                /********************************************//**
                 * \brief Attaches a texture to the target
                 *
                 * \param target    The target to bind the texture to.
                 * \param tex       The texture to bind.
                 * \param index     The color index to use (only relevant when using TARGET_COLOR).
                 * \param mipmap    The mipmap level to bind.
                 * \param face      What face of a cubemap to attach (FACE_COUNT is none).
                 * \return Whether the texture is successfully attached or not.
                 *
                 ***********************************************/
                bool attachTexture(const Target &target, Texture &tex, unsigned int index = 0,
                                   unsigned int mipmap = 0, const Texture::Face &face = Texture::FACE_ALL) const;

                /********************************************//**
                 * \brief Sets the index of TARGET_COLOR to read from
                 *
                 * \param index The index to read from ( < 0 means do not read from any).
                 * \return Whether the index was successfully set or not.
                 *
                 ***********************************************/
                bool setReadIndex(int index = -1) const;

                /********************************************//**
                 * \brief Sets the index of TARGET_COLOR to write to
                 *
                 * \param index The index to write to ( < 0 means do not write to any).
                 * \return Whether the indices were successfully set or not.
                 *
                 ***********************************************/
                bool setWriteIndex(int index = -1) const;

                /********************************************//**
                 * \brief Sets multiple indices of TARGET_COLOR to write to
                 *
                 * \param startIndex    Start index to count up from.
                 * \param numIndices    Number of indices to set.
                 * \return Whether the indices were successfully set or not.
                 *
                 ***********************************************/
                bool setWriteIndices(unsigned int startIndex, unsigned int numIndices) const;
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Hardware Texture : Texture stored in the GPU

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __HARDWARE_TEXTURE_H__
#define __HARDWARE_TEXTURE_H__

#include "CWorxConsole.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Texture stored on the GPU
        class CWE_DLL Texture : public HardwareBase
        {
            //-----------------------------------------------------------------------
            public:
                // Define the GL Texture types possible
                enum Type
                {
                    TYPE_1D     = GL_TEXTURE_1D,
                    TYPE_2D     = GL_TEXTURE_2D,
                    TYPE_3D     = GL_TEXTURE_3D,
                    TYPE_CUBE   = GL_TEXTURE_CUBE_MAP
                };

                // Define Cube map faces
                enum Face
                {
                    FACE_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                    FACE_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                    FACE_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                    FACE_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                    FACE_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                    FACE_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,

                    // Also acts as count
                    FACE_ALL
                };

                // Define the possible Pixel Formats
                enum PixelFormat
                {
                    PIXEL_FORMAT_UNKNOWN,

                    // Known
                    PIXEL_FORMAT_DEPTH          = GL_DEPTH_COMPONENT,
                    PIXEL_FORMAT_RED            = GL_RED,
                    PIXEL_FORMAT_RG             = GL_RG,
                    PIXEL_FORMAT_RGB            = GL_RGB,
                    PIXEL_FORMAT_RGBA           = GL_RGBA,
                    PIXEL_FORMAT_SRGB           = GL_SRGB,
                    PIXEL_FORMAT_SRGBA          = GL_SRGB_ALPHA,

                    PIXEL_FORMAT_DEPTH16        = GL_DEPTH_COMPONENT16,
                    PIXEL_FORMAT_DEPTH24        = GL_DEPTH_COMPONENT24,
                    PIXEL_FORMAT_DEPTH32F       = GL_DEPTH_COMPONENT32F,

                    PIXEL_FORMAT_R8             = GL_R8,
                    PIXEL_FORMAT_R8_SNORM       = GL_R8_SNORM,
                    PIXEL_FORMAT_R16            = GL_R16,
                    PIXEL_FORMAT_R16_SNORM      = GL_R16_SNORM,
                    PIXEL_FORMAT_RG8            = GL_RG8,
                    PIXEL_FORMAT_RG8_SNORM      = GL_RG8_SNORM,
                    PIXEL_FORMAT_RG16           = GL_RG16,
                    PIXEL_FORMAT_RG16_SNORM     = GL_RG16_SNORM,
                    PIXEL_FORMAT_R3_G3_B2       = GL_R3_G3_B2,
                    PIXEL_FORMAT_RGB4           = GL_RGB4,
                    PIXEL_FORMAT_RGB5           = GL_RGB5,
                    PIXEL_FORMAT_RGB8           = GL_RGB8,
                    PIXEL_FORMAT_RGB8_SNORM     = GL_RGB8_SNORM,
                    PIXEL_FORMAT_RGB10          = GL_RGB10,
                    PIXEL_FORMAT_RGB12          = GL_RGB12,
                    PIXEL_FORMAT_RGB16_SNORM    = GL_RGB16_SNORM,
                    PIXEL_FORMAT_RGBA2          = GL_RGBA2,
                    PIXEL_FORMAT_RGBA4          = GL_RGBA4,
                    PIXEL_FORMAT_RGB5_A1        = GL_RGB5_A1,
                    PIXEL_FORMAT_RGBA8          = GL_RGBA8,
                    PIXEL_FORMAT_RGBA8_SNORM    = GL_RGBA8_SNORM,
                    PIXEL_FORMAT_RGB10_A2       = GL_RGB10_A2,
                    PIXEL_FORMAT_RGB10_A2UI     = GL_RGB10_A2UI,
                    PIXEL_FORMAT_RGBA12         = GL_RGBA12,
                    PIXEL_FORMAT_RGBA16         = GL_RGBA16,

                    PIXEL_FORMAT_SRGB8          = GL_SRGB8,
                    PIXEL_FORMAT_SRGB8_A8       = GL_SRGB8_ALPHA8,

                    PIXEL_FORMAT_R16F           = GL_R16F,
                    PIXEL_FORMAT_RG16F          = GL_RG16F,
                    PIXEL_FORMAT_RGB16F         = GL_RGB16F,
                    PIXEL_FORMAT_RGBA16F        = GL_RGBA16F,
                    PIXEL_FORMAT_R32F           = GL_R32F,
                    PIXEL_FORMAT_RG32F          = GL_RG32F,
                    PIXEL_FORMAT_RGB32F         = GL_RGB32F,
                    PIXEL_FORMAT_RGBA32F        = GL_RGBA32F,
                    PIXEL_FORMAT_R11F_G11F_B10F = GL_R11F_G11F_B10F,

                    PIXEL_FORMAT_RGB9_E5        = GL_RGB9_E5,

                    PIXEL_FORMAT_R8I            = GL_R8I,
                    PIXEL_FORMAT_R8UI           = GL_R8UI,
                    PIXEL_FORMAT_R16I           = GL_R16I,
                    PIXEL_FORMAT_R16UI          = GL_R16UI,
                    PIXEL_FORMAT_R32I           = GL_R32I,
                    PIXEL_FORMAT_R32UI          = GL_R32UI,
                    PIXEL_FORMAT_RG8I           = GL_RG8I,
                    PIXEL_FORMAT_RG8UI          = GL_RG8UI,
                    PIXEL_FORMAT_RG16I          = GL_RG16I,
                    PIXEL_FORMAT_RG16UI         = GL_RG16UI,
                    PIXEL_FORMAT_RG32I          = GL_RG32I,
                    PIXEL_FORMAT_RG32UI         = GL_RG32UI,
                    PIXEL_FORMAT_RGB8I          = GL_RGB8I,
                    PIXEL_FORMAT_RGB8UI         = GL_RGB8UI,
                    PIXEL_FORMAT_RGB16I         = GL_RGB16I,
                    PIXEL_FORMAT_RGB16UI        = GL_RGB16UI,
                    PIXEL_FORMAT_RGB32I         = GL_RGB32I,
                    PIXEL_FORMAT_RGB32UI        = GL_RGB32UI,
                    PIXEL_FORMAT_RGBA8I         = GL_RGBA8I,
                    PIXEL_FORMAT_RGBA8UI        = GL_RGBA8UI,
                    PIXEL_FORMAT_RGBA16I        = GL_RGBA16I,
                    PIXEL_FORMAT_RGBA16UI       = GL_RGBA16UI,
                    PIXEL_FORMAT_RGBA32I        = GL_RGBA32I,
                    PIXEL_FORMAT_RGBA32UI       = GL_RGBA32UI
                };

                // Define the possible Pixel Sizes
                enum PixelSize
                {
                    PIXEL_SIZE_BYTE                         = GL_BYTE,
                    PIXEL_SIZE_SHORT                        = GL_SHORT,
                    PIXEL_SIZE_INT                          = GL_INT,
                    PIXEL_SIZE_FLOAT                        = GL_FLOAT,
                    PIXEL_SIZE_UNSIGNED_BYTE                = GL_UNSIGNED_BYTE,
                    PIXEL_SIZE_UNSIGNED_SHORT               = GL_UNSIGNED_SHORT,
                    PIXEL_SIZE_UNSIGNED_INT                 = GL_UNSIGNED_INT
                };

                // Define minifying filters
                enum MinFilter
                {
                    MIN_FILTER_LINEAR                   = GL_LINEAR,
                    MIN_FILTER_LINEAR_MIPMAP_LINEAR     = GL_LINEAR_MIPMAP_LINEAR,
                    MIN_FILTER_LINEAR_MIPMAP_NEAREST    = GL_LINEAR_MIPMAP_NEAREST,
                    MIN_FILTER_NEAREST                  = GL_NEAREST,
                    MIN_FILTER_NEAREST_MIPMAP_LINEAR    = GL_NEAREST_MIPMAP_LINEAR,
                    MIN_FILTER_NEAREST_MIPMAP_NEAREST   = GL_NEAREST_MIPMAP_NEAREST
                };

                // Define magnifying filters
                enum MagFilter
                {
                    MAG_FILTER_LINEAR   = GL_LINEAR,
                    MAG_FILTER_NEAREST  = GL_NEAREST
                };

                // Define texture wrap modes
                enum Wrap
                {
                    WRAP_CLAMP_TO_BORDER    = GL_CLAMP_TO_BORDER,
                    WRAP_CLAMP_TO_EDGE      = GL_CLAMP_TO_EDGE,
                    WRAP_MIRRORED_REPEAT    = GL_MIRRORED_REPEAT,
                    WRAP_REPEAT             = GL_REPEAT
                };

            //-----------------------------------------------------------------------
            protected:
                // Properties
                const Type _type;

                /********************************************//**
                 * \brief Converts the internal format to the format of the pixel data
                 *
                 * \param internal  Format given to the texture.
                 * \return The format converted from the pixel format.
                 *
                 ***********************************************/
                static GLenum getFormat(const PixelFormat &internal);

            //-----------------------------------------------------------------------
            private:
                // Private Copy Constructor to prevent it
                Texture(const Texture &obj);

            //-----------------------------------------------------------------------
            public:
                // To attach to render target
                friend class RenderTarget;

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type      The texture type to generate.
                 * \param format    Format of the input pixels.
                 * \param size      Size of the input pixels.
                 * \param data      A pointer to the data to fill the texture with.
                 * \param size      Size of the texture.
                 *
                 ***********************************************/
                Texture(const Type &type, const PixelFormat &format, const PixelSize &pixSize, const void *data, const Math::vec3ui &size, const Face &face = FACE_ALL);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param file      The path and name to the file to load.
                 * \param mipmaps   Whether to generate mipmaps or not.
                 * \param channels  The count of channels (0 = auto, 2 = luminance + alpha).
                 *
                 ***********************************************/
                Texture(const std::string &file, bool mipmaps = true, unsigned int channels = 0);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Texture();

                /********************************************//**
                 * \brief Fetch the texture type
                 *
                 * \return The type of the texture.
                 *
                 ***********************************************/
                const Type &getType() const;

                /********************************************//**
                 * \brief Fetch the pixel format of the texture
                 *
                 * \return The pixel format of the texture.
                 *
                 ***********************************************/
                PixelFormat getPixelFormat() const;

                /********************************************//**
                 * \brief Fetch the width of the texture
                 *
                 * \return The width of the texture.
                 *
                 ***********************************************/
                unsigned int getWidth() const;

                /********************************************//**
                 * \brief Fetch the height of the txture
                 *
                 * \return The height of the texture.
                 *
                 ***********************************************/
                unsigned int getHeight() const;

                /********************************************//**
                 * \brief Returns the depth of the texture
                 *
                 * \return The depth of the texture.
                 *
                 ***********************************************/
                unsigned int getDepth() const;

                /********************************************//**
                 * \brief Manually binds the texture to a certain texture unit
                 *
                 * \param textureUnit   The unit to bind it to, cannot be 0 (reserved for editing).
                 * \return Whether the texture was successfully bound or not.
                 *
                 ***********************************************/
                bool bind(unsigned int textureUnit) const;

                /********************************************//**
                 * \brief Returns whether this texture can be used or not
                 *
                 * \return Whether the texture is renderable or not.
                 *
                 ***********************************************/
                bool isRenderable() const;

                /********************************************//**
                 * \brief Sets the minifying and magnifying filters
                 *
                 * \param min   The minifying filter.
                 * \param mag   The magnifying filter.
                 * \return Whether the filters were successfully set or not.
                 *
                 ***********************************************/
                bool setFilters(const MinFilter &min, const MagFilter &mag);

                /********************************************//**
                 * \brief Sets the texture wrap mode
                 *
                 * \param r The r (u, x) direction.
                 * \param s The s (v, y) direction.
                 * \param t The t (w, z) direction.
                 * \return Whether the wrap was successfully set or not.
                 *
                 ***********************************************/
                bool setWrap(const Wrap &r, const Wrap &s, const Wrap &t);

                /********************************************//**
                 * \brief Sets the texture wrap mode
                 *
                 * \param wrap  r,s,t (u,v,w) (x,y,z) directions.
                 * \return Whether the wrap was successfully set or not.
                 *
                 ***********************************************/
                bool setWrap(const Wrap &wrap);

                /********************************************//**
                 * \brief Writes new bitmap data to the texture
                 *
                 * \param format    Format of the input pixels.
                 * \param pixSize   Size of the input pixels.
                 * \param data      A pointer to the data to fill the texture with.
                 * \param size      Size of the texture
                 * \param face      Face of a cubemap to write to.
                 * \return Whether the data was successfully written or not.
                 *
                 * This write method actually reallocates the texture data. Do not use if not resizing!
                 *
                 ***********************************************/
                bool write(const PixelFormat &format, const PixelSize &pixSize, const void *data, const Math::vec3ui &size, const Face &face = FACE_ALL);

                /********************************************//**
                 * \brief Writes bitmap data to a part of the texture
                 *
                 * \param format    Format of the input pixels.
                 * \param pixSize   Size of the input pixels.
                 * \param data      A pointer to the data to write.
                 * \param offset    A vector describing the offset within the texture to write to.
                 * \param size      Size of the data.
                 * \return Whether the data was successfully written or not.
                 *
                 * This write method rewrites a certain part of the texture data.
                 *
                 ***********************************************/
                bool write(const PixelFormat &format, const PixelSize &pixSize, const Math::vec3ui &offset, const void *data, const Math::vec3ui &size, const Face &face = FACE_ALL);

                /********************************************//**
                 * \brief Loads a texture from a file
                 *
                 * \param file      The path and name to the file to load.
                 * \param mipmaps   Whether to generate mipmaps or not.
                 * \param channels  The count of channels (0 = auto, 2 = luminance + alpha).
                 * \return Whether the texture was successfully loaded or not.
                 *
                 * Loads an external texture from file using the SOIL library.
                 *
                 ***********************************************/
                bool load(const std::string &file, bool mipmaps = true, unsigned int channels = 0);
        };
    }
}

#endif

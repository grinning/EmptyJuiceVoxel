/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Font : A collection of glyphs describing a face object
 of FreeType.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __FONT_H__
#define __FONT_H__

#include "Hardware/HardwareTexture.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! A collection of glyphs describing a face object of FreeType
    class CWE_DLL Font
    {
        //-----------------------------------------------------------------------
        public:
            // Define a single character
            struct Character
            {
                Math::vec2ui size;
                float x;  // X coordinate
                float y;  // Y coordinate (bottom of character, upside down!)
                float x2; // 'right' coordinate

                // Horizontal Layout
                unsigned int horiBearingX;
                unsigned int horiBearingY;
                unsigned int horiAdvance;

                // Vertical Layout
                unsigned int vertBearingX;
                unsigned int vertBearingY;
                unsigned int vertAdvance;
            };

            // CONSTANT EMPTY
            static const Character EMPTY_CHARACTER;

        //-----------------------------------------------------------------------
        protected:
            // Define a map of characters
            typedef std::map<unsigned short, Character> CharacterMap;

            // Properties
            FT_Face _face;
            bool _hasHorizontal;
            bool _hasVertical;

            // Font Atlas
            Hardware::Texture *_atlas;
            CharacterMap _characters;
            Math::vec2ui _size; // Of entire Font Atlas

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param file  The file to open.
             * \param size  The width and hight to set the font to.
             * \param first First character to load.
             * \param num   Number of characters to load.
             *
             ***********************************************/
            Font(const std::string &file, const Math::vec2ui &size = 16, const unsigned short first = 0, const unsigned short num = 256);

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Font();

            /********************************************//**
             * \brief Fetch whether the font was loaded successfully or not
             *
             * \return Whether the font was loaded successfully.
             *
             * Fetch whether the font was loaded successfully or not, will return false if the size is locked!
             *
             ***********************************************/
            bool isLoaded() const;

            /********************************************//**
             * \brief Fetch whether this font has a horizontal layout or not
             *
             * \return Whether this font has a horizontal layout or not.
             *
             ***********************************************/
            bool hasHorizontal() const;

            /********************************************//**
             * \brief Fetch whether this font has a vertical layout or not
             *
             * \return Whether this font has a vertical layout or not.
             *
             ***********************************************/
            bool hasVertical() const;

            /********************************************//**
             * \brief Sets both the height and width of the font
             *
             * \param size  The width and height to set.
             * \return Whether the size could be set or not.
             *
             ***********************************************/
            bool setSize(const Math::vec2ui &size);

            /********************************************//**
             * \brief Sets both the height and width of the font and a new character range
             *
             * \param size  The width and height to set.
             * \param first First character to load.
             * \param num   Number of characters to load.
             * \return Whether the size could be set or not.
             *
             ***********************************************/
            bool setSize(const Math::vec2ui &size, const unsigned short first, const unsigned short num = 1);

            /********************************************//**
             * \brief Locks the size, cannot set a new size, only the atlas can be used afterwards
             *
             * \return Whether the font could be locked.
             *
             * Locks the size, isLoaded() will always return false afterwards!
             *
             ***********************************************/
            bool lockSize();

            /********************************************//**
             * \brief Fetch the font atlas, a texture containing all characters
             *
             * \return The font atlas.
             *
             ***********************************************/
            Hardware::Texture *getAtlas() const;

            /********************************************//**
             * \brief Fetch the atlas width
             *
             * \return The width of the atlas.
             *
             ***********************************************/
            unsigned int getAtlasWidth() const;

            /********************************************//**
             * \brief Fetch the atlas height
             *
             * \return The height of the atlas.
             *
             ***********************************************/
            unsigned int getAtlasHeight() const;

            /********************************************//**
             * \brief Fetch the atlas size
             *
             * \return The size of the atlas.
             *
             ***********************************************/
            const Math::vec2ui &getAtlasSize() const;

            /********************************************//**
             * \brief Returns a character from the atlas
             *
             * \param character The character to search for.
             * \return A struct containing all the data of the character.
             *
             ***********************************************/
            const Character &getCharacter(const unsigned short character) const;
    };
}

#endif

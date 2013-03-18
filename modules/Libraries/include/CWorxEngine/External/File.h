/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 File : An interface to read from and write to external
 files relative to the application's directory.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __FILE_H__
#define __FILE_H__

#include "CWorxEnginePrerequisites.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // External namespace
    namespace External
    {
        //! An interface to read from and write to an external file
        class CWE_DLL File
        {
            //-----------------------------------------------------------------------
            public:
                // Define the opening mode of files
                enum OpenMode
                {
                    MODE_READ                 = 0b001,
                    MODE_READ_WRITE           = 0b011,
                    MODE_READ_WRITE_APPEND    = 0b111,
                    MODE_WRITE                = 0b010,
                    MODE_WRITE_APPEND         = 0b110
                };

            //-----------------------------------------------------------------------
            protected:
                // File
                const OpenMode _mode;
                const std::string _file;
                std::fstream _iof;

                // Reset flags and seek (to read/write)
                void init(const unsigned int pos, const std::_Ios_Seekdir seekdir = std::ios::beg);

                // Static helper function to extract ios openmode
                static std::ios::openmode getOpenMode(const OpenMode &mode);

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Creates a file
                 *
                 * \param name  The file to create.
                 * \return void
                 *
                 * Creates a file, will erase content if the file already exists!
                 *
                 ***********************************************/
                static void create(const std::string &file);

                /********************************************//**
                 * \brief Renames any file and/or it's directory
                 *
                 * \param path     The directory the file lives in.
                 * \param oldName  The file to rename.
                 * \param newName  The name to give to the file.
                 * \return Whether it successfully changed the name.
                 *
                 ***********************************************/
                static bool rename(const std::string &path, const std::string &oldName, const std::string &newName);

                /********************************************//**
                 * \brief Removes any file
                 *
                 * \param name  The file to remove.
                 * \return Whether it was successfully removed.
                 *
                 ***********************************************/
                static bool remove(const std::string &file);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param name  The path and name of the file.
                 * \param mode  The mode in which to open the file.
                 *
                 ***********************************************/
                File(const std::string &file, const OpenMode &mode = MODE_READ_WRITE);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~File();

                /********************************************//**
                 * \brief Fetch the openmode of the file
                 *
                 * \return The openmode of the file.
                 *
                 ***********************************************/
                const OpenMode &getMode() const;

                /********************************************//**
                 * \brief Fetch the file name and directory
                 *
                 * \return The file name and directory.
                 *
                 ***********************************************/
                const std::string &getFile() const;

                /********************************************//**
                 * \brief Returns the file name of the last opened file
                 *
                 * \return The file name.
                 *
                 ***********************************************/
                std::string getName() const;

                /********************************************//**
                 * \brief Returns the directory the file lives in
                 *
                 * \return The directory.
                 *
                 ***********************************************/
                std::string getPath() const;

                /********************************************//**
                 * \brief Fetch whether the file was successfully opened
                 *
                 * \return Whether the file is open.
                 *
                 ***********************************************/
                bool isOpen() const;

                /********************************************//**
                 * \brief Closes the file
                 *
                 * \return void
                 *
                 ***********************************************/
                void close();

                /********************************************//**
                 * \brief Fetch whether it can operate according to a mode
                 *
                 * \param mode  The mode to check for.
                 * \return Whether it can operate according to the given mode.
                 *
                 ***********************************************/
                bool canOperate(const OpenMode &mode) const;

                /********************************************//**
                 * \brief Fetch the file size in bytes
                 *
                 * \return The file size in bytes.
                 *
                 * Fetches the file size in bytes, to do this it seeks to the end of the file.
                 *
                 ***********************************************/
                unsigned int getSize();

                /********************************************//**
                 * \brief Fetch the file size in lines
                 *
                 * \return The number of lines in the file.
                 *
                 * Fetches the number of lines in the file, to do this it seeks to the end of the file.
                 *
                 ***********************************************/
                unsigned int getLines();

                /********************************************//**
                 * \brief Seeks to a given byte position
                 *
                 * \param line      The line 'offset' in lines.
                 * \param position  The position in bytes.
                 * \return void
                 *
                 ***********************************************/
                void setPosition(const unsigned int line, const unsigned int position = 0);

                /********************************************//**
                 * \brief Fetch the position in the file
                 *
                 * \return The position in the file.
                 *
                 * The returned position may be altered by seek(), read() and alike.
                 *
                 ***********************************************/
                unsigned int getPosition();

                /********************************************//**
                 * \brief Fetch whether the end of the file is reached
                 *
                 * \return Whether the end of the file is reached (EOF) or not.
                 *
                 ***********************************************/
                bool atEOF() const;

                /********************************************//**
                 * \brief Ignores the next character(s)
                 *
                 * \param numChars  The amount of characters to ignore.
                 * \return Whether the character(s) were successfully ignored or not.
                 *
                 ***********************************************/
                bool ignore(unsigned int numChars = 1);

                /********************************************//**
                 * \brief Ignores the next character(s)
                 *
                 * \param numChars  The amount of characters to read.
                 * \param delim     The deliming character.
                 * \return Whether the character(s) were successfully ignored or not.
                 *
                 ***********************************************/
                bool ignore(unsigned int numChars, char delim);

                /********************************************//**
                 * \brief Ignores the next line
                 *
                 * \return Whether the line was successfully ignored or not.
                 *
                 ***********************************************/
                bool ignoreLine();

                /********************************************//**
                 * \brief Reads the next character(s)
                 *
                 * \param numChars  The amount of characters to read.
                 * \return The read character(s).
                 *
                 ***********************************************/
                std::string read(unsigned int numChars = 1);

                /********************************************//**
                 * \brief Reads the next character(s)
                 *
                 * \param numChars  The amount of characters to read.
                 * \param delim     The deliming character.
                 * \return The read character(s).
                 *
                 ***********************************************/
                std::string read(unsigned int numChars, char delim);

                /********************************************//**
                 * \brief Reads the next line
                 *
                 * \return The read line.
                 *
                 ***********************************************/
                std::string readLine();

                /********************************************//**
                 * \brief Reads all the content and returns a string
                 *
                 * \return The read content.
                 *
                 ***********************************************/
                std::string readAll();

                /********************************************//**
                 * \brief Writes a block of data to the file
                 *
                 * \param str   The string to write.
                 * \return Itself.
                 *
                 ***********************************************/
                File &write(const std::string &str);

                //-----------------------------------------------------------------------
                // 'Stream' input
                template <typename _type>
                File &operator<<(const _type &val)
                {
                    // Return if not able to write
                    if(!canOperate(MODE_WRITE)) return *this;

                    // Init and write
                    init(0, std::ios::cur);
                    _iof << val;

                    return *this;
                }

                //-----------------------------------------------------------------------
                // 'Stream' output
                template <typename _type>
                File &operator>>(_type &val)
                {
                    // Return if not able to read
                    if(!canOperate(MODE_READ)) return *this;

                    // Init and read
                    init(0, std::ios::cur);
                    _iof >> val;

                    return *this;
                }
        };
    }
}

#endif

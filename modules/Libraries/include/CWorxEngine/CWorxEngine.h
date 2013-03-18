/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 OpenGL used as 2D/3D graphics rendering API, in combination
 with the GLFW and GLEW libraries. FreeType used for
 accessing and rendering facetypes. SOIL used for loading
 images from memory.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __CWORX_ENGINE_H__
#define __CWORX_ENGINE_H__

// Standard
#include "Geometry/Primitive.h"
#include "Scene/Scene.h"

// External (Import/Export)
#ifndef CWE_NO_WAVEFRONT
#   include "External/MTLFile.h"
#   include "External/OBJFile.h"
#endif

// GUI
#ifndef CWE_NO_GUI
#   include "GUI/Font.h"
#   include "GUI/Overlay.h"
#endif

// CWE (CWorx Engine) namespace
namespace CWE
{
    /********************************************//**
     * \brief Fetch the Console
     *
     * \return A handle to the console.
     *
     * This method purely exists as a shortcut to Console::GET().
     *
     ***********************************************/
    inline Console &Console()
        { return Console::GET(); }

    /********************************************//**
     * \brief Performs the Console openWindow method
     *
     * \param width         The width of the OpenGL context.
     * \param height        The height of the OpenGL context.
     * \param title         The title of the window.
     * \param vsync         If true, vertical synchronization will be enabled.
     * \param resizeable    Whether the user can resize the window (no effect in fullscreen).
     * \return Whether the window was successfully opened or not.
     *
     ***********************************************/
    inline bool openWindow(const int &width, const int &height, const std::string &title, bool vsync = false, bool resizeable = true)
        { return Console::GET().openWindow(width, height, title, vsync, resizeable); }

    /********************************************//**
     * \brief Performs the Console closeWindow method
     *
     * \return void
     *
     ***********************************************/
    inline void closeWindow()
        { Console::GET().closeWindow(); }

    /********************************************//**
     * \brief Performs the Console render method
     *
     * \return Whether the render loop can continue or not.
     *
     ***********************************************/
    inline bool render()
        { return Console::GET().render(); }

    /********************************************//**
     * \brief Terminates the current console and all the CWorxEngine objects
     *
     * \return void
     *
     ***********************************************/
    inline void terminate()
        { delete &Console::GET(); }
}

#endif

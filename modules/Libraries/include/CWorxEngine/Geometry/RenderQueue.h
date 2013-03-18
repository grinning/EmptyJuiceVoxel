/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Render Queue : Stores renderables in the most efficient
 way to achieve as few state changes as possible.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __RENDER_QUEUE_H__
#define __RENDER_QUEUE_H__

#include "Geometry/Renderable.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Stores renderables in the most efficient way to render
        class CWE_DLL RenderQueue
        {
            //-----------------------------------------------------------------------
            public:
                // Define a render callback
                typedef Callback::BinaryBase<const Renderable&, const Shader::Shader&> renderCallback;

            //-----------------------------------------------------------------------
            protected:
                // Define a list of renderables
                typedef std::set<Renderable*> RenderableList;

                // Define a list of renderable pointers
                typedef std::set<Renderable::Pointer*, Renderable::Pointer::sort> PointerList;

                // Define actual queue sorted on pass
                typedef std::map<const Shader::Pass, PointerList> Queue;

                // Properties
                RenderableList _renderables;
                Queue _queue;

                /********************************************//**
                 * \brief Adds a renderable pointer to the render queue
                 *
                 * \param pass  Shader pass the pointer belongs to.
                 * \param pntr  The pointer to be added.
                 * \return Whether the pointer was added or not.
                 *
                 * Adds a renderable pointer to the render queue, which is to be rendered.
                 * If the pointer was already added it will return false.
                 *
                 ***********************************************/
                bool addPointer(const Shader::Pass &pass, Renderable::Pointer *pntr);

            //-----------------------------------------------------------------------
            public:
                // So it can call 'addPointer'
                friend class Renderable;

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param pass  Passes to store in this queue.
                 *
                 ***********************************************/
                RenderQueue(unsigned int pass);

                /********************************************//**
                 * \brief Fetch if the queue contains a certain pass
                 *
                 * \return Whether it contains the pass or not.
                 *
                 ***********************************************/
                bool hasPass(const Shader::Pass &pass) const;

                /********************************************//**
                 * \brief Adds a Renderable to the queue
                 *
                 * \param rend  The renderable to add.
                 * \return Whether the renderable could be added or not.
                 *
                 * Adds a renderable to the queue, the template allows elaborate type specific materials/IDs.
                 *
                 ***********************************************/
                void addRenderable(Renderable &rend);

                /********************************************//**
                 * \brief Returns whether it has the specified renderable
                 *
                 * \param rend  The specified renderable.
                 * \return Whether it has the specified renderable or not.
                 *
                 ***********************************************/
                bool hasRenderable(const Renderable &rend) const;

                /********************************************//**
                 * \brief Fetch the amount of renderables
                 *
                 * \return The amount of renderables.
                 *
                 ***********************************************/
                unsigned int getNumRenderables() const;

                /********************************************//**
                 * \brief Removes a renderable from the queue
                 *
                 * \param rend  The renderable to remove.
                 * \return Whether the renderable could be removed or not.
                 *
                 ***********************************************/
                bool removeRenderable(const Renderable &rend);

                /********************************************//**
                 * \brief Updates the render queue
                 *
                 * \return void
                 *
                 ***********************************************/
                void update();

                /********************************************//**
                 * \brief Updates (and processes) the render queue
                 *
                 * \param cam       Camera matrix to apply.
                 * \param invCam    Inverse camera matrix to apply.
                 * \return void
                 *
                 * If cam and invCam are given, it will also process the queue,
                 * this is significantly faster than calling both functions separately!
                 *
                 ***********************************************/
                void update(const Math::mat4f &cam, const Math::mat4f &invCam);

                /********************************************//**
                 * \brief Processes data for a certain camera setup
                 *
                 * \param cam       Camera matrix to apply.
                 * \param invCam    Inverse camera matrix to apply.
                 * \return void
                 *
                 ***********************************************/
                void process(const Math::mat4f &cam, const Math::mat4f &invCam);

                /********************************************//**
                 * \brief Renders the render queue
                 *
                 * \param pass      Shader pass to render with.
                 * \param callback  Callback function to call before every geometry ID render.
                 * \param prim      Primitive type to exclusively render, use PRIMITIVE_ANY to render all types.
                 * \return Whether it could render with the given shader pass or not.
                 *
                 * Render the render queue, the callback is called for every occurrence of a renderable,
                 * which means it could be called multiple times per renderable.
                 *
                 ***********************************************/
                bool render(const Shader::Pass &pass, renderCallback &callback, const Hardware::Object::PrimitiveType &prim = Hardware::Object::PRIMITIVE_ANY) const;
        };
    }
}

#endif

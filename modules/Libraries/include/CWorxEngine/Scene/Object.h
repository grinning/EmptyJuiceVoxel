/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Object : A renderable at a certain point and orientation
 in 3D space, through node mechanics.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Geometry/Renderable.h"
#include "Scene/Node.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! A renderable located at a certain space in 3D
    class CWE_DLL Object : public Geometry::Renderable, public Node
    {
        //-----------------------------------------------------------------------
        protected:
            // Properties
            Math::vec3f _origin;
            Math::mat4f _camMatrix;
            Math::mat4f _invCamMatrix; // 3x3 Transpose for normal matrix

            /********************************************//**
             * \brief Updates the object specific material properties
             *
             * \return Whether it updated anything or not.
             *
             ***********************************************/
            virtual bool updateProperties();

            /********************************************//**
             * \brief Calculates properties ready to be bound
             *
             * \param cam       Camera matrix to apply.
             * \param invCam    Inverse camera matrix to apply.
             * \return void
             *
             ***********************************************/
            virtual void processProperties(const Math::mat4f &cam, const Math::mat4f &invCam);

            /********************************************//**
             * \brief Binds properties to a given shader
             *
             * \param shad  Shader to bind to.
             * \return void
             *
             ***********************************************/
            virtual void bindProperties(const Shader::Shader &shad) const;

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param mesh      The mesh to use.
             * \param parent    The parent node.
             *
             ***********************************************/
            Object(Geometry::Mesh &mesh, Node *parent = 0);

            /********************************************//**
             * \brief Constructor
             *
             * \param mesh          The mesh to use.
             * \param position      The position of the object in parent space.
             * \param orientation   The orientation of the object.
             * \param scale         The scale of the object.
             * \param parent        The parent node.
             * \param type          Material type to accept.
             *
             ***********************************************/
            Object(Geometry::Mesh &mesh, const Math::vec3f &position, const Math::fquat &orientation, const Math::vec3f &scale, Node *parent = 0);

            /********************************************//**
             * \brief Sets the origin of the object
             *
             * \param vec   The origin in vector form.
             * \return void
             *
             ***********************************************/
            void setOrigin(const Math::vec3f &vec);

            /********************************************//**
             * \brief Sets the origin of the object
             *
             * \param x The x component.
             * \param y The y component.
             * \param z The z component.
             * \return void
             *
             ***********************************************/
            void setOrigin(const float x, const float y, const float z);

            /********************************************//**
             * \brief Fetch the origin of the object
             *
             * \return The origin of the object.
             *
             ***********************************************/
            const Math::vec3f &getOrigin() const;

            /********************************************//**
             * \brief Creates transformation matrices
             *
             * \return  Whether it actually recalculated anything.
             *
             * Creates the transformation matrices (body to world and world to body),
             * won't automatically update when calling 'update()'!
             *
             ***********************************************/
            virtual bool updateMatrices();
    };
}

#endif

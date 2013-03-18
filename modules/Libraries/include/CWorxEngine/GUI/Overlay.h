/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Overlay : A 2D Container describing its position,
 orientation and scale in window space.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include "Geometry/Renderable.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! Describes a Cartesian Space
    class CWE_DLL Overlay : public Geometry::Renderable
    {
        //-----------------------------------------------------------------------
        protected:
            // Define a list of overlays
            typedef std::list<Overlay*> OverlayList;

            // Parent/Child
            Overlay *_parent;
            OverlayList _children;

            // Positioning
            Math::mat2f _orientation;
            Math::vec2f _position;
            Math::vec2f _scale;

            // Update flag
            bool _update;

            // Actual usage
            Math::mat3f _matrix;
            Math::mat3f _invMatrix;

            /********************************************//**
             * \brief Updates the overlay specific material properties
             *
             * \return Whether it updated anything or not.
             *
             ***********************************************/
            virtual bool updateProperties();

            /********************************************//**
             * \brief Binds properties to a given shader
             *
             * \param shad  Shader to bind to.
             * \return void
             *
             ***********************************************/
            virtual void bindProperties(const Shader::Shader &shad) const;

            //-----------------------------------------------------------------------
            // Overlay Mesh
            static Geometry::Mesh *_mesh;

            // Generate the mesh above
            static Geometry::Mesh *generateMesh();

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param parent    The parent overlay.
             *
             ***********************************************/
            Overlay(Overlay *parent = 0);

            /********************************************//**
             * \brief Constructor
             *
             * \param position      The position of the overlay in NDC space.
             * \param orientation   The orientation of the overlay.
             * \param scale         The scale of the overlay.
             * \param parent        The parent overlay.
             *
             ***********************************************/
            Overlay(const Math::vec2f &position, const Math::mat2f &orientation = Math::mat2f(1.0f), const Math::vec2f &scale = Math::vec2f(1.0f), Overlay *parent = 0);

            /********************************************//**
             * \brief Fetch the body to world matrix
             *
             * \return The matrix.
             *
             ***********************************************/
            const Math::mat3f &getMatrix() const;

            /********************************************//**
             * \brief Fetch the world to body matrix
             *
             * \return The inverse matrix.
             *
             ***********************************************/
            const Math::mat3f &getInverseMatrix() const;

            /********************************************//**
             * \brief Sets the orientation of the overlay
             *
             * \param matrix    The rotation matrix.
             * \return void
             *
             ***********************************************/
            void setOrientation(const Math::mat2f &matrix);

            /********************************************//**
             * \brief Sets the orientation of the overlay
             *
             * \param angle The angle to calculate.
             * \return void
             *
             ***********************************************/
            void setOrientation(const float angle);

            /********************************************//**
             * \brief Returns the orientation of the overlay
             *
             * \return The orientation of the overlay.
             *
             ***********************************************/
            const Math::mat2f &getOrientation() const;

            /********************************************//**
             * \brief Rotates the overlay
             *
             * \param matrix    The matrix to rotate it by.
             * \return void
             *
             ***********************************************/
            void rotate(const Math::mat2f &matrix);

            /********************************************//**
             * \brief Rotates the overlay
             *
             * \param angle The angle to rotate by.
             * \return void
             *
             ***********************************************/
            void rotate(const float angle);

            /********************************************//**
             * \brief Sets the position of the overlay
             *
             * \param vec   The new position as vector.
             * \return void
             *
             ***********************************************/
            void setPosition(const Math::vec2f &vec);

            /********************************************//**
             * \brief Sets the position of the overlay
             *
             * \param x    The x coordinate.
             * \param y    The y coordinate.
             * \return void
             *
             ***********************************************/
            void setPosition(const float x, const float y);

            /********************************************//**
             * \brief Returns the position of the overlay
             *
             * \return The position of the overlay.
             *
             ***********************************************/
            const Math::vec2f &getPosition() const;

            /********************************************//**
             * \brief Moves the overlay
             *
             * \param vec   The vector to displace the overlay with.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void move(const Math::vec2f &vec, const TransformSpace::TransformSpace &space = TransformSpace::PARENT);

            /********************************************//**
             * \brief Moves the overlay
             *
             * \param x     The x displacement.
             * \param y     The y displacement.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void move(const float x, const float y, const TransformSpace::TransformSpace &space = TransformSpace::PARENT);

            /********************************************//**
             * \brief Sets the scale of the overlay
             *
             * \param vec   The new scale as vector.
             * \return void
             *
             ***********************************************/
            void setScale(const Math::vec2f &vec);

            /********************************************//**
             * \brief Sets the scale of the overlay
             *
             * \param x    The x component.
             * \param y    The y component.
             * \return void
             *
             ***********************************************/
            void setScale(const float x, const float y);

            /********************************************//**
             * \brief Sets the scale of the overlay
             *
             * \param sc    The uniform scale (x,y components).
             * \return void
             *
             ***********************************************/
            void setScale(const float sc);

            /********************************************//**
             * \brief Fetch the scale of the overlay
             *
             * \return The scale of the overlay.
             *
             ***********************************************/
            const Math::vec2f &getScale() const;

            /********************************************//**
             * \brief Scales the overlay
             *
             * \param vec   The vector to scale the node with.
             * \return void
             *
             ***********************************************/
            void scale(const Math::vec2f &vec);

            /********************************************//**
             * \brief Scales the overlay
             *
             * \param x The x scale.
             * \param y The y scale.
             * \return void
             *
             ***********************************************/
            void scale(const float x, const float y);

            /********************************************//**
             * \brief Scales the overlay
             *
             * \param sc    The uniform scale (x,y components).
             * \return void
             *
             ***********************************************/
            void scale(const float sc);

            /********************************************//**
             * \brief Adds a child to the overlay
             *
             * \param child    The child to add.
             * \return Whether the child was successfully added or not.
             *
             ***********************************************/
            bool addChild(Overlay *child);

            /********************************************//**
             * \brief Returns whether it has the specified child
             *
             * \param child    The specified child.
             * \return Whether it has the child.
             *
             ***********************************************/
            bool hasChild(const Overlay *child) const;

            /********************************************//**
             * \brief Fetch the amount of children
             *
             * \return The number of children.
             *
             ***********************************************/
            unsigned int getNumChildren() const;

            /********************************************//**
             * \brief Removes a child from the overlay
             *
             * \param child The child to remove.
             * \return Whether the child was successfully removed or not.
             *
             ***********************************************/
            bool removeChild(Overlay *child);

            /********************************************//**
             * \brief Sets the parent (adds as child to the parent)
             *
             * \param parent    The parent overlay.
             * \param return    Whether the parent was changed.
             * \return Whether the parent was successfully set or not.
             *
             ***********************************************/
            bool setParent(Overlay *parent);

            /********************************************//**
             * \brief Returns the parent (NULL if root)
             *
             * \return The parent.
             *
             ***********************************************/
            Overlay *getParent() const;

            /********************************************//**
             * \brief Sets all its own and its children update flags
             *
             * \return void
             *
             ***********************************************/
            void forceUpdate();
    };
}

#endif

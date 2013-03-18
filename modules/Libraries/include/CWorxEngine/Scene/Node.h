/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Node : A 'space' in 3D World Space describing its position,
 orientation and scale which can contain various objects.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __NODE_H__
#define __NODE_H__

#include "CWorxEnginePrerequisites.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! Describes an Euler Space
    class CWE_DLL Node
    {
        //-----------------------------------------------------------------------
        protected:
            // Define a list of nodes
            typedef std::list<Node*> NodeList;

            // Parent/Child
            Node *_parent;
            NodeList _children;

            // Positioning
            Math::fquat _orientation;
            Math::vec3f _position;
            Math::vec3f _scale;

            // Derived
            Math::fquat _orientationDerived;
            Math::vec3f _positionDerived;
            Math::vec3f _scaleDerived;

            // Inheritance
            bool _inheritOrientation;
            bool _inheritPosition;
            bool _inheritScale;

            // Update flag
            bool _update;
            bool _updateMatrices;

            // Actual usage
            Math::mat4f _matrix;
            Math::mat4f _invMatrix;

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param parent    The parent node.
             *
             ***********************************************/
            Node(Node *parent = 0);

            /********************************************//**
             * \brief Constructor
             *
             * \param position      The position of the node in parent space.
             * \param orientation   The orientation of the node.
             * \param scale         The scale of the node.
             * \param parent        The parent node.
             *
             ***********************************************/
            Node(const Math::vec3f &position, const Math::fquat &orientation = Math::fquat(1.0f), const Math::vec3f &scale = Math::vec3f(1.0f), Node *parent = 0);

            /********************************************//**
             * \brief Fetch the body to world matrix
             *
             * \return The matrix.
             *
             ***********************************************/
            const Math::mat4f &getMatrix() const;

            /********************************************//**
             * \brief Fetch the world to body matrix
             *
             * \return The inverse matrix.
             *
             ***********************************************/
            const Math::mat4f &getInverseMatrix() const;

            /********************************************//**
             * \brief Sets whether it should inherit orientation or not
             *
             * \param inherit   Whether it should inherit orientation or not.
             * \return void
             *
             ***********************************************/
            void inheritOrientation(const bool inherit = true);

            /********************************************//**
             * \brief Sets whether it should inherit position or not
             *
             * \param inherit   Whether it should inherit position or not.
             * \return void
             *
             ***********************************************/
            void inheritPosition(const bool inherit = true);

            /********************************************//**
             * \brief Sets whether it should inherit scale or not
             *
             * \param inherit   Whether it should inherit scale or not.
             * \return void
             *
             ***********************************************/
            void inheritScale(const bool inherit = true);

            /********************************************//**
             * \brief Sets the orientation of the node
             *
             * \param quat  The new orientation as quaternion.
             * \param space The transformation space the orientation is in.
             * \return void
             *
             ***********************************************/
            void setOrientation(const Math::fquat &qt);

            /********************************************//**
             * \brief Sets the orientation of the node
             *
             * \param w The w component.
             * \param x    The x component.
             * \param y    The y component.
             * \param z    The z component.
             * \return void
             *
             ***********************************************/
            void setOrientation(float w, float x, float y, float z);

            /********************************************//**
             * \brief Sets the orientation of the node
             *
             * \param angle The angle in radians.
             * \param axis  The axis to rotate around in vector form.
             * \return void
             *
             ***********************************************/
            void setOrientation(const float angle, const Math::vec3f &axis);

            /********************************************//**
             * \brief Fetch the orientation of the node
             *
             * \return The orientation of the node.
             *
             ***********************************************/
            const Math::fquat &getOrientation() const;

            /********************************************//**
             * \brief Fetch the world orientation of the node
             *
             * \return The world orientation of the node.
             *
             ***********************************************/
            const Math::fquat &getDerivedOrientation() const;

            /********************************************//**
             * \brief Rotates the node
             *
             * \param quat  The quaternion to rotate the node with.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void rotate(const Math::fquat &qt, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Rotates the node
             *
             * \param w     The w component.
             * \param x     The x component.
             * \param y     The y component.
             * \param z     The z component.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void rotate(float w, float x, float y, float z, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Rotates the node
             *
             * \param angle The angle in radians.
             * \param axis  The axis to rotate around in vector form.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void rotate(float angle, const Math::vec3f &axis, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Sets the position of the node
             *
             * \param vec   The new position as vector.
             * \return void
             *
             ***********************************************/
            void setPosition(const Math::vec3f &vec);

            /********************************************//**
             * \brief Sets the position of the node
             *
             * \param x    The x coordinate.
             * \param y    The y coordinate.
             * \param z    The z coordinate.
             * \return void
             *
             ***********************************************/
            void setPosition(float x, float y, float z);

            /********************************************//**
             * \brief Returns the position of the node
             *
             * \return The position of the node.
             *
             ***********************************************/
            const Math::vec3f &getPosition() const;

            /********************************************//**
             * \brief Returns the world position of the node
             *
             * \return The world position of the node.
             *
             ***********************************************/
            const Math::vec3f &getDerivedPosition() const;

            /********************************************//**
             * \brief Moves the node
             *
             * \param vec   The vector to displace the node with.
             * \param space The transformation space to transform in.
             * \return voids
             *
             ***********************************************/
            void move(const Math::vec3f &vec, const TransformSpace::TransformSpace &space = TransformSpace::PARENT);

            /********************************************//**
             * \brief Moves the node
             *
             * \param x     The x displacement.
             * \param y     The y displacement.
             * \param z     The z displacement.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void move(float x, float y, float z, const TransformSpace::TransformSpace &space = TransformSpace::PARENT);

            /********************************************//**
             * \brief Sets the scale of the node
             *
             * \param vec   The new scale as vector.
             * \return void
             *
             ***********************************************/
            void setScale(const Math::vec3f &vec);

            /********************************************//**
             * \brief Sets the scale of the node
             *
             * \param x    The x component.
             * \param y    The y component.
             * \param z    The z component.
             * \return void
             *
             ***********************************************/
            void setScale(float x, float y, float z);

            /********************************************//**
             * \brief Sets the scale of the node
             *
             * \param sc    The uniform scale (x,y,z components).
             * \return void
             *
             ***********************************************/
            void setScale(float sc);

            /********************************************//**
             * \brief Fetch the scale of the node
             *
             * \return The scale of the node.
             *
             ***********************************************/
            const Math::vec3f &getScale() const;

            /********************************************//**
             * \brief Fetch the world scale of the node
             *
             * \return The world scale of the node.
             *
             ***********************************************/
            const Math::vec3f &getDerivedScale() const;

            /********************************************//**
             * \brief Scales the node
             *
             * \param vec   The vector to scale the node with.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void scale(const Math::vec3f &vec, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Scales the node
             *
             * \param x The x scale.
             * \param y The y scale.
             * \param z The z scale.
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void scale(float x, float y, float z, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Scales the node
             *
             * \param sc    The uniform scale (x,y,z components).
             * \param space The transformation space to transform in.
             * \return void
             *
             ***********************************************/
            void scale(float sc, const TransformSpace::TransformSpace &space = TransformSpace::LOCAL);

            /********************************************//**
             * \brief Adds a child to the node
             *
             * \param child    The child to add.
             * \return Whether it could add the child or not.
             *
             ***********************************************/
            bool addChild(Node *child);

            /********************************************//**
             * \brief Returns whether it has the specified child
             *
             * \param child The specified child.
             * \return Whether it has the specified child or not.
             *
             ***********************************************/
            bool hasChild(const Node *child) const;

            /********************************************//**
             * \brief Fetch the amount of children
             *
             * \return The amount of children.
             *
             ***********************************************/
            unsigned int getNumChildren() const;

            /********************************************//**
             * \brief Removes a child from the node
             *
             * \param child The child to remove.
             * \return Whether it could remove the child or not.
             *
             ***********************************************/
            bool removeChild(Node *child);

            /********************************************//**
             * \brief Sets the parent (adds as child to the parent)
             *
             * \param parent    The parent node.
             * \param return    Whether the parent was changed.
             * \return Whether it could set the parent or not.
             *
             ***********************************************/
            bool setParent(Node *parent);

            /********************************************//**
             * \brief Fetch the parent (NULL if root)
             *
             * \return The parent node
             *
             ***********************************************/
            Node *getParent() const;

            /********************************************//**
             * \brief Updates the node
             *
             * \return  Whether it actually updated anything.
             *
             * Updates the node, which will automatically update parent nodes, and set the update flag of child nodes.
             *
             ***********************************************/
            virtual bool update();

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

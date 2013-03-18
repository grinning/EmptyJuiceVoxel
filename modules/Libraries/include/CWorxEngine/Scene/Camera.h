/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Camera : A virtual camera in 3D space to similate real
 life camera's and their properties.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Scene/Node.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! A virtual camera in 3D space
    class CWE_DLL Camera : public Node
    {
        //-----------------------------------------------------------------------
        protected:
            // Camera Properties
            float _aspectRatio;
            double _angleOfView;

            // Projection Properties
            float _near;
            float _far;
            bool _updateProjection;

            ProjectionType::ProjectionType _projectionType;
            Math::mat4f _projectionMatrix;
            Math::mat2f _ndcToClipMatrix; // For depth to position factor

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Constructor
             *
             * \param angleOfView   The angle of view (FOV) of the camera in radians.
             * \param parent        The parent node.
             *
             ***********************************************/
            Camera(const double angleOfView, Node *parent = 0);

            /********************************************//**
             * \brief Constructor
             *
             * \param size      Size of the view plane.
             * \param parent    The parent node.
             *
             ***********************************************/
            Camera(const Math::vec2ui &size, Node *parent = 0);

            /********************************************//**
             * \brief Constructor
             *
             * \param angleOfView   The angle of view (FOV) of the camera in radians.
             * \param position      The position of the camera in parent space.
             * \param orientation   The orientation of the camera.
             * \param scale         The scale of the camera.
             * \param parent        The parent node.
             *
             ***********************************************/
            Camera(const double angleOfView, const Math::vec3f &position, const Math::fquat &orientation, const Math::vec3f &scale, Node *parent = 0);

            /********************************************//**
             * \brief Sets the projection type
             *
             * \param type  The projection type.
             * \return void
             *
             ***********************************************/
            void setProjectionType(const ProjectionType::ProjectionType &type);

            /********************************************//**
             * \brief Fetch the projection type
             *
             * \return The projection type.
             *
             ***********************************************/
            const ProjectionType::ProjectionType &getProjectionType() const;

            /********************************************//**
             * \brief Fetch the projection matrix
             *
             * \return The projection matrix.
             *
             ***********************************************/
            const Math::mat4f &getProjectionMatrix() const;

            /********************************************//**
             * \brief Fetch the NDC to Clip matrix
             *
             * \return The NDC to Clip matrix.
             *
             ***********************************************/
            const Math::mat2f &getNDCToClipMatrix() const;

            /********************************************//**
             * \brief Fetch the camera matrix
             *
             * \return The camera matrix.
             *
             ***********************************************/
            const Math::mat4f &getMatrix() const;

            /********************************************//**
             * \brief Fetch the inverse camera matrix
             *
             * \return The inverse camera matrix.
             *
             ***********************************************/
            const Math::mat4f &getInverseMatrix() const;

            /********************************************//**
             * \brief Sets the near clipping distance
             *
             * \param near    The near clipping distance.
             * \return void
             *
             ***********************************************/
            void setNearClip(const float clip);

            /********************************************//**
             * \brief Fetch the near clipping distance
             *
             * \return The near clipping distance.
             *
             ***********************************************/
            float getNearClip() const;

            /********************************************//**
             * \brief Sets the far clipping distance
             *
             * \param far   The far clipping distance.
             * \return void
             *
             ***********************************************/
            void setFarClip(const float clip);

            /********************************************//**
             * \brief Fetch the far clipping distance
             *
             * \return The far clipping distance.
             *
             ***********************************************/
            float getFarClip() const;

            /********************************************//**
             * \brief Sets the aspect ratio
             *
             * \param vec   Ratio in vector form.
             * \return void
             *
             ***********************************************/
            void setAspectRatio(const Math::vec2ui &vec);

            /********************************************//**
             * \brief Sets the aspect ratio
             *
             * \param width     Width of the ratio.
             * \param height    Height of the ratio.
             * \return void
             *
             ***********************************************/
            void setAspectRatio(const unsigned int width, const unsigned int height);

            /********************************************//**
             * \brief Fetch the aspect ratio
             *
             * \return The aspect ratio.
             *
             ***********************************************/
            float getAspectRatio() const;

            /********************************************//**
             * \brief Sets the Y angle of view in radians
             *
             * \param angle The angle in radians.
             * \return void
             *
             ***********************************************/
            void setAngleOfView(const double angle);

            /********************************************//**
             * \brief Returns the angle of view in radians
             *
             * \return The angle of view in radians.
             *
             ***********************************************/
            double getAngleOfView() const;

            /********************************************//**
             * \brief Helper function to set the size of the virtual view plane
             *
             * \param size  Size in vector form.
             * \return void
             *
             ***********************************************/
            void setSize(const Math::vec2f &size);

            /********************************************//**
             * \brief Helper function to set the size of the virtual view plane
             *
             * \param width     Width of the plane.
             * \param height    Height of the plane.
             * \return void
             *
             ***********************************************/
            void setSize(const float width, const float height);

            /********************************************//**
             * \brief Returns the size of the virtual view plane
             *
             * \return The size of the virtual view plane.
             *
             ***********************************************/
            Math::vec2f getSize() const;

            /********************************************//**
             * \brief Updates the camera
             *
             * \return  Whether it actually updated anything.
             *
             * Updates the camera, which will automatically update parent nodes, and set the update flag of child nodes.
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
    };
}

#endif

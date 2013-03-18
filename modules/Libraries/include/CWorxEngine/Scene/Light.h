/*********************************************************
 * CWorx Graphics : Graphics Engine produced by Ckef Worx
 * www            : http://www.ckef-worx.com

 Light : A light in 3D World Space describing its position,
 direction, intensity and other various properties.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Scene/Object.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //! A light in 3D Space
    class CWE_DLL Light : public Object
    {
        //-----------------------------------------------------------------------
        public:
            // Define light types
            enum Type
            {
                TYPE_DIRECTIONAL,
                TYPE_POINT
            };

            // Define the default light direction (0,0,-1)
            static const Math::vec3f DEFAULT_DIRECTION;

        //-----------------------------------------------------------------------
        protected:
            // Properties
            const Type _type;
            Geometry::Material _material;
            bool _castShadow;

            // Material Properties
            Math::mat4f _shadowProj;
            Math::mat4f _shadowMatrix;
            Hardware::Texture *_angleMask;

            /********************************************//**
             * \brief Initializes the material for this light
             *
             * \param intensity Intensity to default to.
             * \return void
             *
             * Initializes the material, should only be used in the constructor.
             *
             ***********************************************/
            void initMaterial(const Math::vec3f &intensity);

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
            // Define a list of meshes
            typedef std::vector<Geometry::Mesh*> MeshList;

            // Light meshes
            static MeshList _meshes;

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Generates the geometry for the lights
             *
             * \param precision Precision to generate a circle with.
             * \return void
             *
             * Generates the geometry for the lights, this can only be called once, and is fixed afterwards.
             *
             ***********************************************/
            static void generateGeometry(unsigned short precision = 2);

            /********************************************//**
             * \brief Fetch the mesh of a certain type
             *
             * \param type  The type of the light to fetch.
             * \return The mesh of the given type.
             *
             ***********************************************/
            static Geometry::Mesh &getMesh(const Type &type);

            /********************************************//**
             * \brief Constructor
             *
             * \param type          The type of the light.
             * \param intensity     Intensity of the light.
             * \param bidirectional Whether it should be bidirectional or not (only affects spot lights).
             * \param direction     Direction of the light (parent space).
             *
             ***********************************************/
            Light(const Type &type, const Math::vec3f &intensity = 1.0f, const Math::vec3f &direction = Math::vec3f(0.0f, 0.0f, -1.0f));

            /********************************************//**
             * \brief Constructor (creates an angle mask)
             *
             * \param data  A pointer to the data to fill the texture with.
             * \param size  Size of the texture in bytes (characters).
             *
             ***********************************************/
            Light(const char *data, unsigned int size);

            /********************************************//**
             * \brief Constructor (creates an angle mask)
             *
             * \param inner         Angle of the inner cone in radians.
             * \param outer         Angle of the outer cone in radians.
             * \param falloff       Falloff exponent.
             * \param bidirectional Whether the spotlight is bidirectional or not.
             * \param resolution    The resolution of the texture to generate.
             *
             ***********************************************/
            Light(float inner, float outer, float falloff, bool bidirectional = false, unsigned int resolution = 128);

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Light();

            /********************************************//**
             * \brief Fetch the type of the light
             *
             * \return The type of the light.
             *
             ***********************************************/
            const Type &getType() const;

            /********************************************//**
             * \brief Sets whether this light casts a shadow or not
             *
             * \param shadow    If true, it will cast a shadow, if false, it will not.
             * \param noBleed   If true, directional shadow maps won't bleed.
             * \return Whether it could successfully adjust its shaders.
             *
             * Sets whether this light casts a shadow or not.
             * A shadow cast state change is very expensive because of GLSL compiling.
             *
             ***********************************************/
            bool castShadow(bool shadow, bool noBleed = false);

            /********************************************//**
             * \brief Fetch whether this light casts a shadow or not
             *
             * \return Whether this light casts a shadow or not.
             *
             ***********************************************/
            bool castShadow() const;

            /********************************************//**
             * \brief Sets the shadow near clip
             *
             * \param clip  New near clip to use.
             * \return void
             *
             * Sets the shadow near clip, ranging from [0,1], 1 being the light's edge.
             *
             ***********************************************/
            void setShadowNear(float near);

            /********************************************//**
             * \brief Fetch the projection matrix for shadow mapping
             *
             * \return The projection matrix for shadow mapping.
             *
             ***********************************************/
            const Math::mat4f &getShadowProjection() const;

            /********************************************//**
             * \brief Sets the direction of the light
             *
             * \param vec   The direction.
             * \return void
             *
             ***********************************************/
            void setDirection(const Math::vec3f &vec);

            /********************************************//**
             * \brief Sets the direction of the light
             *
             * \param x The x component.
             * \param y The y component.
             * \param z The z component.
             * \return void
             *
             ***********************************************/
            void setDirection(float x, float y, float z);

            /********************************************//**
             * \brief Fetch the direction of the light
             *
             * \return The direction of the light.
             *
             ***********************************************/
            Math::vec3f getDirection() const;

            /********************************************//**
             * \brief Fetch the world direction of the light
             *
             * \return The world direction of the light.
             *
             ***********************************************/
            Math::vec3f getDerivedDirection() const;

            /********************************************//**
             * \brief Uses a given angle mask texture
             *
             * \param data  A pointer to the data to fill the texture with.
             * \param size  Size of the texture in bytes (characters).
             * \return Whether it could set the texture and adjust its shaders or not.
             *
             * Uses a given angle mask texture, expensive because of GLSL compiling.
             *
             ***********************************************/
            bool setAngleMask(const char *data, unsigned int size);

            /********************************************//**
             * \brief Generates the angle mask texture
             *
             * \param inner         Angle of the inner cone in radians.
             * \param outer         Angle of the outer cone in radians.
             * \param falloff       Falloff exponent.
             * \param bidirectional Whether the spotlight is bidirectional or not.
             * \param resolution    The resolution of the texture to generate.
             * \return Whether it could set the texture or not.
             *
             * Generates the angle mask texture, expensive because of GLSL compiling.
             *
             ***********************************************/
            bool setAngleMask(float inner, float outer, float falloff, bool bidirectional = false, unsigned int resolution = 128);

            /********************************************//**
             * \brief Removes the angle mask texture
             *
             * \return void
             *
             ***********************************************/
            void removeAngleMask();

            /********************************************//**
             * \brief Fetch the angle mask texture
             *
             * \return The angle mask texture.
             *
             ***********************************************/
            Hardware::Texture *getAngleMask() const;

            /********************************************//**
             * \brief Helper function to set the attenuation according to the physical size of the light.
             *
             * \param size      The radius of the light to simulate.
             * \return The final applied attenuation (constant, linear, quadratic).
             *
             ***********************************************/
            Math::vec3f setSize(float size);

            /********************************************//**
             * \brief Helper function to scale the light.
             *
             * \param float The radius of the light's sphere of influence.
             * \return void
             *
             ***********************************************/
            void setRange(float range);

            /********************************************//**
             * \brief Helper function to calculate the range from known parameters
             *
             * \param size      The size of the light to simulate.
             * \param threshold The intensity at the edge of the range to calculate.
             * \return Whether it could set the strength or not.
             *
             ***********************************************/
            bool setStrength(float size, float threshold = 0.001f);

            /********************************************//**
             * \brief Helper function to calculate the size from known parameters
             *
             * \param range     The range of the light to simulate.
             * \param threshold The intensity at the edge of the known range.
             * \return Whether it could set the influence or not.
             *
             ***********************************************/
            bool setInfluence(float range, float threshold = 0.001f);
    };
}

#endif

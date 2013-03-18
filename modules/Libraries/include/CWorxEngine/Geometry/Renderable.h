/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Renderable : Wraps a mesh and several materials
 independent from each other.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "Geometry/Material.h"
#include "Geometry/Mesh.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Geometry namespace
    namespace Geometry
    {
        //! Wraps a mesh and several materials independent from each other
        class CWE_DLL Renderable
        {
            //-----------------------------------------------------------------------
            public:
                // Define a renderable pointer, so stored pointers will automatically update
                struct Pointer
                {
                    // Properties
                    const Renderable &renderable;
                    const unsigned int geometryID;

                    // Actual pointer
                    const Material::Pointer *matPointer;

                    /********************************************//**
                     * \brief Constructor
                     *
                     * \param rend  The renderable this pointer belongs to.
                     * \param ID    The geometry ID to use this pointer for.
                     * \param pntr  The shader pointer to point to.
                     *
                     ***********************************************/
                    Pointer(const Renderable &rend, unsigned int ID, const Material::Pointer *pntr);

                    /********************************************//**
                     * \brief Sort renderable pointers in a container
                     *
                     * \param r1    First renderable pointer.
                     * \param r2    Second renderable pointer.
                     * \return True if r1 precedes r2.
                     *
                     * Does not take null pointers!
                     *
                     ***********************************************/
                    struct sort { bool operator()(const Pointer *p1, const Pointer *p2) const; };
                };

            //-----------------------------------------------------------------------
            protected:
                // Define a renderable pointer per shader pass
                typedef std::map<const Shader::Pass, Pointer*> PointerMap;

                // Define a material and its pointers per geometry ID
                typedef std::map<const unsigned int, std::pair<Material*, PointerMap> > MaterialMap;

                // Properties
                MaterialMap _materials; // The pointers never change once they exist!
                Mesh *_mesh;
                bool _visible;

                /********************************************//**
                 * \brief Updates the renderable specific material properties
                 *
                 * \return Whether it updated anything or not.
                 *
                 ***********************************************/
                virtual bool updateProperties() = 0;

                /********************************************//**
                 * \brief Calculates properties ready to be bound
                 *
                 * \param cam       Camera matrix to apply.
                 * \param invCam    Inverse camera matrix to apply.
                 * \return void
                 *
                 ***********************************************/
                virtual void processProperties(const Math::mat4f &cam, const Math::mat4f &invCam) = 0;

                /********************************************//**
                 * \brief Binds properties to a given shader
                 *
                 * \param shad  Shader to bind to.
                 * \return void
                 *
                 ***********************************************/
                virtual void bindProperties(const Shader::Shader &shad) const = 0;

            //-----------------------------------------------------------------------
            public:
                // To directly access properties
                friend class RenderQueue;

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param mesh  The mesh to use.
                 *
                 ***********************************************/
                Renderable(Mesh &mesh);

                /********************************************//**
                 * \brief Destructor
                 ***********************************************/
                virtual ~Renderable();

                /********************************************//**
                 * \brief Sets the mesh to use
                 *
                 * \param mesh  The mesh to use.
                 * \return void
                 *
                 ***********************************************/
                void setMesh(Mesh &mesh);

                /********************************************//**
                 * \brief Fetch the mesh
                 *
                 * \return The mesh in use.
                 *
                 ***********************************************/
                Mesh &getMesh() const;

                /********************************************//**
                 * \brief Sets the visibility of this renderable
                 *
                 * \param visible   Whether to be visible or not.
                 * \return void
                 *
                 ***********************************************/
                void visible(bool visible);

                /********************************************//**
                 * \brief Toggles the renderable's visibility
                 *
                 * \return Whether the renderable is now visible or not.
                 *
                 ***********************************************/
                bool toggleVisibile();

                /********************************************//**
                 * \brief Fetch whether this renderable is visible
                 *
                 * \return Whether this renderable is visible or not.
                 *
                 ***********************************************/
                bool isVisible() const;

                /********************************************//**
                 * \brief Sets the material for a given ID
                 *
                 * \param mat   The material to set it to.
                 * \param id    Which id the material belongs to.
                 * \return Whether the geometryID already existed or not.
                 *
                 * Sets the material for a given ID and returns whether the ID already existed or not.
                 * If the ID did not exist yet (return = false), the renderable should be re-added to any renderqueue for it to render with the new material!
                 *
                 ***********************************************/
                bool addMaterial(Material &mat, unsigned int id = 0);

                /********************************************//**
                 * \brief Returns the material attached to a given ID
                 *
                 * \param id    The geometryID to search for.
                 * \return The material attached to the given ID.
                 *
                 ***********************************************/
                Material *getMaterial(unsigned int id = 0) const;

                /********************************************//**
                 * \brief Removes a material from the renderable
                 *
                 * \param id    The geometryID of the material to remove.
                 * \return Whether the material could be removed or not.
                 *
                 ***********************************************/
                bool removeMaterial(unsigned int id);

                /********************************************//**
                 * \brief Returns the number of materials
                 *
                 * \return Number of materials.
                 *
                 * Returns the number of materials, if a material is used for multiple IDs, it will be counted multiple times.
                 *
                 ***********************************************/
                unsigned int getNumMaterials() const;

                /********************************************//**
                 * \brief Adds the renderable to a render queue
                 *
                 * \param queue The RenderQueue to add itself to.
                 * \param pass  The pass to add to the queue.
                 * \return void
                 *
                 ***********************************************/
                void addToRenderQueue(RenderQueue &queue, unsigned int pass);
        };
    }
}

#endif

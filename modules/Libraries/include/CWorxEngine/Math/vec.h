/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 vec : object containing an arbitrary amount of dimensions
 in Space for expressing a direction and magnitude.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __VECT_H__
#define __VECT_H__

#include "CWorxEnginePrerequisites.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //-----------------------------------------------------------------------
    template <typename _type, unsigned short _size>
    class vec
    {
        //-----------------------------------------------------------------------
        protected:
            // Storage
            _type *v;

        //-----------------------------------------------------------------------
        public:
            /** Constructor */
            inline vec()
            {
                // Can't allow 0 length
                assert(_size > 0);

                // Create storage
                v = new _type[_size];
            }

            /** Constructor
             * @x   X component.
             */
            inline vec(const _type x)
            {
                // Can't allow 0 length
                assert(_size > 0);

                // Create storage
                v = new _type[_size];
                if(_size > 0) v[0] = x;
            }

            /** Constructor
             * @x   X component.
             * @y   Y component.
             */
            inline vec(const _type x, const _type y)
            {
                // Can't allow 0 length
                assert(_size > 1);

                // Create storage
                v = new _type[_size];
                if(_size > 0) v[0] = x;
                if(_size > 1) v[1] = y;
            }

            /** Constructor
             * @x   X component.
             * @y   Y component.
             * @z   Z component.
             */
            inline vec(const _type x, const _type y, const _type z)
            {
                // Can't allow 0 length
                assert(_size > 0);

                // Create storage
                v = new _type[_size];
                if(_size > 0) v[0] = x;
                if(_size > 1) v[1] = y;
                if(_size > 2) v[2] = z;
            }

            /** Constructor
             * @x   X component.
             * @y   Y component.
             * @z   Z component.
             * @w   W component.
             */
            inline vec(const _type x, const _type y, const _type z, const _type w)
            {
                // Can't allow 0 length
                assert(_size > 0);

                // Create storage
                v = new _type[_size];
                if(_size > 0) v[0] = x;
                if(_size > 1) v[1] = y;
                if(_size > 2) v[2] = z;
                if(_size > 3) v[3] = w;
            }

            /** Destructor */
            inline virtual ~vec()
            {
                // Destroy storage
                delete[] v;
            }

            /** Fetches the value at a given index */
            inline _type &operator[](const unsigned short index)
            {
                // Out of range
                assert(index < _size);
                return v[index];
            }
    };
}

#endif

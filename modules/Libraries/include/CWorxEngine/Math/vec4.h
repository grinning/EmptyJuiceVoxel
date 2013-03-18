/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 vec4 : 4D Vector.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __VEC4_H__
#define __VEC4_H__

#include <cmath>
#include <iostream>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! 4D Vector
        template <typename _type>
        class vec4
        {
            //-----------------------------------------------------------------------
            public:
                // PUBLIC
                _type x;
                _type y;
                _type z;
                _type w;

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline vec4() :
                    x(0), y(0), z(0), w(1)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param fx    The x coordinate of the vector.
                 * \param fy    The y coordinate of the vector.
                 * \param fz    The z coordinate of the vector.
                 * \param fw    The w coordinate of the vector.
                 *
                 ***********************************************/
                inline vec4(const _type fx, const _type fy, const _type fz, const _type fw) :
                    x(fx), y(fy), z(fz), w(fw)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The x, y, z AND w coordinate of the vector.
                 *
                 ***********************************************/
                inline vec4(const _type scalar) :
                    x(scalar), y(scalar), z(scalar), w(scalar)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param vec        The vec3 to take as x, y and z parameters.
                 * \param scalar    The w component.
                 *
                 ***********************************************/
                inline vec4(const vec3<_type> &vec, const _type fw = 1) :
                    x(vec.x), y(vec.y), z(vec.z), w(fw)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar  The x component.
                 * \param vec     The vec3 to take as y, z and w parameters.
                 *
                 ***********************************************/
                inline vec4(const _type fx, const vec3<_type> &vec) :
                    x(fx), y(vec.x), z(vec.y), w(vec.z)
                {
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline vec4(vec4<_t> &vec)
                {
                    *this = vec;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline vec4 &operator=(const vec4<_t> &vec)
                {
                    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
                    return *this;
                }

                /********************************************//**
                 * \brief Assign to scalar
                 *
                 * \param scalar    The scalar to set the vector to.
                 * \return Itself.
                 *
                 ***********************************************/
                inline vec4 &operator=(const _type scalar)
                {
                    x = scalar; y = scalar; z = scalar; w = scalar;
                    return *this;
                }

                /********************************************//**
                 * \brief Assign to vector3
                 *
                 * \param vec   The vec3 to take as x, y and z parameters.
                 * \return Itself.
                 *
                 ***********************************************/
                inline vec4 &operator=(const vec3<_type> &vec)
                {
                    x = vec.x; y = vec.y; z = vec.z; w = 1;
                    return *this;
                }

                /********************************************//**
                 * \brief Computes the lowest value of the vector
                 *
                 * \return The 'minimum' vector.
                 *
                 ***********************************************/
                inline _type min() const
                {
                    return std::min(std::min(std::min(x, y), z), w);
                }

                /********************************************//**
                 * \brief Computes the highest value of the vector
                 *
                 * \return The 'maximum' vector.
                 *
                 ***********************************************/
                inline _type max() const
                {
                    return std::max(std::max(std::max(x, y), z), w);
                }

                /********************************************//**
                 * \brief Computes a vector with all positive values
                 *
                 * \return The absolute vector.
                 *
                 ***********************************************/
                inline vec4 abs() const
                {
                    return vec4(abs(x), abs(y), abs(z), abs(w));
                }

                /********************************************//**
                 * \brief Normalizes the vector
                 *
                 * \return The normalized vector.
                 *
                 ***********************************************/
                inline vec4 normalize() const
                {
                    double mag = magnitude();
                    return !mag ? *this : *this / mag;
                }

                /********************************************//**
                 * \brief Returns the magnitude of the vector
                 *
                 * \return The magnitude of the vector.
                 *
                 ***********************************************/
                inline double magnitude() const
                {
                    return sqrt(x * x + y * y + z * z + w * w);
                }

                /********************************************//**
                 * \brief Fetch the magnitude of the vector squared
                 *
                 * \return Squared magnitude of the vector.
                 *
                 ***********************************************/
                inline _type magnitudeSquared() const
                {
                    return x * x + y * y + z * z + w * w;
                }

                /********************************************//**
                 * \brief Calculates the dot product of this with another vector
                 *
                 * \param vec   The second input vector.
                 * \return The dot product.
                 *
                 ***********************************************/
                inline _type dot(const vec4 &vec) const
                {
                    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
                }

                //-----------------------------------------------------------------------
                /** Basic Vector arithmetics
                 * Incrementing
                 * Decrementing
                 * Comparison
                 * Negation
                 * Scaling
                 * Adding
                 * Subtracting
                 * Multiplying
                 * Dividing
                 */

                // Self modifying
                template <typename _t> inline vec4 &operator+=(const _t scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
                template <typename _t> inline vec4 &operator-=(const _t scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
                template <typename _t> inline vec4 &operator*=(const _t scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
                template <typename _t> inline vec4 &operator/=(const _t scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }
                template <typename _t> inline vec4 &operator+=(const vec4<_t> &vec) { x += vec.x; y += vec.y; z += vec.z; w += vec.w; return *this; }
                template <typename _t> inline vec4 &operator-=(const vec4<_t> &vec) { x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w; return *this; }
                template <typename _t> inline vec4 &operator*=(const vec4<_t> &vec) { x *= vec.x; y *= vec.y; z *= vec.z; w *= vec.w; return *this; }
                template <typename _t> inline vec4 &operator/=(const vec4<_t> &vec) { x /= vec.x; y /= vec.y; z /= vec.z; w /= vec.w; return *this; }

                inline vec4 &operator++() { ++x; ++y; ++z; ++w; return *this; } // Prefix Increment
                inline vec4 &operator--() { --x; --y; --z; --w; return *this; } // Prefix Decrement
                inline vec4 operator++(int) { vec4 copy(*this); ++(*this); return copy; } // Postfix Increment
                inline vec4 operator--(int) { vec4 copy(*this); --(*this); return copy; } // Postfix Decrement

                // Non-Self modifying
                template <typename _t> inline bool operator==(const vec4<_t> &vec) const { return x == vec.x && y == vec.y && z == vec.z && w == vec.w; }
                template <typename _t> inline bool operator!=(const vec4<_t> &vec) const { return !(*this == vec); }
                inline vec4 operator+() const { return *this; }
                inline vec4 operator-() const { return vec4(-x, -y, -z, -w); }

                friend inline vec4 operator*(const _type scalar, const vec4 &vec) { return vec4(scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * vec.w); }
                friend inline vec4 operator/(const _type scalar, const vec4 &vec) { return vec4(scalar / vec.x, scalar / vec.y, scalar / vec.z, scalar / vec.w); }

                template <typename _t> inline vec4 operator+(const _t scalar) const { return vec4(x + scalar, y + scalar, z + scalar, w + scalar); }
                template <typename _t> inline vec4 operator-(const _t scalar) const { return vec4(x - scalar, y - scalar, z - scalar, w - scalar); }
                template <typename _t> inline vec4 operator*(const _t scalar) const { return vec4(x * scalar, y * scalar, z * scalar, w * scalar); }
                template <typename _t> inline vec4 operator/(const _t scalar) const { return vec4(x / scalar, y / scalar, z / scalar, w / scalar); }
                template <typename _t> inline vec4 operator+(const vec4<_t> &vec) const { return vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w); }
                template <typename _t> inline vec4 operator-(const vec4<_t> &vec) const { return vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w); }
                template <typename _t> inline vec4 operator*(const vec4<_t> &vec) const { return vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w); }
                template <typename _t> inline vec4 operator/(const vec4<_t> &vec) const { return vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w); }

                // Stream Output
                inline friend std::ostream &operator<<(std::ostream &out, const vec4 &vec)
                    { out << vec.x << " " << vec.y << " " << vec.z << " " << vec.w; return out; }

                // Stream Input
                inline friend std::istream &operator>>(std::istream &in, vec4 &vec)
                    { in >> vec.x >> vec.y >> vec.z >> vec.w; return in; }
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 vec3 : 3D Vector.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>
#include <iostream>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! 3D Vector
        template <typename _type>
        class vec3
        {
            //-----------------------------------------------------------------------
            public:
                // PUBLIC
                _type x;
                _type y;
                _type z;

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline vec3() :
                    x(0), y(0), z(0)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param fx    The x coordinate of the vector.
                 * \param fy    The y coordinate of the vector.
                 * \param fz    The z coordinate of the vector.
                 *
                 ***********************************************/
                inline vec3(const _type fx, const _type fy, const _type fz) :
                    x(fx), y(fy), z(fz)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The x, y AND z coordinate of the vector.
                 *
                 ***********************************************/
                inline vec3(const _type scalar) :
                    x(scalar), y(scalar), z(scalar)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param vec        The vec2 to take as x and y parameters.
                 * \param scalar    The w component.
                 *
                 ***********************************************/
                inline vec3(const vec2<_type> &vec, const _type fz = 0) :
                    x(vec.x), y(vec.y), z(fz)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar  The x component.
                 * \param vec     The vec2 to take as y and z parameters.
                 *
                 ***********************************************/
                inline vec3(const _type fx, const vec2<_type> &vec) :
                    x(fx), y(vec.x), z(vec.y)
                {
                }

                /********************************************//**
                 * \brief Copies from a 4D vector
                 ***********************************************/
                inline vec3(const vec4<_type> &vec)
                {
                    *this = vec;
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline vec3(const vec3<_t> &vec)
                {
                    *this = vec;
                }

                /********************************************//**
                 * \brief Assigns a 4D vector
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                inline vec3 &operator=(const vec4<_type> &vec)
                {
                    x = vec.x; y = vec.y; z = vec.z;
                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline vec3 &operator=(const vec3<_t> &vec)
                {
                    x = vec.x; y = vec.y; z = vec.z;
                    return *this;
                }

                /********************************************//**
                 * \brief Assign to scalar
                 *
                 * \param scalar    The scalar to set the vector to.
                 *
                 ***********************************************/
                inline vec3 &operator=(const _type scalar)
                {
                    x = scalar; y = scalar; z = scalar;
                    return *this;
                }

                /********************************************//**
                 * \brief Assign to vector2
                 *
                 * \param vec   The vec2 to take as x and y parameters.
                 *
                 ***********************************************/
                inline vec3 &operator=(const vec2<_type> &vec)
                {
                    x = vec.x; y = vec.y; z = 0;
                    return *this;
                }

                /********************************************//**
                 * \brief Returns true if the magnitude is 0.0
                 *
                 * \return True if the magnitude is 0.0.
                 *
                 ***********************************************/
                inline bool isZero() const
                {
                    return !x && !y && !z;
                }

                /********************************************//**
                 * \brief Compute the lowest value of the vector
                 *
                 * \return The 'minimum' vector.
                 *
                 ***********************************************/
                inline _type min() const
                {
                    return std::min(std::min(x, y), z);
                }

                /********************************************//**
                 * \brief Compute the highest value of the vector
                 *
                 * \return The 'maximum' vector
                 *
                 ***********************************************/
                inline _type max() const
                {
                    return std::max(std::max(x, y), z);
                }

                /********************************************//**
                 * \brief Computes a vector with all positive values
                 *
                 * \return The absolute vector.
                 *
                 ***********************************************/
                inline vec3 abs() const
                {
                    return vec3(abs(x), abs(y), abs(z));
                }

                /********************************************//**
                 * \brief Normalizes the vector
                 *
                 * \return The normalized vector.
                 *
                 ***********************************************/
                inline vec3 normalize() const
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
                    return sqrt(x * x + y * y + z * z);
                }

                /********************************************//**
                 * \brief Fetch the magnitude of the vector squared
                 *
                 * \return Squared magnitude of the vector.
                 *
                 ***********************************************/
                inline _type magnitudeSquared() const
                {
                    return x * x + y * y + z * z;
                }

                /********************************************//**
                 * \brief Calculates the dot product of this with another vector
                 *
                 * \param vec   The second input vector.
                 * \return The dot product.
                 *
                 ***********************************************/
                inline _type dot(const vec3 &vec) const
                {
                    return x * vec.x + y * vec.y + z * vec.z;
                }

                /********************************************//**
                 * \brief Calculates the cross product of this with another vector
                 *
                 * \param vec   The second input vector.
                 * \return The cross product.
                 *
                 ***********************************************/
                inline vec3 cross(const vec3 &vec) const
                {
                    return vec3(
                        y * vec.z - z * vec.y,
                        z * vec.x - x * vec.z,
                        x * vec.y - y * vec.x
                    );
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
                template <typename _t> inline vec3 &operator+=(const _t scalar) { x += scalar; y += scalar; z += scalar; return *this; }
                template <typename _t> inline vec3 &operator-=(const _t scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
                template <typename _t> inline vec3 &operator*=(const _t scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
                template <typename _t> inline vec3 &operator/=(const _t scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }
                template <typename _t> inline vec3 &operator+=(const vec3<_t> &vec) { x += vec.x; y += vec.y; z += vec.z; return *this; }
                template <typename _t> inline vec3 &operator-=(const vec3<_t> &vec) { x -= vec.x; y -= vec.y; z -= vec.z; return *this; }
                template <typename _t> inline vec3 &operator*=(const vec3<_t> &vec) { x *= vec.x; y *= vec.y; z *= vec.z; return *this; }
                template <typename _t> inline vec3 &operator/=(const vec3<_t> &vec) { x /= vec.x; y /= vec.y; z /= vec.z; return *this; }

                inline vec3 &operator++() { ++x; ++y; ++z; return *this; } // Prefix Increment
                inline vec3 &operator--() { --x; --y; --z; return *this; } // Prefix Decrement
                inline vec3 operator++(int) { vec3 copy(*this); ++(*this); return copy; } // Postfix Increment
                inline vec3 operator--(int) { vec3 copy(*this); --(*this); return copy; } // Postfix Decrement

                // Non-Self modifying
                template <typename _t> inline bool operator==(const vec3<_t> &vec) const { return x == vec.x && y == vec.y && z == vec.z; }
                template <typename _t> inline bool operator!=(const vec3<_t> &vec) const { return !(*this == vec); }
                inline vec3 operator+() const { return *this; }
                inline vec3 operator-() const { return vec3(-x, -y, -z); }

                friend inline vec3 operator*(const _type scalar, const vec3 &vec) { return vec3(scalar * vec.x, scalar * vec.y, scalar * vec.z); }
                friend inline vec3 operator/(const _type scalar, const vec3 &vec) { return vec3(scalar / vec.x, scalar / vec.y, scalar / vec.z); }

                template <typename _t> inline vec3 operator+(const _t scalar) const { return vec3(x + scalar, y + scalar, z + scalar); }
                template <typename _t> inline vec3 operator-(const _t scalar) const { return vec3(x - scalar, y - scalar, z - scalar); }
                template <typename _t> inline vec3 operator*(const _t scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
                template <typename _t> inline vec3 operator/(const _t scalar) const { return vec3(x / scalar, y / scalar, z / scalar); }
                template <typename _t> inline vec3 operator+(const vec3<_t> &vec) const { return vec3(x + vec.x, y + vec.y, z + vec.z); }
                template <typename _t> inline vec3 operator-(const vec3<_t> &vec) const { return vec3(x - vec.x, y - vec.y, z - vec.z); }
                template <typename _t> inline vec3 operator*(const vec3<_t> &vec) const { return vec3(x * vec.x, y * vec.y, z * vec.z); }
                template <typename _t> inline vec3 operator/(const vec3<_t> &vec) const { return vec3(x / vec.x, y / vec.y, z / vec.z); }

                // Stream Output
                inline friend std::ostream &operator<<(std::ostream &out, const vec3 &vec)
                    { out << vec.x << " " << vec.y << " " << vec.z; return out; }

                // Stream Input
                inline friend std::istream &operator>>(std::istream &in, vec3 &vec)
                    { in >> vec.x >> vec.y >> vec.z; return in; }
        };
    }
}

#endif

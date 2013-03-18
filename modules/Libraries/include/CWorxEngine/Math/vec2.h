/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 vec2 : 2D Vector.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>
#include <iostream>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! 2D Vector
        template <typename _type>
        class vec2
        {
            //-----------------------------------------------------------------------
            public:
                // PUBLIC
                _type x;
                _type y;

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline vec2() :
                    x(0), y(0)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param fx    The x coordinate of the vector.
                 * \param fy    The y coordinate of the vector.
                 *
                 ***********************************************/
                inline vec2(const _type fx, const _type fy) :
                    x(fx), y(fy)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The x AND y coordinate of the vector.
                 *
                 ***********************************************/
                inline vec2(const _type scalar) :
                    x(scalar), y(scalar)
                {
                }

                /********************************************//**
                 * \brief Copies from a 3D vector
                 ***********************************************/
                inline vec2(const vec3<_type> &vec)
                {
                    *this = vec;
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline vec2(const vec2<_t> &vec)
                {
                    *this = vec;
                }

                /********************************************//**
                 * \brief Assigns a 3D vector
                 ***********************************************/
                inline vec2 &operator=(const vec3<_type> &vec)
                {
                    x = vec.x; y = vec.y;
                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 ***********************************************/
                template <typename _t>
                inline vec2 &operator=(const vec2<_t> &vec)
                {
                    x = vec.x; y = vec.y;
                    return *this;
                }

                /********************************************//**
                 * \brief Assign to scalar
                 *
                 * \param scalar    The scalar to set the vector to.
                 * \return Itself.
                 *
                 ***********************************************/
                inline vec2 &operator=(const _type scalar)
                {
                    x = scalar; y = scalar;
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
                    return !x && !y;
                }

                /********************************************//**
                 * \brief Computes the loewst value of the vector
                 *
                 * \return The 'minimum' vector.
                 *
                 ***********************************************/
                inline _type min() const
                {
                    return std::min(x, y);
                }

                /********************************************//**
                 * \brief Computes the highest value of the vector
                 *
                 * \return The 'maximum' vector.
                 *
                 ***********************************************/
                inline _type max() const
                {
                    return std::max(x, y);
                }

                /********************************************//**
                 * \brief Compute a vector with all positive values
                 *
                 * \return The absolute vector.
                 *
                 ***********************************************/
                inline vec2 abs() const
                {
                    return vec2(abs(x), abs(y));
                }

                /********************************************//**
                 * \brief Normalizes the vector
                 *
                 * \return The normalized vector.
                 *
                 ***********************************************/
                inline vec2 normalize() const
                {
                    double mag = magnitude();
                    return !mag ? *this : *this / mag;
                }

                /********************************************//**
                 * \brief Fetch the magnitude of the vector
                 *
                 * \return Magnitude of the vector.
                 *
                 ***********************************************/
                inline double magnitude() const
                {
                    return sqrt(x * x + y * y);
                }

                /********************************************//**
                 * \brief Fetch the magnitude of the vector squared
                 *
                 * \return Squared magnitude of the vector.
                 *
                 ***********************************************/
                inline _type magnitudeSquared() const
                {
                    return x * x + y * y;
                }

                /********************************************//**
                 * \brief Calculates the dot product of this with another vector
                 *
                 * \param vec   The second input vector.
                 * \return The dot product.
                 *
                 ***********************************************/
                inline _type dot(const vec2 &vec) const
                {
                    return x * vec.x + y * vec.y;
                }

                /********************************************//**
                 * \brief Calculates the cross product
                 *
                 * \return The cross product.
                 *
                 ***********************************************/
                inline vec2 cross() const
                {
                    return vec2(y, -x);
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
                template <typename _t> inline vec2 &operator+=(const _t scalar) { x += scalar; y += scalar; return *this; }
                template <typename _t> inline vec2 &operator-=(const _t scalar) { x -= scalar; y -= scalar; return *this; }
                template <typename _t> inline vec2 &operator*=(const _t scalar) { x *= scalar; y *= scalar; return *this; }
                template <typename _t> inline vec2 &operator/=(const _t scalar) { x /= scalar; y /= scalar; return *this; }
                template <typename _t> inline vec2 &operator+=(const vec2<_t> &vec) { x += vec.x; y += vec.y; return *this; }
                template <typename _t> inline vec2 &operator-=(const vec2<_t> &vec) { x -= vec.x; y -= vec.y; return *this; }
                template <typename _t> inline vec2 &operator*=(const vec2<_t> &vec) { x *= vec.x; y *= vec.y; return *this; }
                template <typename _t> inline vec2 &operator/=(const vec2<_t> &vec) { x /= vec.x; y /= vec.y; return *this; }

                inline vec2 &operator++() { ++x; ++y; return *this; } // Prefix Increment
                inline vec2 &operator--() { --x; --y; return *this; } // Prefix Decrement
                inline vec2 operator++(int) { vec2 copy(*this); ++(*this); return copy; } // Postfix Increment
                inline vec2 operator--(int) { vec2 copy(*this); --(*this); return copy; } // Postfix Decrement

                // Non-Self modifying
                template <typename _t> inline bool operator==(const vec2<_t> &vec) const { return x == vec.x && y == vec.y; }
                template <typename _t> inline bool operator!=(const vec2<_t> &vec) const { return !(*this == vec); }
                inline vec2 operator+() const { return *this; }
                inline vec2 operator-() const { return vec2(-x, -y); }

                friend inline vec2 operator*(const _type scalar, const vec2 &vec) { return vec2(scalar * vec.x, scalar * vec.y); }
                friend inline vec2 operator/(const _type scalar, const vec2 &vec) { return vec2(scalar / vec.x, scalar / vec.y); }

                template <typename _t> inline vec2 operator+(const _t scalar) const { return vec2(x + scalar, y + scalar); }
                template <typename _t> inline vec2 operator-(const _t scalar) const { return vec2(x - scalar, y - scalar); }
                template <typename _t> inline vec2 operator*(const _t scalar) const { return vec2(x * scalar, y * scalar); }
                template <typename _t> inline vec2 operator/(const _t scalar) const { return vec2(x / scalar, y / scalar); }
                template <typename _t> inline vec2 operator+(const vec2<_t> &vec) const { return vec2(x + vec.x, y + vec.y); }
                template <typename _t> inline vec2 operator-(const vec2<_t> &vec) const { return vec2(x - vec.x, y - vec.y); }
                template <typename _t> inline vec2 operator*(const vec2<_t> &vec) const { return vec2(x * vec.x, y * vec.y); }
                template <typename _t> inline vec2 operator/(const vec2<_t> &vec) const { return vec2(x / vec.x, y / vec.y); }

                // Stream Output
                inline friend std::ostream &operator<<(std::ostream &out, const vec2 &vec)
                    { out << vec.x << " " << vec.y; return out; }

                // Stream Input
                inline friend std::istream &operator>>(std::istream &in, vec2 &vec)
                    { in >> vec.x >> vec.y; return in; }
        };
    }
}

#endif

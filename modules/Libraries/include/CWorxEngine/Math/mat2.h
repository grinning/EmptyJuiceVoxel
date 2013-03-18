/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 mat2 : A 2x2 Matrix.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MAT2_H__
#define __MAT2_H__

#include <cassert>
#include <cmath>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! \cond

        template <typename _type> class mat3;
        template <typename _type> class vec2;

        //! \endcond

        //! 2x2 Matrix
        template <typename _type>
        class mat2
        {
            //-----------------------------------------------------------------------
            protected:
                // Array, row-major
                _type m[4];

            //-----------------------------------------------------------------------
            public:
                // For taking parts
                template <typename _t> friend class mat3;

                /********************************************//**
                 * \brief Constructor, NOTE: does not initialize
                 ***********************************************/
                inline mat2() {}

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline mat2(const _type m00, const _type m01,
                            const _type m02, const _type m03)
                {
                    m[0] = m00; m[1] = m01;
                    m[2] = m02; m[3] = m03;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param x The x (right) vector.
                 * \param y The y (up) vector.
                 *
                 ***********************************************/
                inline mat2(const vec2<_type> &x, const vec2<_type> &y)
                {
                    vec2<_type> xAxis = x.normalize();
                    vec2<_type> yAxis = y.normalize();

                    m[0] = xAxis.x; m[1] = yAxis.x;
                    m[2] = xAxis.y; m[3] = yAxis.y;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The diagnal scalar.
                 *
                 ***********************************************/
                inline mat2(const _type scalar)
                {
                    m[0] = scalar; m[1] = 0;
                    m[2] = 0,      m[3] = scalar;
                }

                /********************************************//**
                 * \brief Copy Constructor from 3x3 matrix
                 ***********************************************/
                inline mat2(const mat3<_type> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline mat2(const mat2<_t> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Assignment Copy from 3x3 matrix
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                inline mat2 &operator=(const mat3<_type> &mat)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1];
                    m[2] = mat.m[3]; m[3] = mat.m[4];

                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline mat2 &operator=(const mat2<_t> &mat)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1];
                    m[2] = mat.m[2]; m[3] = mat.m[3];

                    return *this;
                }

                /********************************************//**
                 * \brief Fetches the value at a given index
                 *
                 * \param index The index of the parameter.
                 * \return The asked parameter.
                 *
                 ***********************************************/
                inline _type &operator[](unsigned short index)
                {
                    assert(index <= 3);

                    return m[index];
                }

                inline const _type &operator[](unsigned short index) const
                {
                    assert(index <= 3);

                    return *(m + index);
                }

                /********************************************//**
                 * \brief Fetches the value at a given coordinate
                 *
                 * \param row       The row of the parameter.
                 * \param collumn   The collumn of the parameter.
                 * \return The asked parameter.
                 *
                 ***********************************************/
                inline _type &operator()(unsigned short row, unsigned short collumn)
                {
                    assert(row <= 1 && collumn <= 1);

                    return m[2 * row + collumn];
                }

                inline const _type &operator()(unsigned short row, unsigned short collumn) const
                {
                    assert(row <= 1 && collumn <= 1);

                    return *(m + 2 * row + collumn);
                }

                /********************************************//**
                 * \brief Returns the transposed matrix
                 *
                 * \return The transpose.
                 *
                 ***********************************************/
                inline mat2 transpose() const
                {
                    return mat2(
                        m[0], m[2],
                        m[1], m[3] );
                }

                /********************************************//**
                 * \brief Inverses the matrix
                 *
                 * \param tolerance of a non existing matrix.
                 * \return Whether an inverse exists.
                 *
                 ***********************************************/
                inline bool invert(const double tolerance = 0.000006)
                {
                    // If determinant equals 0, there is no inverse
                    _type det = m[0] * m[3] - m[1] * m[2];
                    if(std::abs(det) <= tolerance) return false;

                    *this = (1 / det) * mat2(m[3], -m[1], -m[2], m[0]);

                    return true;
                }

                /********************************************//**
                 * \brief Computes the determinant of the matrix
                 *
                 * \return The determinant.
                 *
                 ***********************************************/
                inline _type determinant()
                {
                    return m[0] * m[3] - m[1] * m[2];
                }

                //-----------------------------------------------------------------------
                /** Basic Matrix arithmetics
                 * Comparison
                 * Negation
                 * Adding
                 * Subtracting
                 * Multiplying
                 */

                // Self modifying
                template <typename _t> inline mat2 &operator+=(const mat2<_t> &mat) { *this = *this + mat; return *this; }
                template <typename _t> inline mat2 &operator-=(const mat2<_t> &mat) { *this = *this - mat; return *this; }
                template <typename _t> inline mat2 &operator*=(const mat2<_t> &mat) { *this = *this * mat; return *this; }

                // Non-Self modifying
                template <typename _t> inline bool operator!=(const mat2<_t> &mat) const { return !(*this == mat); }
                inline mat2 operator+() const { return *this; }
                inline mat2 operator-() const { return mat2(-m[0], -m[1], -m[2], -m[3]); }

                inline friend mat2 operator*(const mat2 &mat, const _type scalar) { return scalar * mat; }
                inline friend mat2 operator*(const _type scalar, const mat2 &mat)
                {
                    return mat2(
                        scalar * mat.m[0], scalar * mat.m[1],
                        scalar * mat.m[2], scalar * mat.m[3]);
                }

                template <typename _t>
                inline bool operator==(const mat2<_t> &mat) const
                {
                    return (m[0] == mat.m[0] && m[1] == mat.m[1] &&
                            m[2] == mat.m[2] &&    m[3] == mat.m[3]);
                }

                template <typename _t>
                inline mat2 operator+(const mat2<_t> &mat) const
                {
                    return mat2(
                        m[0] + mat.m[0], m[1] + mat.m[1],
                        m[2] + mat.m[2], m[3] + mat.m[3]);
                }

                template <typename _t>
                inline mat2 operator-(const mat2<_t> &mat) const
                {
                    return mat2(
                        m[0] - mat.m[0], m[1] - mat.m[1],
                        m[2] - mat.m[2], m[3] - mat.m[3]);
                }

                template <typename _t>
                inline mat2 operator*(const mat2<_t> &mat) const
                {
                    return mat2(
                        m[0] * mat.m[0] + m[1] * mat.m[2],
                        m[0] * mat.m[1] + m[1] * mat.m[3],

                        m[2] * mat.m[0] + m[3] * mat.m[2],
                        m[2] * mat.m[1] + m[3] * mat.m[3]);
                }

                // Multiply vec2 by mat2
                template <typename _t>
                inline vec2<_t> operator*(const vec2<_t> &vec) const
                {
                    return vec2<_t>(
                        m[0] * vec.x + m[1] * vec.y,
                        m[2] * vec.x + m[3] * vec.y);
                }
        };
    }
}

#endif

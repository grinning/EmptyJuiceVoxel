/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 mat3 : A 3x3 Matrix.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MAT3_H__
#define __MAT3_H__

#include <cassert>
#include <cmath>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! \cond

        template <typename _type> class mat4;
        template <typename _type> class quat;
        template <typename _type> class vec3;

        //! \endcond

        //! 3x3 Matrix
        template <typename _type>
        class mat3
        {
            //-----------------------------------------------------------------------
            protected:
                // Array, row-major
                _type m[9];

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Computes the matrix according to a position, orientation and scale
                 *
                 * \param position        The position of the item.
                 * \param orientation     The orientation of the item.
                 * \param scale           The scale of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat3<_t> createMatrix(const vec2<_t> &position, const mat2<_t> &orientation, const vec2<_t> &scale = vec2<_t>(1.0f))
                {
                    // Stuff 3x3 matrix
                    mat3<_t> matrix = orientation;

                    // Scale/Translate
                    matrix[0] *= scale.x; matrix[1] *= scale.y; matrix[2] = position.x;
                    matrix[3] *= scale.x; matrix[4] *= scale.y; matrix[5] = position.y;

                    return matrix;
                }

                /********************************************//**
                 * \brief Computes the inverse matrix according to a position, orientation and scale
                 *
                 * \param position        The position of the item.
                 * \param orientation     The orientation of the item.
                 * \param scale           The scale of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat3<_t> createMatrixInverse(const vec2<_t> &position, const mat2<_t> &orientation, const vec2<_t> &scale = vec2<_t>(1.0f))
                {
                    // Create inverse orientation
                    mat2<_t> rotMatrix = orientation;
                    rotMatrix.invert();

                    // Inverse Scale
                    vec2<_t> invScale = 1.0f / scale;

                    // Apply Scale
                    rotMatrix[0] *= invScale.x; rotMatrix[1] *= invScale.x;
                    rotMatrix[2] *= invScale.y; rotMatrix[3] *= invScale.y;

                    // Rotate inverse position and add it
                    return mat3<_t>(rotMatrix, rotMatrix * -position);
                }

                /********************************************//**
                 * \brief Computes the matrix according to a orientation and scale
                 *
                 * \param orientation   The orientation of the item.
                 * \param scale         The scale of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat3<_t> createMatrix(quat<_t> &orientation, vec3<_t> &scale)
                {
                    // quaternion -> matrix
                    mat3<_t> matrix;
                    orientation.toMatrix(matrix);

                    // Apply Scale
                    matrix[0] *= scale.x; matrix[1] *= scale.y; matrix[2] *= scale.z;
                    matrix[3] *= scale.x; matrix[4] *= scale.y; matrix[5] *= scale.z;
                    matrix[6] *= scale.x; matrix[7] *= scale.y; matrix[8] *= scale.z;

                    return matrix;
                }

                /********************************************//**
                 * \brief Computes the inverse matrix according to a orientation and scale
                 *
                 * \param orientation   The orientation of the item.
                 * \param scale         The scale of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat3<_t> createMatrixInverse(quat<_t> &orientation, vec3<_t> &scale)
                {
                    // quaternion -> inverse -> matrix
                    mat3<_t> matrix;
                    orientation.inverse().toMatrix(matrix);

                    // Inverse Scale
                    vec3<_t> invScale = 1.0f / scale;

                    // Apply Scale
                    matrix[0] *= invScale.x; matrix[1] *= invScale.x; matrix[2] *= invScale.x;
                    matrix[3] *= invScale.y; matrix[4] *= invScale.y; matrix[5] *= invScale.y;
                    matrix[6] *= invScale.z; matrix[7] *= invScale.z; matrix[8] *= invScale.z;

                    return matrix;
                }

                // For taking parts
                template <typename _t> friend class mat3;
                template <typename _t> friend class mat4;

                /********************************************//**
                 * \brief Constructor, NOTE: does not initialize
                 ***********************************************/
                inline mat3() {}

                /********************************************//**
                 * \brief Constructor
                 ************************************************/
                inline mat3(const _type m00, const _type m01, const _type m02,
                            const _type m10, const _type m11, const _type m12,
                            const _type m20, const _type m21, const _type m22)
                {
                    m[0] = m00; m[1] = m01; m[2] = m02;
                    m[3] = m10; m[4] = m11; m[5] = m12;
                    m[6] = m20; m[7] = m21; m[8] = m22;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param x The x (right) vector.
                 * \param y The y (up) vector.
                 * \param z The z (front) vector.
                 *
                 ***********************************************/
                inline mat3(const vec3<_type> &x, const vec3<_type> &y, const vec3<_type> &z)
                {
                    vec3<_type> xAxis = x.normalize();
                    vec3<_type> yAxis = y.normalize();
                    vec3<_type> zAxis = z.normalize();

                    m[0] = xAxis.x; m[1] = yAxis.x; m[2] = zAxis.x;
                    m[3] = xAxis.y; m[4] = yAxis.y; m[5] = zAxis.y;
                    m[6] = xAxis.z; m[7] = yAxis.z; m[8] = zAxis.z;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The diagonal scalar.
                 *
                 ***********************************************/
                inline mat3(const _type scalar)
                {
                    m[0] = scalar; m[1] = 0;      m[2] = 0;
                    m[3] = 0,      m[4] = scalar; m[5] = 0;
                    m[6] = 0,      m[7] = 0;      m[8] = scalar;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The diagonal scalar.
                 * \param position  The position of the item.
                 *
                 ***********************************************/
                mat3(const _type scalar, const vec2<_type> &position)
                {
                    m[0] = scalar; m[1] = 0;      m[2] = position.x;
                    m[3] = 0;      m[4] = scalar; m[5] = position.y;
                    m[6] = 0;      m[7] = 0;      m[8] = scalar;
                }

                /********************************************//**
                 * \brief Copies from a 3x3 matrix
                 *
                 * \param mat       The rotational 2x2 matrix.
                 * \param position  The position of the item.
                 *
                 ***********************************************/
                mat3(const mat2<_type> &mat, const vec2<_type> &position)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1]; m[2] = position.x;
                    m[3] = mat.m[2]; m[4] = mat.m[3]; m[5] = position.y;
                    m[6] = 0;        m[7] = 0;        m[8] = 1;
                }

                /********************************************//**
                 * \brief Copy Constructor of 2x2 matrix
                 ***********************************************/
                inline mat3(const mat2<_type> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Copy Constructor from a 4x4 matrix
                 ***********************************************/
                inline mat3(const mat4<_type> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline mat3(const mat3<_t> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Assignment Copy of 2x2 matrix
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                inline mat3 &operator=(const mat2<_type> &mat)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1]; m[2] = 0;
                    m[3] = mat.m[2]; m[4] = mat.m[3]; m[5] = 0;
                    m[6] = 0;        m[7] = 0;        m[8] = 1;

                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy of 4x4 matrix
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                inline mat3 &operator=(const mat4<_type> &mat)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1]; m[2] = mat.m[2];
                    m[3] = mat.m[4]; m[4] = mat.m[5]; m[5] = mat.m[6];
                    m[6] = mat.m[8]; m[7] = mat.m[9]; m[8] = mat.m[10];

                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline mat3 &operator=(const mat3<_t> &mat)
                {
                    m[0] = mat.m[0]; m[1] = mat.m[1]; m[2] = mat.m[2];
                    m[3] = mat.m[3]; m[4] = mat.m[4]; m[5] = mat.m[5];
                    m[6] = mat.m[6]; m[7] = mat.m[7]; m[8] = mat.m[8];

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
                    assert(index <= 8);

                    return m[index];
                }

                inline const _type &operator[](unsigned short index) const
                {
                    assert(index <= 8);

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
                    assert(row <= 2 && collumn <= 2);

                    return m[3 * row + collumn];
                }

                inline const _type &operator()(unsigned short row, unsigned short collumn) const
                {
                    assert(row <= 2 && collumn <= 2);

                    return *(m + 3 * row + collumn);
                }

                /********************************************//**
                 * \brief Returns the transposed matrix
                 *
                 * \return The transpose.
                 *
                 ***********************************************/
                inline mat3 transpose() const
                {
                    return mat3(
                        m[0], m[3], m[6],
                        m[1], m[4], m[7],
                        m[2], m[5], m[8]);
                }

                /********************************************//**
                 * \brief Inverses the matrix
                 *
                 * \param tolerance of a non existing matrix.
                 * \return Whether an inverse exists.
                 *
                 ***********************************************/
                bool invert(const double tolerance = 0.000006)
                {
                    // Compute adjugate matrix
                    mat3 adj = mat3(
                        +(m[4] * m[8] - m[5] * m[7]), -(m[1] * m[8] - m[2] * m[7]), +(m[1] * m[5] - m[2] * m[4]),
                        -(m[3] * m[8] - m[5] * m[6]), +(m[0] * m[8] - m[2] * m[6]), -(m[0] * m[5] - m[2] * m[3]),
                        +(m[3] * m[7] - m[4] * m[6]), -(m[0] * m[7] - m[1] * m[6]), +(m[0] * m[4] - m[1] * m[3]) );

                    // If determinant equals 0, there is no inverse
                    _type det = m[0] * adj[0] + m[1] * adj[3] + m[2] * adj[6];
                    if(std::abs(det) <= tolerance) return false;

                    *this = (1 / det) * adj;

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
                    return m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7] -
                            m[0] * m[5] * m[7] - m[1] * m[3] * m[8] - m[2] * m[4] * m[6];
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
                template <typename _t> inline mat3 &operator+=(const mat3<_t> &mat) { *this = *this + mat; return *this; }
                template <typename _t> inline mat3 &operator-=(const mat3<_t> &mat) { *this = *this - mat; return *this; }
                template <typename _t> inline mat3 &operator*=(const mat3<_t> &mat) { *this = *this * mat; return *this; }

                // Non-Self modifying
                template <typename _t> inline bool operator!=(const mat3<_t> &mat) const { return !(*this == mat); }
                inline mat3 operator+() const { return *this; }
                inline mat3 operator-() const
                {
                    return mat3(
                        -m[0], -m[1], -m[2],
                        -m[3], -m[4], -m[5],
                        -m[6], -m[7], -m[8] );
                }

                inline friend mat3 operator*(const mat3 &mat, const _type scalar) { return scalar * mat; }
                inline friend mat3 operator*(const _type scalar, const mat3 &mat) { return mat3(
                        scalar * mat.m[0], scalar * mat.m[1], scalar * mat.m[2],
                        scalar * mat.m[3], scalar * mat.m[4], scalar * mat.m[5],
                        scalar * mat.m[6], scalar * mat.m[7], scalar * mat.m[8] );
                }

                template <typename _t>
                inline bool operator==(const mat3<_t> &mat) const
                {
                    return (
                        m[0] == mat.m[0] && m[1] == mat.m[1] && m[2] == mat.m[2] &&
                        m[3] == mat.m[3] && m[4] == mat.m[4] && m[5] == mat.m[5] &&
                        m[6] == mat.m[6] && m[7] == mat.m[7] && m[8] == mat.m[8] );
                }

                template <typename _t>
                inline mat3 operator+(const mat3<_t> &mat) const
                {
                    return mat3(
                        m[0] + mat.m[0], m[1] + mat.m[1], m[2] + mat.m[2],
                        m[3] + mat.m[3], m[4] + mat.m[4], m[5] + mat.m[5],
                        m[6] + mat.m[6], m[7] + mat.m[7], m[8] + mat.m[8] );
                }

                template <typename _t>
                inline mat3 operator-(const mat3<_t> &mat) const
                {
                    return mat3(
                        m[0] - mat.m[0], m[1] - mat.m[1], m[2] - mat.m[2],
                        m[3] - mat.m[3], m[4] - mat.m[4], m[5] - mat.m[5],
                        m[6] - mat.m[6], m[7] - mat.m[7], m[8] - mat.m[8] );
                }

                template <typename _t>
                mat3 operator*(const mat3<_t> &mat) const
                {
                    return mat3(
                        m[0] * mat.m[0] + m[1] * mat.m[3] + m[2] * mat.m[6],
                        m[0] * mat.m[1] + m[1] * mat.m[4] + m[2] * mat.m[7],
                        m[0] * mat.m[2] + m[1] * mat.m[5] + m[2] * mat.m[8],

                        m[3] * mat.m[0] + m[4] * mat.m[3] + m[5] * mat.m[6],
                        m[3] * mat.m[1] + m[4] * mat.m[4] + m[5] * mat.m[7],
                        m[3] * mat.m[2] + m[4] * mat.m[5] + m[5] * mat.m[8],

                        m[6] * mat.m[0] + m[7] * mat.m[3] + m[8] * mat.m[6],
                        m[6] * mat.m[1] + m[7] * mat.m[4] + m[8] * mat.m[7],
                        m[6] * mat.m[2] + m[7] * mat.m[5] + m[8] * mat.m[8] );
                }

                // Multiply vec3 by mat3
                template <typename _t>
                inline vec3<_t> operator*(const vec3<_t> &vec) const
                {
                    return vec3<_t>(
                        m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
                        m[3] * vec.x + m[4] * vec.y + m[5] * vec.z,
                        m[6] * vec.x + m[7] * vec.y + m[8] * vec.z );
                }

                // Multiply vec2 by mat3
                template <typename _t>
                inline vec2<_t> operator*(const vec2<_t> &vec) const
                {
                    return vec2<_t>(
                        m[0] * vec.x + m[1] * vec.y + m[2],
                        m[3] * vec.x + m[4] * vec.y + m[5] );
                }
        };
    }
}

#endif

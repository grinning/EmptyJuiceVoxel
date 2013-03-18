/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 mat4 : A 4x4 Matrix.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __MAT4_H__
#define __MAT4_H__

#include <cassert>
#include <cmath>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! \cond

        template <typename _type> class vec4;

        //! \endcond

        //! 4x4 Matrix
        template <typename _type>
        class mat4
        {
            //-----------------------------------------------------------------------
            protected:
                // Array, row-major
                _type m[16];

            //-----------------------------------------------------------------------
            public:
                // For taking parts
                template <typename _t> friend class mat3;

                /********************************************//**
                 * \brief Computes the matrix according to a position, orientation and scale
                 *
                 * \param position        The position of the item.
                 * \param orientation     The orientation of the item.
                 * \param scale           The scale of the item.
                 * \param origin          The origin of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat4<_t> createMatrix(const vec3<_t> &position, const quat<_t> &orientation,
                                             const vec3<_t> &scale = vec3<_t>(1.0f), const vec3<_t> &origin = vec3<_t>())
                {
                    // quaternion -> matrix
                    mat3<_t> rotMatrix;
                    orientation.toMatrix(rotMatrix);

                    // Scale/Translate
                    rotMatrix[0] *= scale.x; rotMatrix[1] *= scale.y; rotMatrix[2] *= scale.z;
                    rotMatrix[3] *= scale.x; rotMatrix[4] *= scale.y; rotMatrix[5] *= scale.z;
                    rotMatrix[6] *= scale.x; rotMatrix[7] *= scale.y; rotMatrix[8] *= scale.z;

                    // Add translation (rotate origin and add position)
                    return mat4<_t>(rotMatrix, rotMatrix * -origin + position);
                }

                /********************************************//**
                 * \brief Computes the inverse matrix according to a position, orientation and scale
                 *
                 * \param position        The position of the item.
                 * \param orientation     The orientation of the item.
                 * \param scale           The scale of the item.
                 * \param origin          The origin of the item.
                 * \return The computed matrix.
                 *
                 ***********************************************/
                template <typename _t>
                static mat4<_t> createMatrixInverse(const vec3<_t> &position, const quat<_t> &orientation,
                                                    const vec3<_t> &scale = vec3<_t>(1.0f), const vec3<_t> &origin = vec3<_t>())
                {
                    // quaternion -> inverse -> matrix
                    mat3<_t> rotMatrix;
                    orientation.inverse().toMatrix(rotMatrix);

                    // Inverse Scale
                    vec3<_t> invScale = 1.0f / scale;

                    // Apply Scale
                    rotMatrix[0] *= invScale.x; rotMatrix[1] *= invScale.x; rotMatrix[2] *= invScale.x;
                    rotMatrix[3] *= invScale.y; rotMatrix[4] *= invScale.y; rotMatrix[5] *= invScale.y;
                    rotMatrix[6] *= invScale.z; rotMatrix[7] *= invScale.z; rotMatrix[8] *= invScale.z;

                    // Add translation (rotate position and add origin)
                    return mat4<_t>(rotMatrix, rotMatrix * -position + origin);
                }

                /********************************************//**
                 * \brief Constructor, NOTE: does not initialize
                 ***********************************************/
                inline mat4() {}

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline mat4(const _type m00, const _type m01, const _type m02, const _type m03,
                            const _type m10, const _type m11, const _type m12, const _type m13,
                            const _type m20, const _type m21, const _type m22, const _type m23,
                            const _type m30, const _type m31, const _type m32, const _type m33)
                {
                    m[0]  = m00; m[1]  = m01; m[2]  = m02; m[3]  = m03;
                    m[4]  = m10; m[5]  = m11; m[6]  = m12; m[7]  = m13;
                    m[8]  = m20; m[9]  = m21; m[10] = m22; m[11] = m23;
                    m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param x         The x (right) vector.
                 * \param y         The y (up) vector.
                 * \param z         The z (front) vector.
                 * \param position  The position of the item.
                 *
                 ***********************************************/
                mat4(const vec3<_type> &x, const vec3<_type> &y, const vec3<_type> &z, const vec3<_type> &position = vec3<_type>())
                {
                    vec3<_type> xAxis = x.normalize();
                    vec3<_type> yAxis = y.normalize();
                    vec3<_type> zAxis = z.normalize();

                    m[0]  = xAxis.x; m[1]  = yAxis.x; m[2]  = zAxis.x; m[3]  = position.x;
                    m[4]  = xAxis.y; m[5]  = yAxis.y; m[6]  = zAxis.y; m[7]  = position.y;
                    m[8]  = xAxis.z; m[9]  = yAxis.z; m[10] = zAxis.z; m[11] = position.z;
                    m[12] = 0;       m[13] = 0;       m[14] = 0;       m[15] = 1;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The diagonal scalar.
                 *
                 ***********************************************/
                inline mat4(const _type scalar)
                {
                    m[0]  = scalar; m[1]  = 0;      m[2]  = 0;      m[3]  = 0;
                    m[4]  = 0;      m[5]  = scalar; m[6]  = 0;      m[7]  = 0;
                    m[8]  = 0;      m[9]  = 0;      m[10] = scalar; m[11] = 0;
                    m[12] = 0;      m[13] = 0;      m[14] = 0;      m[15] = scalar;
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param scalar    The diagonal scalar.
                 * \param position  The position of the item.
                 *
                 ***********************************************/
                mat4(const _type scalar, const vec3<_type> &position)
                {
                    m[0]  = scalar; m[1]  = 0;      m[2]  = 0;      m[3]  = position.x;
                    m[4]  = 0;      m[5]  = scalar; m[6]  = 0;      m[7]  = position.y;
                    m[8]  = 0;      m[9]  = 0;      m[10] = scalar; m[11] = position.z;
                    m[12] = 0;      m[13] = 0;      m[14] = 0;      m[15] = scalar;
                }

                /********************************************//**
                 * \brief Copies from a 3x3 matrix
                 *
                 * \param mat       The rotational 3x3 matrix.
                 * \param position  The position of the item.
                 *
                 ***********************************************/
                mat4(const mat3<_type> &mat, const vec3<_type> &position)
                {
                    m[0]  = mat.m[0]; m[1]  = mat.m[1]; m[2]  = mat.m[2]; m[3]  = position.x;
                    m[4]  = mat.m[3]; m[5]  = mat.m[4]; m[6]  = mat.m[5]; m[7]  = position.y;
                    m[8]  = mat.m[6]; m[9]  = mat.m[7]; m[10] = mat.m[8]; m[11] = position.z;
                    m[12] = 0;        m[13] = 0;        m[14] = 0;        m[15] = 1;
                }

                /********************************************//**
                 * \brief Copies from a 3x3 matrix
                 ***********************************************/
                inline mat4(const mat3<_type> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline mat4(const mat4<_t> &mat)
                {
                    *this = mat;
                }

                /********************************************//**
                 * \brief Assignment Copy of 3x3 matrix
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                inline mat4 &operator=(const mat3<_type> &mat)
                {
                    m[0]  = mat.m[0]; m[1]  = mat.m[1]; m[2]  = mat.m[2]; m[3]  = 0;
                    m[4]  = mat.m[3]; m[5]  = mat.m[4]; m[6]  = mat.m[5]; m[7]  = 0;
                    m[8]  = mat.m[6]; m[9]  = mat.m[7]; m[10] = mat.m[8]; m[11] = 0;
                    m[12] = 0;        m[13] = 0;        m[14] = 0;        m[15] = 1;

                    return *this;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline mat4 &operator=(const mat4<_t> &mat)
                {
                    m[0]  = mat.m[0];  m[1]  = mat.m[1];  m[2]  = mat.m[2];  m[3]  = mat.m[3];
                    m[4]  = mat.m[4];  m[5]  = mat.m[5];  m[6]  = mat.m[6];  m[7]  = mat.m[7];
                    m[8]  = mat.m[8];  m[9]  = mat.m[9];  m[10] = mat.m[10]; m[11] = mat.m[11];
                    m[12] = mat.m[12]; m[13] = mat.m[13]; m[14] = mat.m[14]; m[15] = mat.m[15];

                    return *this;
                }

                /********************************************//**
                 * \brief Fetches the value at a given index
                 *
                 * \param index The index of the parameter
                 * \return The asked parameter.
                 *
                 ***********************************************/
                inline _type &operator[](unsigned short index)
                {
                    assert(index <= 15);

                    return m[index];
                }

                inline const _type &operator[](unsigned short index) const
                {
                    assert(index <= 15);

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
                    assert(row <= 3 && collumn <= 3);

                    return m[4 * row + collumn];
                }

                inline const _type &operator()(unsigned short row, unsigned short collumn) const
                {
                    assert(row <= 3 && collumn <= 3);

                    return *(m + 4 * row + collumn);
                }

                /********************************************//**
                 * \brief Returns the transposed matrix
                 *
                 * \return The transpose.
                 *
                 ***********************************************/
                inline mat4 transpose() const
                {
                    return mat4(
                        m[0], m[4], m[8], m[12],
                        m[1], m[5], m[9], m[13],
                        m[2], m[6], m[10], m[14],
                        m[3], m[7], m[11], m[15] );
                }

                /********************************************//**
                 * \brief Inverses the matrix
                 *
                 * \param tolerance The tolerance of a non existing matrix.
                 * \return Whether an inverse matrix exists.
                 *
                 ***********************************************/
                bool invert(const double tolerance = 0.000006f)
                {
                    // Determinants of 2x2 submatrices
                    _type S0 = m[0] * m[5] - m[1] * m[4];
                    _type S1 = m[0] * m[6] - m[2] * m[4];
                    _type S2 = m[0] * m[7] - m[3] * m[4];
                    _type S3 = m[1] * m[6] - m[2] * m[5];
                    _type S4 = m[1] * m[7] - m[3] * m[5];
                    _type S5 = m[2] * m[7] - m[3] * m[6];

                    _type C5 = m[10] * m[15] - m[11] * m[14];
                    _type C4 = m[9] * m[15] - m[11] * m[13];
                    _type C3 = m[9] * m[14] - m[10] * m[13];
                    _type C2 = m[8] * m[15] - m[11] * m[12];
                    _type C1 = m[8] * m[14] - m[10] * m[12];
                    _type C0 = m[8] * m[13] - m[9] * m[12];

                    // If determinant equals 0, there is no inverse
                    _type det = S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
                    if(std::abs(det) <= tolerance) return false;

                    // Compute adjugate matrix
                    *this = (1 / det) * mat4(
                         m[5] * C5  - m[6] * C4  + m[7] * C3,  -m[1] * C5 + m[2] * C4  - m[3] * C3,
                         m[13] * S5 - m[14] * S4 + m[15] * S3, -m[9] * S5 + m[10] * S4 - m[11] * S3,

                        -m[4] * C5  + m[6] * C2  - m[7] * C1,   m[0] * C5 - m[2] * C2  + m[3] * C1,
                        -m[12] * S5 + m[14] * S2 - m[15] * S1,  m[8] * S5 - m[10] * S2 + m[11] * S1,

                         m[4] * C4  - m[5] * C2  + m[7] * C0,  -m[0] * C4 + m[1] * C2  - m[3] * C0,
                         m[12] * S4 - m[13] * S2 + m[15] * S0, -m[8] * S4 + m[9] * S2  - m[11] * S0,

                        -m[4] * C3  + m[5] * C1  - m[6] * C0,   m[0] * C3 - m[1] * C1  + m[2] * C0,
                        -m[12] * S3 + m[13] * S1 - m[14] * S0,  m[8] * S3 - m[9] * S1  + m[10] * S0 );

                    return true;
                }

                /********************************************//**
                 * \brief Computes the determinant of the matrix
                 *
                 * \return The determinant.
                 *
                 ***********************************************/
                _type determinant()
                {
                    // Determinants of 2x2 submatrices
                    _type S0 = m[0] * m[5] - m[1] * m[4];
                    _type S1 = m[0] * m[6] - m[2] * m[4];
                    _type S2 = m[0] * m[7] - m[3] * m[4];
                    _type S3 = m[1] * m[6] - m[2] * m[5];
                    _type S4 = m[1] * m[7] - m[3] * m[5];
                    _type S5 = m[2] * m[7] - m[3] * m[6];

                    _type C5 = m[10] * m[15] - m[11] * m[14];
                    _type C4 = m[9] * m[15] - m[11] * m[13];
                    _type C3 = m[9] * m[14] - m[10] * m[13];
                    _type C2 = m[8] * m[15] - m[11] * m[12];
                    _type C1 = m[8] * m[14] - m[10] * m[12];
                    _type C0 = m[8] * m[13] - m[9] * m[12];

                    return S0 * C5 - S1 * C4 + S2 * C3 + S3 * C2 - S4 * C1 + S5 * C0;
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
                template <typename _t> inline mat4 &operator+=(const mat4<_t> &mat) { *this = *this + mat; return *this; }
                template <typename _t> inline mat4 &operator-=(const mat4<_t> &mat) { *this = *this - mat; return *this; }
                template <typename _t> inline mat4 &operator*=(const mat4<_t> &mat) { *this = *this * mat; return *this; }

                // Non-Self modifying
                template <typename _t> inline bool operator!=(const mat4<_t> &mat) const { return !(*this == mat); }
                inline mat4 operator+() const { return *this; }
                inline mat4 operator-() const
                {
                    return mat4(
                        -m[0], -m[1], -m[2], -m[3],
                        -m[4], -m[5], -m[6], -m[7],
                        -m[8], -m[9], -m[10], -m[11],
                        -m[12], -m[13], -m[14], -m[15] );
                }

                inline friend mat4 operator*(const mat4 &mat, const _type scalar) { return scalar * mat; }
                inline friend mat4 operator*(const _type scalar, const mat4 &mat) { return mat4(
                        scalar * mat.m[0],  scalar * mat.m[1],  scalar * mat.m[2],  scalar * mat.m[3],
                        scalar * mat.m[4],  scalar * mat.m[5],  scalar * mat.m[6],  scalar * mat.m[7],
                        scalar * mat.m[8],  scalar * mat.m[9],  scalar * mat.m[10], scalar * mat.m[11],
                        scalar * mat.m[12], scalar * mat.m[13], scalar * mat.m[14], scalar * mat.m[15] );
                }

                template <typename _t>
                inline bool operator==(const mat4<_t> &mat) const
                {
                    return (
                        m[0] == mat.m[0] && m[1] == mat.m[1] && m[2] == mat.m[2] && m[3] == mat.m[3] &&
                        m[4] == mat.m[4] && m[5] == mat.m[5] && m[6] == mat.m[6] && m[7] == mat.m[7] &&
                        m[8] == mat.m[8] && m[8] == mat.m[8] && m[10] == mat.m[10] && m[11] == mat.m[11] &&
                        m[12] == mat.m[12] && m[13] == mat.m[13] && m[14] == mat.m[14] && m[15] == mat.m[15] );
                }

                template <typename _t>
                inline mat4 operator+(const mat4<_t> &mat) const
                {
                    return mat4(
                        m[0] + mat.m[0], m[1] + mat.m[1], m[2] + mat.m[2], m[3] + mat.m[3],
                        m[4] + mat.m[4], m[5] + mat.m[5], m[6] + mat.m[6], m[7] + mat.m[7],
                        m[8] + mat.m[8], m[9] + mat.m[9], m[10] + mat.m[10], m[11] + mat.m[11],
                        m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15] );
                }

                template <typename _t>
                inline mat4 operator-(const mat4<_t> &mat) const
                {
                    return mat4(
                        m[0] - mat.m[0], m[1] - mat.m[1], m[2] - mat.m[2], m[3] - mat.m[3],
                        m[4] - mat.m[4], m[5] - mat.m[5], m[6] - mat.m[6], m[7] - mat.m[7],
                        m[8] - mat.m[8], m[9] - mat.m[9], m[10] - mat.m[10], m[11] - mat.m[11],
                        m[12] - mat.m[12], m[13] - mat.m[13], m[14] - mat.m[14], m[15] - mat.m[15] );
                }

                template <typename _t>
                mat4 operator*(const mat4<_t> &mat) const
                {
                    return mat4(
                        m[0] * mat.m[0] + m[1] * mat.m[4] + m[2] * mat.m[8] + m[3] * mat.m[12],
                        m[0] * mat.m[1] + m[1] * mat.m[5] + m[2] * mat.m[9] + m[3] * mat.m[13],
                        m[0] * mat.m[2] + m[1] * mat.m[6] + m[2] * mat.m[10] + m[3] * mat.m[14],
                        m[0] * mat.m[3] + m[1] * mat.m[7] + m[2] * mat.m[11] + m[3] * mat.m[15],

                        m[4] * mat.m[0] + m[5] * mat.m[4] + m[6] * mat.m[8] + m[7] * mat.m[12],
                        m[4] * mat.m[1] + m[5] * mat.m[5] + m[6] * mat.m[9] + m[7] * mat.m[13],
                        m[4] * mat.m[2] + m[5] * mat.m[6] + m[6] * mat.m[10] + m[7] * mat.m[14],
                        m[4] * mat.m[3] + m[5] * mat.m[7] + m[6] * mat.m[11] + m[7] * mat.m[15],

                        m[8] * mat.m[0] + m[9] * mat.m[4] + m[10] * mat.m[8] + m[11] * mat.m[12],
                        m[8] * mat.m[1] + m[9] * mat.m[5] + m[10] * mat.m[9] + m[11] * mat.m[13],
                        m[8] * mat.m[2] + m[9] * mat.m[6] + m[10] * mat.m[10] + m[11] * mat.m[14],
                        m[8] * mat.m[3] + m[9] * mat.m[7] + m[10] * mat.m[11] + m[11] * mat.m[15],

                        m[12] * mat.m[0] + m[13] * mat.m[4] + m[14] * mat.m[8] + m[15] * mat.m[12],
                        m[12] * mat.m[1] + m[13] * mat.m[5] + m[14] * mat.m[9] + m[15] * mat.m[13],
                        m[12] * mat.m[2] + m[13] * mat.m[6] + m[14] * mat.m[10] + m[15] * mat.m[14],
                        m[12] * mat.m[3] + m[13] * mat.m[7] + m[14] * mat.m[11] + m[15] * mat.m[15] );
                }

                // Multiply vec4 by mat4
                template <typename _t>
                inline vec4<_t> operator*(const vec4<_t> &vec) const
                {
                    return vec4<_t>(
                        m[0] * vec.x  + m[1] * vec.y  + m[2] * vec.z  + m[3] * vec.w,
                        m[4] * vec.x  + m[5] * vec.y  + m[6] * vec.z  + m[7] * vec.w,
                        m[8] * vec.x  + m[9] * vec.y  + m[10] * vec.z + m[11] * vec.w,
                        m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w );
                }

                // Multiply vec3 by mat4
                template <typename _t>
                inline vec3<_t> operator*(const vec3<_t> &vec) const
                {
                    return vec3<_t>(
                        m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3],
                        m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7],
                        m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] );
                }
        };
    }
}

#endif

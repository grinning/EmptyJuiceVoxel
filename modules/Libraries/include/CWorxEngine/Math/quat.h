/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 quat : Mathematical concept of a quaternion
 optimised for orientation.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <iostream>

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Math namespace
    namespace Math
    {
        //! Quaternion
        template <typename _type>
        class quat
        {
            //-----------------------------------------------------------------------
            public:
                // PUBLIC
                _type w;
                _type x;
                _type y;
                _type z;

                /********************************************//**
                 * \brief Constructor
                 ***********************************************/
                inline quat() :
                    w(1), x(0), y(0), z(0)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param fw  The w component of the quaternion.
                 *
                 ***********************************************/
                inline quat(const _type fw) :
                    w(fw), x(0), y(0), z(0)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param fw    The w component of the quaternion.
                 * \param fx    The x component of the quaternion.
                 * \param fy    The y component of the quaternion.
                 * \param fz    The z component of the quaternion.
                 *
                 ***********************************************/
                inline quat(const _type fw, const _type fx, const _type fy, const _type fz) :
                    w(fw), x(fx), y(fy), z(fz)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param vec   Vector to take for x, y and z components.
                 *
                 ***********************************************/
                inline quat(const vec3<_type> &vec) :
                    w(0), x(vec.x), y(vec.y), z(vec.z)
                {
                }

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param angle    The angle in radians.
                 * \param axis    The axis to rotate around in vector form.
                 *
                 ***********************************************/
                inline quat(const _type angle, const vec3<_type> &axis) :
                    w(1), x(0), y(0), z(0)
                {
                    fromAngleAxis(angle, axis);
                }

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                template <typename _t>
                inline quat(const quat<_t> &qt)
                {
                    *this = qt;
                }

                /********************************************//**
                 * \brief Assignment Copy
                 *
                 * \return Itself.
                 *
                 ***********************************************/
                template <typename _t>
                inline quat &operator=(const quat<_t> &qt)
                {
                    w = qt.w; x = qt.x; y = qt.y; z = qt.z;
                    return *this;
                }

                /********************************************//**
                 * \brief Returns true if the magnitude is 0.0
                 *
                 * \return True if the magnitude is 0.0
                 *
                 ***********************************************/
                inline bool isZero() const
                {
                    return !w && !x && !y && !z;
                }

                /********************************************//**
                 * \brief Normalizes the quaternion
                 *
                 * \return The normalized quaternion.
                 *
                 ***********************************************/
                inline quat normalize() const
                {
                    double mag = magnitude();
                    return !mag ? *this : *this / mag;
                }

                /********************************************//**
                 * \brief Inverses the quaternion (conjugate)
                 *
                 * \return The inverse.
                 *
                 ***********************************************/
                inline quat inverse() const
                {
                    return quat(w, -x, -y, -z);
                }

                /********************************************//**
                 * \brief Fetch the magnitude of the quaternion
                 *
                 * \return The magnitude of the quaternion.
                 *
                 ***********************************************/
                inline double magnitude() const
                {
                    return sqrt(w * w + x * x + y * y + z * z);
                }

                /********************************************//**
                 * \brief Computes a quaternion from a rotation axis and angle
                 *
                 * \param angle    The angle in radians.
                 * \param axis    The axis to rotate around in vector form.
                 * \return Itself.
                 *
                 ***********************************************/
                quat &fromAngleAxis(const _type angle, const vec3<_type> &axis)
                {
                    // validate axis
                    if(axis.isZero()) return *this;

                    double halfAngle = angle * 0.5f;
                    double scale = sin(halfAngle) / axis.magnitude();

                    x = axis.x * scale;
                    y = axis.y * scale;
                    z = axis.z * scale;
                    w = cos(halfAngle);

                    return *this;
                }

                /********************************************//**
                 * \brief Computes the angle and axis from the quaternion
                 *
                 * \param angle The float to store the angle in.
                 * \param axis    The vec3 to store the axis in.
                 * \return void
                 *
                 ***********************************************/
                void toAngleAxis(_type &angle, vec3<_type> &axis) const
                {
                    double halfAngle = acos(w);
                    double scale = 1.0f / sin(halfAngle);

                    angle = halfAngle * 2.0f;
                    axis.x = x * scale;
                    axis.y = y * scale;
                    axis.z = z * scale;
                }

                /********************************************//**
                 * \brief Converts the quaternion to a 3x3 rotation matrix
                 *
                 * \param mat   The mat3 to store the matrix in.
                 * \return void
                 *
                 ***********************************************/
                void toMatrix(mat3<_type> &mat) const
                {
                    float x2 = x + x;
                    float y2 = y + y;
                    float z2 = z + z;

                    float wx = x2 * w;
                    float wy = y2 * w;
                    float wz = z2 * w;
                    float xx = x2 * x;
                    float xy = y2 * x;
                    float xz = z2 * x;
                    float yy = y2 * y;
                    float yz = z2 * y;
                    float zz = z2 * z;

                    mat[0] = 1 - (yy + zz); mat[1] = xy - wz; mat[2] = xz + wy;
                    mat[3] = xy + wz; mat[4] = 1 - (xx + zz); mat[5] = yz - wx;
                    mat[6] = xz - wy; mat[7] = yz + wx; mat[8] = 1 - (xx + yy);
                }

                //-----------------------------------------------------------------------
                /** Basic Quaternion arithmetics
                 * Comparison
                 * Negation
                 * Adding
                 * Subtracting
                 * Multiplying
                 */

                // Self modifying
                template <typename _t> inline quat &operator+=(const _t scalar) { w += scalar; x += scalar; y += scalar; z += scalar; return *this; }
                template <typename _t> inline quat &operator-=(const _t scalar) { w -= scalar; x -= scalar; y -= scalar; z -= scalar; return *this; }
                template <typename _t> inline quat &operator*=(const _t scalar) { w *= scalar; x *= scalar; y *= scalar; z *= scalar; return *this; }
                template <typename _t> inline quat &operator/=(const _t scalar) { w /= scalar; x /= scalar; y /= scalar; z /= scalar; return *this; }
                template <typename _t> inline quat &operator+=(const quat<_t> &qt) { w += qt.w; x += qt.x; y += qt.y; z += qt.z; return *this; }
                template <typename _t> inline quat &operator-=(const quat<_t> &qt) { w -= qt.w; x -= qt.x; y -= qt.x; z -= qt.z; return *this; }
                template <typename _t> inline quat &operator*=(const quat<_t> &qt) { *this = *this * qt; return *this; }

                // Non-Self modifying
                template <typename _t> inline bool operator==(const quat<_t> &qt) const { return w == qt.w && x == qt.x && y == qt.y && z == qt.z; }
                template <typename _t> inline bool operator!=(const quat<_t> &qt) const { return !(*this == qt); }
                inline quat operator+() const { return *this; }
                inline quat operator-() const { return quat(-w, -x, -y, -z); }

                friend inline quat operator*(const _type scalar, const quat &qt) { return quat(scalar * qt.w, scalar * qt.x, scalar * qt.y, scalar * qt.z); }
                friend inline quat operator/(const _type scalar, const quat &qt) { return quat(scalar / qt.w, scalar / qt.x, scalar / qt.y, scalar / qt.z); }

                template <typename _t> inline quat operator+(const _t scalar) const { return quat(w + scalar, x + scalar, y + scalar, z + scalar); }
                template <typename _t> inline quat operator-(const _t scalar) const { return quat(w - scalar, x - scalar, y - scalar, z - scalar); }
                template <typename _t> inline quat operator*(const _t scalar) const { return quat(w * scalar, x * scalar, y * scalar, z * scalar); }
                template <typename _t> inline quat operator/(const _t scalar) const { return quat(w / scalar, x / scalar, y / scalar, z / scalar); }
                template <typename _t> inline quat operator+(const quat<_t> &qt) const { return quat(w + qt.w, x + qt.x, y + qt.y, z + qt.z); }
                template <typename _t> inline quat operator-(const quat<_t> &qt) const { return quat(w - qt.w, x - qt.x, y - qt.y, z - qt.z); }
                template <typename _t> inline quat operator*(const quat<_t> &qt) const
                {
                    return quat(
                        w * qt.w - x * qt.x - y * qt.y - z * qt.z,
                        w * qt.x + x * qt.w + y * qt.z - z * qt.y,
                        w * qt.y + y * qt.w + z * qt.x - x * qt.z,
                        w * qt.z + z * qt.w + x * qt.y - y * qt.x );
                }

                // Rotate vector by quaternion
                template <typename _t>
                inline vec3<_t> operator*(const vec3<_t> &vec) const
                {
                    // want = q * v * q^-1 (sandwich product)
                    // in which v = (0, x, y, z) and q^-1 = (w, -x, -y, -z)
                    // because of the 0 we write it out to spare some calculations
                    // first we compute v * q^-1
                    _t qw = vec.x * x + vec.y * y + vec.z * z;
                    _t qx = vec.x * w - vec.y * z + vec.z * y;
                    _t qy = vec.y * w - vec.z * x + vec.x * z;
                    _t qz = vec.z * w - vec.x * y + vec.y * x;

                    // next we compute q * the above
                    return vec3<_t>(
                        w * qx + x * qw + y * qz - z * qy,
                        w * qy + y * qw + z * qx - x * qz,
                        w * qz + z * qw + x * qy - y * qx);
                }

                // Stream Output
                inline friend std::ostream &operator<<(std::ostream &out, const quat &qt)
                    { out << qt.w << " " << qt.x << " " << qt.y << " " << qt.z; return out; }

                // Stream Input
                inline friend std::istream &operator>>(std::istream &in, quat &qt)
                    { in >> qt.w >> qt.x >> qt.y >> qt.z; return in; }
        };
    }
}

#endif

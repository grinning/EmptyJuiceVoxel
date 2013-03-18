/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Prerequisites : Utilities used globally in the engine
 available for all classes and files

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __CWORX_ENGINE_PREREQUISITES_H__
#define __CWORX_ENGINE_PREREQUISITES_H__

// GLEW & GLFW
#define GLEW_STATIC
#define GLEW_NO_GLU
#define GLFW_NO_GLU

// Import headers for Windows
#if defined(_WIN32) || defined(__WIN32__)
#   include "GL/glew.h"
#   include "GL/glfw_win.h"

// Import headers for Unix
#else
#   include "GL/glew.h"
#   include "GL/glfw_unix.h"
#endif

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

//-----------------------------------------------------------------------
// Define CWE_DLL Import/Export spec for Windows
#if defined(_WIN32) || defined(__WIN32__)
#   ifdef __CWORX_ENGINE_EXPORT__
#       define CWE_DLL __declspec(dllexport)
#   else
#       define CWE_DLL __declspec(dllimport)
#   endif

// Define CWE_DLL spec for other platforms
#else
#   define CWE_DLL
#endif

//-----------------------------------------------------------------------
// Standard Includes
#include <algorithm>
#include <climits>
#include <fstream>
#include <functional>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stdint.h>
#include <typeinfo>
#include <vector>

// Maths
#include "Math/mat2.h"
#include "Math/mat3.h"
#include "Math/mat4.h"
#include "Math/quat.h"
#include "Math/vec2.h"
#include "Math/vec3.h"
#include "Math/vec4.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    //-----------------------------------------------------------------------
    // External
    namespace External
    {
        class File;
        class MTLFile;
        class OBJFile;
    }

    //-----------------------------------------------------------------------
    // Geometry
    namespace Geometry
    {
        class DataArray;
        class Material;
        class Mesh;
        class Primitive;
        class Renderable;
        class RenderQueue;
        class Viewport;
    }

    //-----------------------------------------------------------------------
    // Shaders
    namespace Shader
    {
        class Shader;
        class Depth;
        class Flat;
        class Geometry;
        class Light;
    }

    //-----------------------------------------------------------------------
    // Hardware
    namespace Hardware
    {
        class Buffer;
        class Object;
        class Program;
        class RenderTarget;
        class Shader;
        class Texture;
    }

    //-----------------------------------------------------------------------
    // Scene
    class Camera;
    class Light;
    class Node;
    class Object;
    class Scene;
    class ShadowBuffer;

    //-----------------------------------------------------------------------
    // GUI
    class Font;
    class Overlay;

    //-----------------------------------------------------------------------
    // Define all possible OpenGL versions
    namespace OpenGL
    {
        enum OpenGL
        {
            v3_2,
            v3_3,
            v4_0,
            v4_1,
            v4_2,
            v4_3,

            INVALID // On failure
        };
    }

    //-----------------------------------------------------------------------
    // Define spaces in which to transform
    namespace TransformSpace
    {
        enum TransformSpace
        {
            LOCAL,
            PARENT,
            WORLD
        };
    }

    //-----------------------------------------------------------------------
    // Define projection types
    namespace ProjectionType
    {
        enum ProjectionType
        {
            PROJECTION_ORTHOGRAPHIC,
            PROJECTION_PERSPECTIVE
        };
    }

    //-----------------------------------------------------------------------
    // Some Mathematical helper variables and functions
    namespace Math
    {
        //-----------------------------------------------------------------------
        // Mathematical Constants

        extern CWE_DLL const double PI;
        extern CWE_DLL const double HALF_PI;
        extern CWE_DLL const double TWO_PI;
        extern CWE_DLL const double RADIAN_TO_DEGREE;
        extern CWE_DLL const double DEGREE_TO_RADIAN;

        //-----------------------------------------------------------------------
        // Some useful typedefs ^.^

        typedef vec2<short>         vec2s;
        typedef vec2<int>           vec2i;
        typedef vec2<unsigned int>  vec2ui;
        typedef vec2<float>         vec2f;
        typedef vec2<double>        vec2d;

        typedef vec3<short>         vec3s;
        typedef vec3<int>           vec3i;
        typedef vec3<unsigned int>  vec3ui;
        typedef vec3<float>         vec3f;
        typedef vec3<double>        vec3d;

        typedef vec4<short>         vec4s;
        typedef vec4<int>           vec4i;
        typedef vec4<unsigned int>  vec4ui;
        typedef vec4<float>         vec4f;
        typedef vec4<double>        vec4d;

        typedef quat<float>         fquat;
        typedef quat<double>        dquat;

        typedef mat2<float>         mat2f;
        typedef mat2<double>        mat2d;

        typedef mat3<float>         mat3f;
        typedef mat3<double>        mat3d;

        typedef mat4<float>         mat4f;
        typedef mat4<double>        mat4d;

        //-----------------------------------------------------------------------
        // Calculate a projection matrix
        CWE_DLL mat4f projectionMatrix(const ProjectionType::ProjectionType &type, float right, float top, float near, float far);

        // Calculate an NDC to clip matrix
        CWE_DLL mat2f NDCToClipMatrix(const ProjectionType::ProjectionType &type, const mat4f &projectionMatrix);
    }

    //-----------------------------------------------------------------------
    // User Input Characters
    namespace Char
    {
        enum Char
        {
            // Unicode characters
            Exclamation         = '!',
            InverseExclamation  = '¡',
            Quotation           = '"',
            Hash                = '#',
            Dollar              = '$',
            Percentage          = '%',
            Amp                 = '&',
            ParenthesesOpen     = '(',
            ParenthesesClose    = ')',
            Asterisk            = '*',
            Plus                = '+',
            Comma               = ',',
            Minus               = '-',
            Period              = '.',
            Slash               = '/',
            Colon               = ':',
            Semicolon           = ';',
            LesserThan          = '<',
            Equal               = '=',
            GreaterThan         = '>',
            Question            = '?',
            InverseQuestion     = '¿',
            At                  = '@',
            SquareBracketOpen   = '[',
            SquareBracketClose  = ']',
            Circumflex          = '^',
            Underscore          = '_',
            GraveAccent         = '`',
            CurlyBracketOpen    = '{',
            CurlyBracketClose   = '}',
            Vertical            = '|',
            Tilde               = '~',
            Cent                = '¢',
            Pound               = '£',
            Currency            = '¤',
            Yen                 = '¥',
            VerticalSplit       = '¦',
            Section             = '§',
            Umlaut              = '¨',
            Copyright           = '©',
            OrdinalA            = 'ª',
            GuillemetOpen       = '«',
            GuillemetClose      = '»',
            Negation            = '¬',
            Registered          = '®',
            Macron              = '¯',
            Degree              = '°',
            PlusMinus           = '±',
            Squared             = '²',
            Cubed               = '³',
            AcuteAcent          = '´',
            Micro               = 'µ',
            Pilcrow             = '¶',
            Interpunct          = '·',
            Cedilla             = '¸',
            OrdinalO            = 'º',
            OneFourth           = '¼',
            Half                = '½',
            ThreeFourths        = '¾',
            Space               = ' ',

            // Special
            Newline         = '\n',
            HorizontalTab   = '\t',
            VerticalTab     = '\v',
            Backspace       = '\b',
            Backslash       = '\\',
            Apostrophe      = '\'',

            // Numbers
            Num0 = '0',
            Num1 = '1',
            Num2 = '2',
            Num3 = '3',
            Num4 = '4',
            Num5 = '5',
            Num6 = '6',
            Num7 = '7',
            Num8 = '8',
            Num9 = '9',

            // Alphabet
            A = 'A',
            B = 'B',
            C = 'C',
            D = 'D',
            E = 'E',
            F = 'F',
            G = 'G',
            H = 'H',
            I = 'I',
            J = 'J',
            K = 'K',
            L = 'L',
            M = 'M',
            N = 'N',
            O = 'O',
            P = 'P',
            Q = 'Q',
            R = 'R',
            S = 'S',
            T = 'T',
            U = 'U',
            V = 'V',
            W = 'W',
            X = 'X',
            Y = 'Y',
            Z = 'Z',

            a = 'a',
            b = 'b',
            c = 'c',
            d = 'd',
            e = 'e',
            f = 'f',
            g = 'g',
            h = 'h',
            i = 'i',
            j = 'j',
            k = 'k',
            l = 'l',
            m = 'm',
            n = 'n',
            o = 'o',
            p = 'p',
            q = 'q',
            r = 'r',
            s = 's',
            t = 't',
            u = 'u',
            v = 'v',
            w = 'w',
            x = 'x',
            y = 'y',
            z = 'z'
        };
    }

    //-----------------------------------------------------------------------
    // User Input Keys
    namespace Key
    {
        enum MouseKey
        {
            Mouse1      = GLFW_MOUSE_BUTTON_1,
            Mouse2      = GLFW_MOUSE_BUTTON_2,
            Mouse3      = GLFW_MOUSE_BUTTON_3,
            Mouse4      = GLFW_MOUSE_BUTTON_4,
            Mouse5      = GLFW_MOUSE_BUTTON_5,
            Mouse6      = GLFW_MOUSE_BUTTON_6,
            Mouse7      = GLFW_MOUSE_BUTTON_7,
            Mouse8      = GLFW_MOUSE_BUTTON_8,
            MouseLast   = GLFW_MOUSE_BUTTON_LAST,
            MouseLeft   = GLFW_MOUSE_BUTTON_LEFT,
            MouseMiddle = GLFW_MOUSE_BUTTON_MIDDLE,
            MouseRight  = GLFW_MOUSE_BUTTON_RIGHT
        };

        enum Key
        {
            // 'Special' Keys
            Backspace   = GLFW_KEY_BACKSPACE,
            CapsLock    = GLFW_KEY_CAPS_LOCK,
            Delete      = GLFW_KEY_DEL,
            Down        = GLFW_KEY_DOWN,
            End         = GLFW_KEY_END,
            Enter       = GLFW_KEY_ENTER,
            Escape      = GLFW_KEY_ESC,
            Home        = GLFW_KEY_HOME,
            Insert      = GLFW_KEY_INSERT,
            NumLock     = GLFW_KEY_KP_NUM_LOCK,
            LAlt        = GLFW_KEY_LALT,
            Last        = GLFW_KEY_LAST,
            LCtrl       = GLFW_KEY_LCTRL,
            Left        = GLFW_KEY_LEFT,
            LShift      = GLFW_KEY_LSHIFT,
            LSuper      = GLFW_KEY_LSUPER,
            Menu        = GLFW_KEY_MENU,
            PageDown    = GLFW_KEY_PAGEDOWN,
            PageUp      = GLFW_KEY_PAGEUP,
            Pause       = GLFW_KEY_PAUSE,
            RAlt        = GLFW_KEY_RALT,
            RCtrl       = GLFW_KEY_RCTRL,
            Repeat      = GLFW_KEY_REPEAT,
            Right       = GLFW_KEY_RIGHT,
            RShift      = GLFW_KEY_RSHIFT,
            RSuper      = GLFW_KEY_RSUPER,
            ScrollLock  = GLFW_KEY_SCROLL_LOCK,
            Space       = GLFW_KEY_SPACE,
            Special     = GLFW_KEY_SPECIAL,
            Tab         = GLFW_KEY_TAB,
            Up          = GLFW_KEY_UP,

            // Numpad Numbers
            Numpad0 = GLFW_KEY_KP_0,
            Numpad1 = GLFW_KEY_KP_1,
            Numpad2 = GLFW_KEY_KP_2,
            Numpad3 = GLFW_KEY_KP_3,
            Numpad4 = GLFW_KEY_KP_4,
            Numpad5 = GLFW_KEY_KP_5,
            Numpad6 = GLFW_KEY_KP_6,
            Numpad7 = GLFW_KEY_KP_7,
            Numpad8 = GLFW_KEY_KP_8,
            Numpad9 = GLFW_KEY_KP_9,

            // Numpad
            NumpadAdd       = GLFW_KEY_KP_ADD,
            NumpadDecimal   = GLFW_KEY_KP_DECIMAL,
            NumpadDivide    = GLFW_KEY_KP_DIVIDE,
            NumpadEnter     = GLFW_KEY_KP_ENTER,
            NumpadEqual     = GLFW_KEY_KP_EQUAL,
            NumpadMultiply  = GLFW_KEY_KP_MULTIPLY,
            NumpadSubtract  = GLFW_KEY_KP_SUBTRACT,

            // Function Keys
            F1  = GLFW_KEY_F1,
            F2  = GLFW_KEY_F2,
            F3  = GLFW_KEY_F3,
            F4  = GLFW_KEY_F4,
            F5  = GLFW_KEY_F5,
            F6  = GLFW_KEY_F6,
            F7  = GLFW_KEY_F7,
            F8  = GLFW_KEY_F8,
            F9  = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12,
            F13 = GLFW_KEY_F13,
            F14 = GLFW_KEY_F14,
            F15 = GLFW_KEY_F15,
            F16 = GLFW_KEY_F16,
            F17 = GLFW_KEY_F17,
            F18 = GLFW_KEY_F18,
            F19 = GLFW_KEY_F19,
            F20 = GLFW_KEY_F20,
            F21 = GLFW_KEY_F21,
            F22 = GLFW_KEY_F22,
            F23 = GLFW_KEY_F23,
            F24 = GLFW_KEY_F24,
            F25 = GLFW_KEY_F25,

            // Alphabet
            A = Char::A,
            B = Char::B,
            C = Char::C,
            D = Char::D,
            E = Char::E,
            F = Char::F,
            G = Char::G,
            H = Char::H,
            I = Char::I,
            J = Char::J,
            K = Char::K,
            L = Char::L,
            M = Char::M,
            N = Char::N,
            O = Char::O,
            P = Char::P,
            Q = Char::Q,
            R = Char::R,
            S = Char::S,
            T = Char::T,
            U = Char::U,
            V = Char::V,
            W = Char::W,
            X = Char::X,
            Y = Char::Y,
            Z = Char::Z,

            // Derp?
            Unknown = GLFW_KEY_UNKNOWN
        };
    }

    //-----------------------------------------------------------------------
    // Define callback functors
    namespace Callback
    {
        //! Define the unary callback functor base
        template <typename _arg, typename _return = void>
        struct UnaryBase : public std::unary_function<_arg, _return>
        {
            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~UnaryBase() {}

            /********************************************//**
             * \brief Call the function pointer
             *
             * \param arg   The first argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg arg) = 0;
        };

        //-----------------------------------------------------------------------
        //! Define a unary callback functor
        template <typename _arg, typename _return = void>
        struct Unary : public UnaryBase<_arg, _return>
        {
            // Define the function pointer
            typedef _return (*func_type)(_arg);

            // Pointer
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param fun   Function to point to.
             *
             ***********************************************/
            inline Unary(func_type fun) : func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Unary() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg   The first argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg arg) { return (*func)(arg); }
        };

        //-----------------------------------------------------------------------
        //! Define a unary member callback functor
        template <typename _class, typename _arg, typename _return = void>
        struct UnaryMember : public UnaryBase<_arg, _return>
        {
            // Define the function pointer
            typedef _return (_class::*func_type)(_arg);

            // Pointer
            _class *obj;
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param object    Class object to point to.
             * \param fun       Member function to point to.
             *
             ***********************************************/
            inline UnaryMember(_class &object, func_type fun) : obj(&object), func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~UnaryMember() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg   The first argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg arg) { return (obj->*func)(arg); }
        };

        //-----------------------------------------------------------------------
        //! Define a unary member callback functor to take a silent argument
        template <typename _class, typename _silent, typename _arg, typename _return = void>
        struct UnarySilent : public UnaryBase<_arg, _return>
        {
            // Define the function pointer
            typedef _return (_class::*func_type)(_silent, _arg);

            // Pointer
            _class *obj;
            _silent sil;
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param object    Class object to point to.
             * \param silent    Silent object to pass to the function.
             * \param fun       Member function to point to.
             *
             ***********************************************/
            inline UnarySilent(_class &object, _silent silent, func_type fun) : obj(&object), sil(silent), func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~UnarySilent() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg   The first argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg arg) { return (obj->*func)(sil, arg); }
        };

        //-----------------------------------------------------------------------
        //! Define the binary callback base functor
        template <typename _arg1, typename _arg2, typename _return = void>
        struct BinaryBase : public std::binary_function<_arg1, _arg2, _return>
        {
            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~BinaryBase() {}

            /********************************************//**
             * \brief Call the function pointer
             *
             * \param arg1  The first argument.
             * \param arg2  The second argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg1 arg1, _arg2 arg2) = 0;
        };

        //-----------------------------------------------------------------------
        //! Define a binary callback functor
        template <typename _arg1, typename _arg2, typename _return = void>
        struct Binary : public BinaryBase<_arg1, _arg2, _return>
        {
            // Define the function pointer
            typedef _return (*func_type)(_arg1, _arg2);

            // Pointer
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param fun   Function to point to.
             *
             ***********************************************/
            inline Binary(func_type fun) : func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Binary() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg1  The first argument.
             * \param arg2  The second argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg1 arg1, _arg2 arg2) { return (*func)(arg1, arg2); }
        };

        //-----------------------------------------------------------------------
        //! Define a binary member callback functor
        template <typename _class, typename _arg1, typename _arg2, typename _return = void>
        struct BinaryMember : public BinaryBase<_arg1, _arg2, _return>
        {
            // Define the function pointer
            typedef _return (_class::*func_type)(_arg1, _arg2);

            // Pointer
            _class *obj;
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param object    Class object to point to.
             * \param fun       Member function to point to.
             *
             ***********************************************/
            inline BinaryMember(_class &object, func_type fun) : obj(&object), func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~BinaryMember() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg1  The first argument.
             * \param arg2  The second argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg1 arg1, _arg2 arg2) { return (obj->*func)(arg1, arg2); }
        };

        //-----------------------------------------------------------------------
        //! Define a binary member callback functor to take a silent argument
        template <typename _class, typename _silent, typename _arg1, typename _arg2, typename _return = void>
        struct BinarySilent : public BinaryBase<_arg1, _arg2, _return>
        {
            // Define the function pointer
            typedef _return (_class::*func_type)(_silent, _arg1, _arg2);

            // Pointer
            _class *obj;
            _silent sil;
            const func_type func;

            /********************************************//**
             * \brief Constructor
             *
             * \param object    Class object to point to.
             * \param silent    Silent object to pass to the function.
             * \param fun       Member function to point to.
             *
             ***********************************************/
            inline BinarySilent(_class &object, _silent silent, func_type fun) : obj(&object), sil(silent), func(fun) {}

            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~BinarySilent() {}

            /********************************************//**
             * \brief Calls the callback function
             *
             * \param arg1  The first argument.
             * \param arg2  The second argument.
             * \return The return value of the function.
             *
             ***********************************************/
            virtual _return operator()(_arg1 arg1, _arg2 arg2) { return (obj->*func)(sil, arg1, arg2); }
        };
    }
}

#endif

/*********************************************************
 * CWorx Engine    :    Graphics Engine produced by Ckef Worx
 * www             :    http://www.ckef-worx.com

 Console : The singleton class to handle the window, input,
 Hardware and all other global management tasks.

 * Copyright (c) Stef Velzel :: All Rights Reserved
 *********************************************************/

#ifndef __CWORX_CONSOLE_H__
#define __CWORX_CONSOLE_H__

#include "CWorxEnginePrerequisites.h"

// CWE (CWorx Engine) namespace
namespace CWE
{
    // Hardware namespace
    namespace Hardware
    {
        //! Hardware errors, managed by the console
        class CWE_DLL HardwareError
        {
            //-----------------------------------------------------------------------
            public:
                // Define possible generic errors
                enum GenericError
                {
                    NO_ERROR                            = GL_NO_ERROR, // Guaranteed to not be stored in the console

                    INVALID_ENUM                        = GL_INVALID_ENUM,
                    INVALID_VALUE                       = GL_INVALID_VALUE,
                    INVALID_OPERATION                   = GL_INVALID_OPERATION,
                    INVALID_RENDER_TARGET_OPERATION     = GL_INVALID_FRAMEBUFFER_OPERATION,
                    OUT_OF_MEMORY                       = GL_OUT_OF_MEMORY,
                    STACK_OVERFLOW                      = GL_STACK_OVERFLOW,
                    STACK_UNDERFLOW                     = GL_STACK_UNDERFLOW
                };

                //-----------------------------------------------------------------------
                // Define possible render target errors
                enum RenderTargetError
                {
                    RENDER_TARGET_NO_ERROR              = GL_FRAMEBUFFER_COMPLETE, // Guaranteed to not be stored in the console

                    RENDER_TARGET_INCOMPLETE_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
                    RENDER_TARGET_MISSING_ATTACHMENT    = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
                    RENDER_TARGET_MISSING_WRITE_BUFFER  = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
                    RENDER_TARGET_MISSING_READ_BUFFER   = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
                    RENDER_TARGET_FORMAT_UNSUPPORTED    = GL_FRAMEBUFFER_UNSUPPORTED,
                    RENDER_TARGET_INVALID_MULTISAMPLE   = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
                    RENDER_TARGET_INVALID_LAYER         = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
                };

                //-----------------------------------------------------------------------
                // Define possible 'silent' GL 'errors'
                enum SilentError
                {
                    SILENT_NO_ERROR,

                    SILENT_FAILED_CONSOLE_OPERATION,
                    SILENT_LINK_FAILURE,
                    SILENT_COMPILE_FAILURE
                };

                //-----------------------------------------------------------------------
                // Define error types
                enum Type
                {
                    TYPE_GENERIC,
                    TYPE_RENDER_TARGET_WRITE,
                    TYPE_RENDER_TARGET_READ,
                    TYPE_SILENT // Silent as in, OpenGL doesn't flag it as an error
                };

                // Define storage for an error
                union Error
                {
                    GenericError        generic;
                    RenderTargetError   renderTarget;
                    SilentError         silent;
                };

                //-----------------------------------------------------------------------
                // Given Properties
                const Type type;
                const std::string info;

                // Generated Error
                Error error;

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param type  Type of the error to check for (silent will be ignored, use other constructor!).
                 * \param info  Message to give information about where the error occured.
                 *
                 * Checks for any errors of the given type and adds a copy of itself to the console if any error was found.
                 * If the type concerns the render target, the internal framebuffer should first be bound before constructing an error.
                 *
                 ***********************************************/
                HardwareError(const Type &type, const std::string &info);

                /********************************************//**
                 * \brief Constructor
                 *
                 * \param err   The silent error to construct.
                 * \param info  Message to give information about where the error occured.
                 *
                 * Constructs a silent error, the error must be given in this case.
                 *
                 ***********************************************/
                HardwareError(const SilentError &err, const std::string &info);

                /********************************************//**
                 * \brief Copy Constructor
                 ***********************************************/
                HardwareError(const HardwareError &err);

                /********************************************//**
                 * \brief Prints the error through the console
                 *
                 * \return void
                 *
                 ***********************************************/
                void print() const;

                /********************************************//**
                 * \brief Fetch whether it found any error or not
                 *
                 * \return Whether it found any error or not.
                 *
                 ***********************************************/
                bool isError() const;
        };

        //! Hardware objects managed by the console
        class HardwareBase
        {
            //-----------------------------------------------------------------------
            protected:
                // GL Object
                GLuint _GL_Object;

            //-----------------------------------------------------------------------
            public:
                /********************************************//**
                 * \brief Constructor
                 *
                 * Adds itself to the console.
                 *
                 ***********************************************/
                HardwareBase();

                /********************************************//**
                 * \brief Destructor
                 *
                 * Removes itself from the console.
                 *
                 ***********************************************/
                virtual ~HardwareBase();

                /********************************************//**
                 * \brief Checks for any errors
                 *
                 * \param type  Type of the error to look for.
                 * \param info  Message to give information about where the error occured.
                 * \return Whether any generic error was found or not.
                 *
                 ***********************************************/
                bool getError(const HardwareError::Type &type, const std::string &info) const;

                /********************************************//**
                 * \brief Constructs a silent error
                 *
                 * \param err   The silent error to construct.
                 * \param info  Message to give information about where the error occured.
                 * \return Whether the error turned out to be an actual error or not.
                 *
                 ***********************************************/
                bool getError(const HardwareError::SilentError &err, const std::string &info) const;

                //-----------------------------------------------------------------------
                // Compare by GL index

                inline bool operator==(const HardwareBase &hw) const { return _GL_Object == hw._GL_Object; }
                inline bool operator!=(const HardwareBase &hw) const { return _GL_Object != hw._GL_Object; }
                inline bool operator<=(const HardwareBase &hw) const { return _GL_Object <= hw._GL_Object; }
                inline bool operator>=(const HardwareBase &hw) const { return _GL_Object >= hw._GL_Object; }
                inline bool operator<(const HardwareBase &hw) const { return _GL_Object < hw._GL_Object; }
                inline bool operator>(const HardwareBase &hw) const { return _GL_Object > hw._GL_Object; }

                inline bool operator==(GLuint i) const { return _GL_Object == i; }
                inline bool operator!=(GLuint i) const { return _GL_Object != i; }
                inline bool operator<=(GLuint i) const { return _GL_Object <= i; }
                inline bool operator>=(GLuint i) const { return _GL_Object >= i; }
                inline bool operator<(GLuint i) const { return _GL_Object < i; }
                inline bool operator>(GLuint i) const { return _GL_Object > i; }
        };
    }

    //! Main hub to store all engine properties
    class CWE_DLL Console
    {
        //-----------------------------------------------------------------------
        private:
            // Singleton
            static Console *_singleton;     // Console
            static FT_Library _freetype;    // Freetype

            Console();                      // Private constructor
            Console(const Console&);        // Private copy constructor
            void operator=(const Console&); // Private assignment

            //-----------------------------------------------------------------------
            // GLFW Callbacks
            static void keyCallback        (int key, int pressed);
            static void mousePosCallback   (int x, int y);
            static void mouseKeyCallback   (int key, int pressed);
            static void mouseWheelCallback (int pos);
            static void resizeCallback     (int width, int height);

            // User Callbacks
            Callback::UnaryBase<Key::Key>       *_callbackKeyPress;
            Callback::UnaryBase<Key::Key>       *_callbackKeyRelease;
            Callback::BinaryBase<int, int>      *_callbackMousePos;
            Callback::UnaryBase<Key::MouseKey>  *_callbackMousePress;
            Callback::UnaryBase<Key::MouseKey>  *_callbackMouseRelease;
            Callback::UnaryBase<int>            *_callbackMouseWheel;
            Callback::BinaryBase<int, int>      *_callbackResize;

            //-----------------------------------------------------------------------
            // Engine Properties
            OpenGL::OpenGL _gl;
            bool _cursor;
            double _frameCap;
            double _frameTime;

            //-----------------------------------------------------------------------
            // Active Render Targets
            Geometry::Viewport *_viewport;
            Scene *_scene;

            // Render Target Properties
            Math::vec2ui _maxBufferSize; // (0,0) = no maximum
            Math::vec2f _bufferScale;    // For Anti Aliasing or similar

            // Returns the viewport size according to the maximum size and scale
            Math::vec2ui getViewportSize(const Math::vec2ui &_size) const;

            //-----------------------------------------------------------------------
            // Define a list of hardware objects
            typedef std::set<Hardware::HardwareBase*> HardwareList;

            // Define a queue of hardware errors
            typedef std::queue<Hardware::HardwareError> HardwareErrorQueue;

            // Storage
            HardwareList _hardware;
            HardwareErrorQueue _hardwareErrors;

            // Storage Properties
            unsigned short _maxErrors;

        //-----------------------------------------------------------------------
        public:
            /********************************************//**
             * \brief Destructor
             ***********************************************/
            virtual ~Console();

            /********************************************//**
             * \brief Fetch the singleton instance
             *
             * \return A handle to the singleton instance.
             *
             ***********************************************/
            static Console &GET();

            /********************************************//**
             * \brief Fetch the freetype instance
             *
             * \return A handle to the singleton FreeType instance.
             *
             ***********************************************/
            static FT_Library &FT();

            /********************************************//**
             * \brief Adds hardware to the memory list
             *
             * \param hardware  The hardware to add.
             * \return void
             *
             ***********************************************/
            void addHardware(Hardware::HardwareBase *hardware);

            /********************************************//**
             * \brief Removes hardware from the memory list
             *
             * \param hardware  The hardware to remove.
             * \return void
             *
             ***********************************************/
            void removeHardware(Hardware::HardwareBase *hardware);

            /********************************************//**
             * \brief Fetch the amount of hardware managed by the console
             *
             * \return Amount of hardware managed by the console.
             *
             ***********************************************/
            unsigned int getNumHardware() const;

            /********************************************//**
             * \brief Pushes a hardware error on top of the error queue
             *
             * \param err   The hardware error to push.
             * \return void
             *
             ***********************************************/
            void pushError(const Hardware::HardwareError &err);

            /********************************************//**
             * \brief Views the hardware error at the bottom of the error queue
             *
             * \return The oldest hardware error stored (0 if none stored).
             *
             ***********************************************/
            const Hardware::HardwareError *viewError() const;

            /********************************************//**
             * \brief Pops a hardware error from the bottom of the error queue
             *
             * \return False if no hardware errors are stored.
             *
             ***********************************************/
            bool popError();

            /********************************************//**
             * \brief Fetch the number of hardware errors stored
             *
             * \return Number of hardware errors stored in the console.
             *
             ***********************************************/
            unsigned int getNumErrors() const;

            /********************************************//**
             * \brief Set the maximum number of hardware errors stored
             *
             * \param max   Maximum numer of hardware errors stored at one time.
             * \return void
             *
             ***********************************************/
            void setMaxErrors(unsigned int max);

            /********************************************//**
             * \brief Fetch the maximum number of hardware errors stored
             *
             * \return Maximum numer of hardware errors stored in the console.
             *
             ***********************************************/
            unsigned int getMaxErrors() const;

            /********************************************//**
             * \brief Fetch whether a OpenGL Context to render to is open
             *
             * \return Whether a OpenGL Context is open or not.
             *
             ***********************************************/
            bool isOpen() const;

            /********************************************//**
             * \brief Sets the requested OpenGL version
             *
             * \param version   The enumerator describing major and minor version.
             * \return void
             *
             ***********************************************/
            void setOpenGL(const OpenGL::OpenGL &version);

            /********************************************//**
             * \brief Fetch the OpenGL version
             *
             * \return The OpenGL version.
             *
             * If the window is open, it will fetch the active OpenGL version.
             * If the window is closed, it will fetch the requested OpenGL version.
             *
             ***********************************************/
            const OpenGL::OpenGL &getOpenGL() const;

            /********************************************//**
             * \brief Opens a OpenGL Context with a certain width and height and a title
             *
             * \param width         The width of the OpenGL context.
             * \param height        The height of the OpenGL context.
             * \param title            The title of the window.
             * \param vsync         If true, vertical synchronization will be enabled.
             * \param resizeable    Whether the user can resize the window (no effect in fullscreen).
             * \return Whether the window was successfully opened or not.
             *
             ***********************************************/
            bool openWindow(unsigned int width, unsigned int height, const std::string &title, bool vsync = false, bool resizeable = true);

            /********************************************//**
             * \brief Closes the OpenGL Context
             *
             * \return void
             *
             ***********************************************/
            void closeWindow();

            /********************************************//**
             * \brief Sets the title of the screen
             *
             * \param title New title of the window.
             * \return void
             *
             ***********************************************/
            void setTitle(const std::string &title);

            /********************************************//**
             * \brief Resizes the resolution
             *
             * \param vec   new width and height of the screen.
             * \return void
             *
             ***********************************************/
            void resize(const Math::vec2ui &vec);

            /********************************************//**
             * \brief Resizes the resolution
             *
             * \param width     New width of the screen.
             * \param height    New height of the screen.
             * \return void
             *
             ***********************************************/
            void resize(unsigned int width, unsigned int height);

            /********************************************//**
             * \brief Fetch both the screen width and height
             *
             * \return The size of the window.
             *
             ***********************************************/
            Math::vec2ui getSize() const;

            /********************************************//**
             * \brief Repositions the window
             *
             * \param vec   X and Y coordinates as vector.
             * \return void
             *
             ***********************************************/
            void position(const Math::vec2i &vec);

            /********************************************//**
             * \brief Repositions the window
             *
             * \param x X coordinate.
             * \param y Y coordinate.
             * \return void
             *
             ***********************************************/
            void position(int x, int y);

            /********************************************//**
             * \brief Sets the maximum frame rate to run at
             *
             * \param cap   The maximum Frames Per Second (FPS).
             * \return void
             *
             * Sets the maximum frame rate to run it, a cap of 0 means no limit.
             *
             ***********************************************/
            void setFramerateCap(unsigned int cap);

            /********************************************//**
             * \brief Fetch the last frame rate (FPS)
             *
             * \return The framerate.
             *
             ***********************************************/
            double getFramerate() const;

            /********************************************//**
             * \brief Fetch the last frame time (seconds)
             *
             * \return The frametime.
             *
             ***********************************************/
            double getFrametime() const;

            /********************************************//**
             * \brief Executes all processes of rendering a final image to the screen
             *
             * \return Whether the engine is still 'running'.
             *
             ***********************************************/
            bool render();

            /********************************************//**
             * \brief Fetch the 'screen' viewport
             *
             * \return The viewport of the console.
             *
             ***********************************************/
            const Geometry::Viewport *getViewport() const;

            /********************************************//**
             * \brief Sets the maximum buffer size for the viewport
             *
             * \param size  The maximum size of the internal buffers.
             * \return void
             *
             * Sets the maximum buffer size for the viewport, a component of 0 means no limit.
             *
             ***********************************************/
            void setMaxBufferSize(const Math::vec2ui &size);

            /********************************************//**
             * \brief Sets the maximum buffer size for the viewport
             *
             * \param x The X component of the size.
             * \param y The Y component of the size.
             * \return void
             *
             * Sets the maximum buffer size for the viewport, a component of 0 means no limit.
             *
             ***********************************************/
            void setMaxBufferSize(unsigned int x, unsigned int y);


            /********************************************//**
             * \brief Fetch the maximum buffer size for the viewport
             *
             * \return The maximum buffer size.
             *
             ***********************************************/
            const Math::vec2ui &getMaxBufferSize() const;

            /********************************************//**
             * \brief Sets the buffer scale for the viewport
             *
             * \param scale The scale of the internal buffers.
             * \return void
             *
             ***********************************************/
            void setBufferScale(const Math::vec2f &scale);

            /********************************************//**
             * \brief Sets the buffer scale for the viewport
             *
             * \param x The X component of the scale.
             * \param y The Y component of the scale.
             * \return void
             *
             ***********************************************/
            void setBufferScale(float x, float y);

            /********************************************//**
             * \brief Fetch the buffer scale for the viewport
             *
             * \return The buffer scale.
             *
             ***********************************************/
            const Math::vec2f &getBufferScale() const;

            /********************************************//**
             * \brief Sets the active scene
             *
             * \return void
             *
             * Sets the active scene, the internal viewport of the scene will be lost!
             *
             ***********************************************/
            void setScene(Scene *scene);

            /********************************************//**
             * \brief Fetch the active scene
             *
             * \return The active scene.
             *
             ***********************************************/
            Scene *getScene() const;

            /********************************************//**
             * \brief Fetch the mouse position
             *
             * \return The mouse position.
             *
             ***********************************************/
            Math::vec2i getMousePosition() const;

            /********************************************//**
             * \brief Sets the mouse position
             *
             * \param vec   The x and y coordinates relative to the window.
             * \return void
             *
             ***********************************************/
            void setMousePosition(const Math::vec2i &vec);

            /********************************************//**
             * \brief Sets the mouse position
             *
             * \param x The x coordinate relative to the window.
             * \param y The y coordinate relative to the window.
             * \return void
             *
             ***********************************************/
            void setMousePosition(int x, int y);

            /********************************************//**
             * \brief Sets the mouse cursor to be enabled or not
             *
             * \param enable    Whether to enable the cursor or not.
             * \return void
             *
             ***********************************************/
            void setCursorEnabled(bool enable);

            /********************************************//**
             * \brief Toggles the mouse cursor between enabled and disabled
             *
             * \return Whether the cursor is now enabled or not.
             *
             ***********************************************/
            bool toggleCursorEnabled();

            /********************************************//**
             * \brief Fetch whether the mouse is enabled
             *
             * \return Whether the cursor is enabled or not.
             *
             ***********************************************/
            bool isCursorEnabled() const;

            /********************************************//**
             * \brief Fetch the postion of the mouse wheel
             *
             * \return the position of the mouse wheel.
             *
             ***********************************************/
            int getMouseWheel() const;

            /********************************************//**
             * \brief Returns whether a certain key is pressed
             *
             * \param key   The key to check for.
             * \return void
             *
             ***********************************************/
            bool isKeyPressed(const Key::Key &key) const;

            /********************************************//**
             * \brief Returns whether a certain mouse key is pressed
             *
             * \param key   The key to check for.
             * \return void
             *
             ***********************************************/
            bool isMousePressed(const Key::MouseKey &key) const;

            //-----------------------------------------------------------------------
            // Key press callback
            template <typename _func> inline void setKeyPressCallback(_func func)
                { delete _callbackKeyPress; _callbackKeyPress = new Callback::Unary<Key::Key>(func); }

            // Key press member callback
            template <typename _class, typename _func> inline void setKeyPressCallback(_class &cl, _func func)
                { delete _callbackKeyPress; _callbackKeyPress = new Callback::UnaryMember<_class, Key::Key>(cl, func); }

            //-----------------------------------------------------------------------
            // Key release callback
            template <typename _func> inline void setKeyReleaseCallback(_func func)
                { delete _callbackKeyRelease; _callbackKeyRelease = new Callback::Unary<Key::Key>(func); }

            // Key release member callback
            template <typename _class, typename _func> inline void setKeyReleaseCallback(_class &cl, _func func)
                { delete _callbackKeyRelease; _callbackKeyRelease = new Callback::UnaryMember<_class, Key::Key>(cl, func); }

            //-----------------------------------------------------------------------
            // Mouse move callback
            template <typename _func> inline void setMouseMoveCallback(_func func)
                { delete _callbackMousePos; _callbackMousePos = new Callback::Binary<int, int>(func); }

            // Mouse move member callback
            template <typename _class, typename _func> inline void setMouseMoveCallback(_class &cl, _func func)
                { delete _callbackMousePos; _callbackMousePos = new Callback::BinaryMember<_class, int, int>(cl, func); }

            //-----------------------------------------------------------------------
            // Mouse press callback
            template <typename _func> inline void setMousePressCallback(_func func)
                { delete _callbackMousePress; _callbackMousePress = new Callback::Unary<Key::MouseKey>(func); }

            // Mouse press member callback
            template <typename _class, typename _func> inline void setMousePressCallback(_class &cl, _func func)
                { delete _callbackMousePress; _callbackMousePress = new Callback::UnaryMember<_class, Key::MouseKey>(cl, func); }

            //-----------------------------------------------------------------------
            // Mouse release callback
            template <typename _func> inline void setMouseReleaseCallback(_func func)
                { delete _callbackMouseRelease; _callbackMouseRelease = new Callback::Unary<Key::MouseKey>(func); }

            // Mouse release member callback
            template <typename _class, typename _func> inline void setMouseReleaseCallback(_class &cl, _func func)
                { delete _callbackMouseRelease; _callbackMouseRelease = new Callback::UnaryMember<_class, Key::MouseKey>(cl, func); }

            //-----------------------------------------------------------------------
            // Mouse wheel callback
            template <typename _func> inline void setMouseWheelCallback(_func func)
                { delete _callbackMouseWheel; _callbackMouseWheel = new Callback::Unary<int>(func); }

            // Mouse wheel member callback
            template <typename _class, typename _func> inline void setMouseWheelCallback(_class &cl, _func func)
                { delete _callbackMouseWheel; _callbackMouseWheel = new Callback::UnaryMember<_class, int>(cl, func); }

            //-----------------------------------------------------------------------
            // Resize callback
            template <typename _func> inline void setResizeCallback(_func func)
                { delete _callbackResize; _callbackResize = new Callback::Binary<int, int>(func); }

            // Resize member callback
            template <typename _class, typename _func> inline void setResizeCallback(_class &cl, _func func)
                { delete _callbackResize; _callbackResize = new Callback::BinaryMember<_class, int, int>(cl, func); }

            //-----------------------------------------------------------------------
            // 'Stream' input
            template <typename _type>
            inline Console &operator<<(const _type &val)
                { std::cout << val; return *this; }
    };
}

#endif

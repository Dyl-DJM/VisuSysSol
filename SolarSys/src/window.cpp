/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Window management module.                         =
=  													 =
======================================================
*/

#include "include/window.hpp"

/**
 * @brief Displays the error that occured on the window.
 *
 * @param code Code error.
 * @param desc A description of the error.
 ********************************************************************************/
void Window::onError(int code, const char *desc)
{
    std::cerr << "Code : " << code << std::endl
              << desc << std::endl;
}

/**
 * @brief Initializes the library for the window management.
 *
 * @warning This must be called before the creation of the window
 *
 * @return A code error telling if the initialization is successfull or not.
 ********************************************************************************/
int Window::initWindowLib()
{

    if (!glfwInit())
    {
        return ERR_INT_CODE;
    }
    return SUCCESS_INT_CODE;
}

/**
 * @brief Frees properly the current window.
 ********************************************************************************/
void Window::freeCurrentWindow()
{
    glfwMakeContextCurrent(NULL); // Deletion of the context in the current window
    glfwSetKeyCallback(_window, nullptr);
    glfwSetErrorCallback(nullptr);

    // Destruction of the window
    glfwDestroyWindow(_window);
    _window = NULL; // Allows identification of a window that has been deleted
}

/**
 * @brief Checks if a window is still active/opened.
 *
 * @return A boolean, true if window is still open and false otherwise.
 ********************************************************************************/
bool Window::isWindowOpen()
{
    if (glfwWindowShouldClose(_window)) // Close flag is true
    {
        return false;
    }
    return true;
}

/**
 * @brief Make a window being active.
 *
 * This means that, its allows the window to react with the possible events by the
 * user on the window for example.
 ********************************************************************************/
void Window::manageWindow()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(_window);

    // Check the possible events that occured
    glfwPollEvents();
}

/**
 * @brief Creates a window.
 *
 * @param width Width dimension of the window.
 * @param height Height dimension of the window.
 * @param title A char array that represents the title of the window.
 ********************************************************************************/
Window::Window(unsigned int width, unsigned int height, const char *title)
{

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // Useful to get errors in the window management
    // glfwSetErrorCallback(onError);

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Couldn't be created properly
    if (!_window)
    {
        std::cout << "0" << std::endl;
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return;
    }

    _state = true;
}

/**
 * @brief Sets the events for the window.
 ********************************************************************************/
void Window::configureEvents(Context &context)
{
    Events::setEvents(_window, context);
}

/**
 * @brief Gives the creation state of the window.
 ********************************************************************************/
int Window::isCreated()
{
    return _state;
}

/**
 * @brief Destructor of the class.
 ********************************************************************************/
Window::~Window()
{
    if (_window != NULL) // Need to be sure the _window hasn't been deleted yet
    {
        glfwDestroyWindow(_window);
        _window = NULL;
    }
}

/**
 * @brief Ends the window library.
 *
 * Terminates the GLFW library.
 ********************************************************************************/
void Window::endWindowLib()
{
    glfwTerminate();
}
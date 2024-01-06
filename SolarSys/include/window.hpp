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

#pragma once

#define GLFW_INCLUDE_NONE

#include <string>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "include/tools.hpp"
#include "include/events.hpp"

/**
 * @brief Representation of a window where we can render the 3D scene.
 *
 * This one is using GLFW library.
 ********************************************************************************/
class Window
{

public:
    /**
     * @brief Creates a window.
     *
     * @param width Width dimension of the window.
     * @param height Height dimension of the window.
     * @param title The title of the window.
     *
     * @return The window created or a null pointer if an error occured.
     ********************************************************************************/
    Window(unsigned int width, unsigned int height, const char *title);

    /**
     * @brief Initializes the library for the window management.
     *
     * @warning This must be called before the creation of the window
     *
     * @return 1 if the initialization is successfull, else 0.
     ********************************************************************************/
    static int initWindowLib();

    /**
     * @brief Frees properly the current window.
     ********************************************************************************/
    /*static*/ void freeCurrentWindow();

    /**
     * @brief Make a window active.
     *
     * Allows the window to react to the possible events.
     *
     * @param window A window.
     ********************************************************************************/
    void manageWindow();

    /**
     * @brief Checks if a window is still active/opened.
     *
     * @return A boolean, true if window is still open, false otherwise.
     ********************************************************************************/
    bool isWindowOpen();

    /**
     * @brief Sets the events for the window.
     ********************************************************************************/
    void configureEvents(Context &context);

    /**
     * @brief Gives the creation state of the window.
     ********************************************************************************/
    int isCreated();

    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    ~Window();

    /**
     * @brief Closes the window library.
     *
     * Closes the GLFW library.
     ********************************************************************************/
    static void endWindowLib();

private:
    /**
     * @brief Displays the error that occured on the window.
     *
     * @param code Error code.
     * @param desc Description of the error.
     ********************************************************************************/
    static void onError(int code, const char *desc);

    GLFWwindow *_window = NULL; // Pointer on a GLFW window
    bool _state = false;        // true if the window is open, false otherwise
};
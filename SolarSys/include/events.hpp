/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Module where we can find the system of events.    =
=													 =
=  Contains implementations of the interactions      =
=  with the window using the keys, the keyboard,     =
=  the mouse or window events (resize..)      		 =
======================================================
*/

#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <iostream>
#include "../include/camera.hpp"

/**
 * @brief Contains all the methods to interact with the window.
 *
 * Sets all the behaviours the app must have for each event made by the user
 * thanks to callback system user with the GLFW library.
 * It handles :
 *
 *      -> Mouse motion
 *      -> Mouse buttons
 *      -> Window resize
 *      -> Pression on the keyboard
 ********************************************************************************/
class Events
{

public:
    /**
     * @brief Sets all the events the user is allowed to interact with.
     *
     * Sets all the kind of interactions the user is allowed to have with its window
     * for instance the ones with the keys, its mouse... Moreover the behaviour of
     * the app binded to each interaction are also configured there
     *
     * @param window A window to bind the events with.
     ********************************************************************************/
    static void setEvents(GLFWwindow *window);

    /**
     * @brief Recover the view matrix of the Camera
    */
    static glm::mat4 getViewMatrix();

private:

    static Camera camera;  // Camera object
    static bool mouse_right_press;  // Boolean describing wether the right mouse is pressed or not
    static double mouse_x;
    static double mouse_y;


    /**
     * @brief Callback function for the keys on the keyboard.
     *
     * It fits the wanted template of the GLFW description.
     *
     * @param window A window.
     * @param key Key id.
     * @param scancode Code of the key.
     * @param action Kind of action (Pressed/Released).
     ********************************************************************************/
    static void onKey(GLFWwindow *window, int key, int scancode, int action, int mods);

    /**
     * @brief Callback function for the mouse buttons.
     *
     * It fits the wanted template of the GLFW description.
     *
     * @param window A window.
     * @param code Code of the button.
     * @param action Kind of action (Pressed/Released).
     * @param other Other information.
     ********************************************************************************/
    static void onMouseButton(GLFWwindow *window, int code, int action, int other);

    /**
     * @brief Callback function for the motion of the mouse on the window.
     *
     * It fits the wanted template of the GLFW description.
     *
     * @param window A window.
     * @param x Position of the mouse on x axis.
     * @param y  Position of the mouse on y axis.
     ********************************************************************************/
    static void onMouseMotion(GLFWwindow *window, double x, double y);


    /**
     * @brief Callback function for mouse scroll.
     *
     * It fits the wanted template of the GLFW description.
     *
     * @param window A window.
     * @param xoffset 
     * @param yoffset
     ********************************************************************************/
    static void onScroll(GLFWwindow* window, double xoffset, double yoffset);

    /**
     * @brief Callback function for the resize event.
     *
     * It fits the wanted template of the GLFW description.
     *
     * @param window A window.
     * @param width Width dimension. Contains the new width of the window.
     * @param height Height dimension. Contains the new height of the window.
     ********************************************************************************/
    static void onWindowResized(GLFWwindow *window, int width, int height);
};

// Initialization of the static Camera
inline Camera Events::camera = Camera();

inline bool Events::mouse_right_press = false;

inline double Events::mouse_x = 0.0f;

inline double Events::mouse_y = 0.0f;
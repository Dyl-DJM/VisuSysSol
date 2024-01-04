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

#include "include/events.hpp"

/**
 * @brief Callback function for the resize event.
 *
 * It fits the wanted template of the GLFW description.
 *
 * @param window A window.
 * @param width Width dimension. Contains the new width of the window.
 * @param height Height dimension. Contains the new height of the window.
 ********************************************************************************/
void Events::onWindowResized(GLFWwindow *window, int width, int height)
{
    std::cout << "RESIZE : " << window << " for dimension " << width << " x " << height << std::endl;
}

/**
 * @brief Callback function for the motion of the mouse on the window.
 *
 * It fits the wanted template of the GLFW description.
 *
 * @param window A window.
 * @param x Position of the mouse on x axis.
 * @param y  Position of the mouse on y axis.
 ********************************************************************************/
void Events::onMouseMotion(GLFWwindow *window, double x, double y)
{
    std::cout << "Mouse Motion : " << window << " for mouse position " << x << " , " << y << std::endl;

    if (mouse_right_press)
    { // Camera rotation

        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));

        Camera &camera = context->getCamera();

        camera.rotateLeft(mouse_x - x);
        camera.rotateUp(mouse_y - y);

        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }
}

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
void Events::onMouseButton(GLFWwindow *window, int code, int action, int other)
{
    std::cout << "Mouse Button : " << window << " of code " << code << " fo action "
              << action << " and other : " << other << std::endl;

    if (code == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        mouse_right_press = true;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }
    else if (code == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        mouse_right_press = false;
    }
}

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
void Events::onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    std::cout << "Key Event : " << window << " for key " << key << " of scancode " << scancode
              << ". Made the action : " << action << " and mods are " << mods << std::endl;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE); // Sets the close flag of the window at true
    }

    /**************** Camera Management ****************/

    // Go to the next planet focused pov
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        context->previous_planet();
    }
    // Go to the previous planet focused pov
    else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        context->next_planet();
    }
    // Go to the initial pov
    else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        context->resetCam();
    }

    /**************** Speed Management ****************/

    else if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        context->increaseSpeed(2);
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        context->decreaseSpeed(2);
    }
}

void Events::onScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    std::cout << "Key Event : " << window << "\nxoffset: " << xoffset << "\nyoffset: " << yoffset << std::endl;

    Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));

    Camera &camera = context->getCamera();

    if (yoffset == -1)
    { // Dezooming
        camera.moveFront(0.1);
    }
    else if (yoffset == 1)
    { // Zooming
        camera.moveFront(-0.1);
    }
}

/**
 * @brief Sets all the events the user is allowed to interact with.
 *
 * Sets all the kind of interactions the user is allowed to have with its window
 * for instance the ones with the keys, its mouse... Moreover the behaviour of
 * the app binded to each interaction are also configured there
 *
 * @param window A window to bind the events with.
 ********************************************************************************/
void Events::setEvents(GLFWwindow *window, Context &context)
{
    glfwSetWindowSizeCallback(window, Events::onWindowResized);
    glfwSetCursorPosCallback(window, Events::onMouseMotion);   /* Mouse moved */
    glfwSetMouseButtonCallback(window, Events::onMouseButton); /* Mouse click */
    glfwSetKeyCallback(window, Events::onKey);                 /* Key events */
    glfwSetScrollCallback(window, Events::onScroll);

    glfwSetWindowUserPointer(window, &context); /* Set the context */

    std::cout << window << std::endl;
}

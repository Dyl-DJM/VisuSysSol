/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Module defining a Context class used to store     =
=  data that will be used / modified in callback     =
=  functions.                                        =
=													 =
======================================================
*/

#pragma once

#define GLFW_INCLUDE_NONE

#include "../include/camera.hpp"
#include "../include/light.hpp"
#include "../include/solarSystem.hpp"

class Context
{

public:
    /**
     * @brief constructor.
     * @param cam The camera associated to the program
     * @param solarSystem The SolarSystem object associated to the program
     */
    Context(Camera &cam, SolarSystem &solarSystem, Light &light);

    /**
     * Camera accessor.
     * @return the camera
     */
    Camera &getCamera();

    /**
     * @brief SolarSystem accessor.
     * @return the SolarSystem object stored in the Context
     */
    SolarSystem &getSolarSys();

    /**
     * Update the camera's position with the selected planet's position.
     */
    void update_camera();

    /**
     * @brief Select the next planet.
     */
    void next_planet();

    /**
     * @brief Select the previous planet.
     */
    void previous_planet();

    /**
     * @brief Accessor for the speed multiplier
     */
    float getSpeedMultiplier();

    /**
     * @brief Increase the speed multiplier by the given value. Maximum multiplier is capped at 25.
     * @param value value by which to increase the speed multiplier
     */
    void increaseSpeed(float value);

    /**
     * @brief Decrease the speed multiplier by the given value. Speed multiplier can't go lower than 1
     * @param value value by which to decrease the speed multiplier
     */
    void decreaseSpeed(float value);

    /**
     * @brief Creates a time leap linked to the context.
     *
     * @param value The float value of the time leap (in seconds).
     ********************************************************************************/
    void timeLeap(float value);
    /**
     * @brief Consumes the current time leap.
     *
     * Returns the current value of the time leap, if no one was created before
     * the value returned is 0.
     *
     * Then the time leap is restored to 0.
     *
     * @param The float value of the time leap (in seconds).
     ********************************************************************************/
    float consumeTimeLeap();

    /**
     * @brief Returns to the initial configuration of the camera.
     *
     * The camera will return its first position, view angle...
     ********************************************************************************/
    void resetCam();

    /**
     * @brief Tells if the cam is on the focused mode or not.
     *
     * @return True if the camera is set on the focused mode and false otherwise.
     ********************************************************************************/
    bool isCamFocused();

    /**
     * @brief Tells if the cam is on the initial mode or not.
     *
     * @return True if the camera is set on the initial mode and false otherwise.
     ********************************************************************************/
    bool isInitalCam();

    /**
     * @brief Sets the profile point of view for the camera.
     ********************************************************************************/
    void profileCam();

    /**
     * @brief Tells if the cam is on the profile mode or not.
     *
     * @return True if the camera is set on the profile mode and false otherwise.
     ********************************************************************************/
    bool isProfileCam();

    /**
     * @brief Accessor for the light
     */
    Light &getLight();

private:
    Camera &camera;
    SolarSystem &solarSys;
    unsigned int planet_idx; // Index of the selected planet in the solar system
    float speedMultiplier;   // Multiplier for the speed at which time elapses in the solar system
    float _tLeap = 0;
    Light &_light;
};
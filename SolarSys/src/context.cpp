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

#include "include/context.hpp"

/**
 * @brief Class constructor.
 * @param cam The camera associated to the program
 * @param solarSystem The SolarSystem object associated to the program
 * @param speedMultiplier Speed multiplier at which time elapses in the solar system
 */
Context::Context(Camera &cam, SolarSystem &solarSystem)
    : camera{cam}, solarSys{solarSystem}, planet_idx{0}, speedMultiplier{1}
{
    update_camera();
    camera.set_distance(solarSys[planet_idx].getSize() * 2);
}

/**
 * @brief Camera accessor.
 * @return the camera
 */
Camera &Context::getCamera()
{
    return camera;
}

/**
 * @brief SolarSystem accessor.
 * @return the SolarSystem object stored in the Context
 */
SolarSystem &Context::getSolarSys()
{
    return solarSys;
}

/**
 * @brief Update the camera's position with the selected planet's position.
 */
void Context::update_camera()
{
    if (camera.isFocusedPov()) // If the camera is in planet focused mode, then the view matrix will be computed thanks to the planet position
    {
        camera.update_position(solarSys[planet_idx].getMatrices().getMVMatrix()[3]);
    }
    else if (camera.isInitialPov()) // We juste restore the initial computations for the view matrix of this point of viex
    {
        camera.initialConfig();
    }
}

/**
 * @brief Select the next planet.
 */
void Context::next_planet()
{
    planet_idx = (planet_idx == solarSys.nbPlanets() - 1) ? 0 : (planet_idx + 1);

    // camera settings
    camera.set_distance(solarSys[planet_idx].getSize() * 2);
    camera.setFocusedPov();
}

/**
 * @brief Select the previous planet.
 */
void Context::previous_planet()
{
    planet_idx = (planet_idx == 0) ? solarSys.nbPlanets() - 1 : (planet_idx - 1);

    // camera settings
    camera.set_distance(solarSys[planet_idx].getSize() * 2);
    camera.setFocusedPov();
}

/**
 * @brief Accessor for the speed multiplier
 */
float Context::getSpeedMultiplier()
{
    return speedMultiplier;
}

/**
 * @brief Increase the speed multiplier by the given value. Maximum multiplier is capped at 25.
 * @param value value by which to increase the speed multiplier
 */
void Context::increaseSpeed(float value)
{
    speedMultiplier = (speedMultiplier + value > 25) ? speedMultiplier : (speedMultiplier + value);
}

/**
 * @brief Decrease the speed multiplier by the given value. Speed multiplier can't go lower than 1
 * @param value value by which to decrease the speed multiplier
 */
void Context::decreaseSpeed(float value)
{
    speedMultiplier = (speedMultiplier - value < 1) ? speedMultiplier : (speedMultiplier - value);
}

/**
 * @brief Returns to the initial configuration of the camera.
 *
 * The camera will return its first position, view angle...
 ********************************************************************************/
void Context::resetCam()
{
    planet_idx = 0;
    camera.setInitialPov();
}
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
Context::Context(Camera &cam, SolarSystem &solarSystem, Light & light)
    : camera{cam}, solarSys{solarSystem}, planet_idx{0}, speedMultiplier{1}, _light {light}
{
    update_camera();
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
    else if (camera.isInitialPov() || camera.isProfilePov()) // We just restore the initial computations(transformations on matrices) for the view matrix for one of these two modes
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
 * @brief Creates a time leap linked to the context.
 *
 * @param value The float value of the time leap (in seconds).
 ********************************************************************************/
void Context::timeLeap(float value)
{
    _tLeap = value;
}

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
float Context::consumeTimeLeap()
{
    auto val = _tLeap;
    _tLeap = 0; // Restores the time leap to 0 when consumed
    return val;
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

/**
 * @brief Returns to the profile point of view for the camera.
 ********************************************************************************/
void Context::profileCam()
{
    camera.setProfilePov();
}

/**
 * @brief Tells if the cam is on the focused mode or not.
 *
 * @return True if the camera is set on the focused mode and false otherwise.
 ********************************************************************************/
bool Context::isCamFocused()
{
    return camera.isFocusedPov();
}

/**
 * @brief Tells if the cam is on the initial mode or not.
 *
 * @return True if the camera is set on the initial mode and false otherwise.
 ********************************************************************************/
bool Context::isInitalCam()
{
    return camera.isInitialPov();
}

/**
 * @brief Tells if the cam is on the profile mode or not.
 *
 * @return True if the camera is set on the profile mode and false otherwise.
 ********************************************************************************/
bool Context::isProfileCam()
{
    return camera.isProfilePov();
}

/**
 * @brief Accessor for the light
*/
Light & Context::getLight(){
    return _light;
}
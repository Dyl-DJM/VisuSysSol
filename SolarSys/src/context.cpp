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
*/
Context::Context(Camera & cam, SolarSystem & solarSystem)
    : camera {cam}
    , solarSys {solarSystem}
    , planet_idx {0}
    {
        update_camera();
    }

/**
 * @brief Camera accessor.
 * @return the camera
*/
Camera &  Context::getCamera(){
    return camera;
}

/**
 * @brief SolarSystem accessor.
 * @return the SolarSystem object stored in the Context
*/
SolarSystem & Context::getSolarSys(){
    return solarSys;
}

/**
 * @brief Update the camera's position with the selected planet's position.
*/
void Context::update_camera(){
    camera.update_position(solarSys[planet_idx].getMatrices().getMVMatrix()[3]);
}

/**
 * @brief Select the next planet.
*/
void Context::next_planet(){
    planet_idx = (planet_idx == solarSys.nbPlanets() - 1) ? 0 : (planet_idx + 1);
}

/**
 * @brief Select the previous planet.
*/
void Context::previous_planet(){
    planet_idx = (planet_idx == 0) ? solarSys.nbPlanets() - 1 : (planet_idx - 1);
}
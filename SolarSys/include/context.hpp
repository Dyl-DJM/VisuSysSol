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
#include "../include/solarSystem.hpp"


class Context{

public:

    /**
     * @brief constructor.
     * @param cam The camera associated to the program
     * @param solarSystem The SolarSystem object associated to the program
    */
    Context(Camera & cam, SolarSystem & solarSystem);

    /**
     * Camera accessor.
     * @return the camera
    */
    Camera & getCamera();

    /**
     * @brief SolarSystem accessor.
     * @return the SolarSystem object stored in the Context
    */
    SolarSystem & getSolarSys();

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

private:
    Camera & camera;
    SolarSystem & solarSys;
    unsigned int planet_idx;  // Index of the selected planet in the solar system 
};
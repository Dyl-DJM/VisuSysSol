/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This is the core engine module, it gathers        =
=  the whole system that manages the behaviour       =
=  of the app.                                       =
=													 =
=  We can find the main loop that manages the        =
=  simulation.										 =
=													 =
======================================================
*/

#pragma once

#include <iostream>

#include "include/window.hpp"
#include "include/renderEngine.hpp"
#include "include/solarSystem.hpp"

#include <glimac/getTime.hpp> // Must keep it after the other includes

/**
 * @brief Renders the whole 3D simulation
 *
 * Launches the main loop that allows the program to run the 3D simulation.
 * It manages the computations of trasnformations, the window management,
 * and the rendering of a 3D environment.
 *
 * @param relativePath A path location where the app is ran.
 *
 * @return The code error of the core engine part.
 ********************************************************************************/
int render3DScene(char *relativePath);

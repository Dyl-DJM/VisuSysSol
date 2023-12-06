/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Texture management. Contains the functions        =
=  that allow the loading, the binding,              =
=  the filtering..                                   =
=													 =
======================================================
*/

#pragma once

#include <glimac/Program.hpp>

#include "include/resources.hpp"

/**
 * @brief Loads a texture.
 *
 * @param ptrText A pointer on an Image (defined in the glimac library).
 ********************************************************************************/
GLuint loadTexture(std::unique_ptr<Image> ptrText);

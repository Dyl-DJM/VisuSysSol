/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Module that manages the resources (files load     =
=  etc)                                      	     =
=  													 =
======================================================
*/

#pragma once

#include <glimac/Image.hpp>

using namespace glimac;

/**
 * @brief Loads an image at a given path.
 *
 * @param path Path of the Image to load.
 *
 * @return A pointer on an Image (defined in the glimac library).
 ********************************************************************************/
std::unique_ptr<Image> loadImgFromPath(const char *path);
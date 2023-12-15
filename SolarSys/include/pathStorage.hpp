/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Location of all the paths for the resources      =
=  used by the software.							 =
=													 =
======================================================
*/

#pragma once

/**
 * @brief Gathers all the path used in the app.
 ********************************************************************************/
class PathStorage
{
public:
    // Textures
    static constexpr const char *PATH_TEXTURE_SUN = "../assets/sun/sunBetter.jpg";
    static constexpr const char *PATH_TEXTURE_EARTH = "../assets/earth/earthMapBetter.jpg";
    static constexpr const char *PATH_TEXTURE_CLOUDS = "../assets/earth/earthCloudBetter.jpg";
    static constexpr const char *PATH_TEXTURE_SKYBOX = "../assets/skybox/spaceMilky.jpg";

    // Shaders
    static constexpr const char *RELATIVE_PATH_VERTEX = "SolarSys/shaders/3D.vs.glsl";         // Vertex shader path
    static constexpr const char *RELATIVE_PATH_FRAGMENT_1T = "SolarSys/shaders/1Text.fs.glsl"; // Single Texture shader path
    static constexpr const char *RELATIVE_PATH_FRAGMENT_2T = "SolarSys/shaders/2Text.fs.glsl"; // Multi texturing(2) shader path
};
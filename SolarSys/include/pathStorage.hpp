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

    static constexpr const char *PATH_TEXTURE_MERCURY = "../assets/mercury/mercurymapenhanced.jpg";

    static constexpr const char *PATH_TEXTURE_VENUS = "../assets/venus/venusmap.jpg";

    static constexpr const char *PATH_TEXTURE_EARTH = "../assets/earth/earthMapBetter.jpg";
    static constexpr const char *PATH_TEXTURE_CLOUDS = "../assets/earth/earthCloudBetter.jpg";
    static constexpr const char *PATH_TEXTURE_MOON = "../assets/earth/moon.jpg";

    static constexpr const char *PATH_TEXTURE_MARS = "../assets/mars/mars_1k_color.jpg";
    static constexpr const char *PATH_TEXTURE_PHOBOS = "../assets/mars/phobos.jpeg";
    static constexpr const char *PATH_TEXTURE_DEIMOS = "../assets/mars/deimos.jpeg";

    static constexpr const char *PATH_TEXTURE_JUPITER = "../assets/jupiter/jupiter2_2k.jpg";
    static constexpr const char *PATH_TEXTURE_CALLISTO = "../assets/jupiter/callisto.jpeg";
    static constexpr const char *PATH_TEXTURE_GANYMEDE = "../assets/jupiter/ganymede.jpeg";
    static constexpr const char *PATH_TEXTURE_EUROPA = "../assets/jupiter/europa.jpeg";
    static constexpr const char *PATH_TEXTURE_IO = "../assets/jupiter/io.jpeg";

    static constexpr const char *PATH_TEXTURE_SATURN = "../assets/saturn/saturnmap.jpg";
    static constexpr const char *PATH_TEXTURE_MIMAS = "../assets/saturn/mimas.jpeg";
    static constexpr const char *PATH_TEXTURE_ENCELADUS = "../assets/saturn/enceladus.jpeg";
    static constexpr const char *PATH_TEXTURE_TETHYS = "../assets/saturn/tethys.jpeg";
    static constexpr const char *PATH_TEXTURE_DIONE = "../assets/saturn/dione.jpeg";
    static constexpr const char *PATH_TEXTURE_REHA = "../assets/saturn/reha.jpeg";
    static constexpr const char *PATH_TEXTURE_TITAN = "../assets/saturn/titan.jpeg";
    static constexpr const char *PATH_TEXTURE_HYPERION = "../assets/saturn/hyperion.jpeg";
    static constexpr const char *PATH_TEXTURE_IAPETUS = "../assets/saturn/iapetus.jpeg";

    static constexpr const char *PATH_TEXTURE_URANUS = "../assets/uranus/uranusmap.jpg";
    static constexpr const char *PATH_TEXTURE_ARIEL = "../assets/uranus/ariel.jpeg";
    static constexpr const char *PATH_TEXTURE_UMBRIEL = "../assets/uranus/umbriel.png";
    static constexpr const char *PATH_TEXTURE_TITANIA = "../assets/uranus/titania.jpeg";
    static constexpr const char *PATH_TEXTURE_OBERON = "../assets/uranus/oberon.jpeg";
    static constexpr const char *PATH_TEXTURE_MIRANDA = "../assets/uranus/miranda.jpeg";

    static constexpr const char *PATH_TEXTURE_NEPTUNE = "../assets/neptune/neptunemap.jpg";
    static constexpr const char *PATH_TEXTURE_TRITON = "../assets/neptune/triton.jpeg";
    static constexpr const char *PATH_TEXTURE_NEREID = "../assets/neptune/nereid.jpeg";

    static constexpr const char *PATH_TEXTURE_PLUTO = "../assets/pluto/plutomap1k.jpg";
    static constexpr const char *PATH_TEXTURE_CHARON = "../assets/pluto/charon.jpeg";

    static constexpr const char *PATH_TEXTURE_SKYBOX = "../assets/skybox/spaceMilky.jpg";

    // Shaders
    static constexpr const char *RELATIVE_PATH_VERTEX = "SolarSys/shaders/3D.vs.glsl";                                 // Vertex shader path
    static constexpr const char *RELATIVE_PATH_FRAGMENT_FULLYLIGHTED1T = "SolarSys/shaders/1TextFullyLighted.fs.glsl"; // Path of the shader for single textures fully lighted
    static constexpr const char *RELATIVE_PATH_FRAGMENT_1T = "SolarSys/shaders/1Text.fs.glsl";                         // Single Texture shader path
    static constexpr const char *RELATIVE_PATH_FRAGMENT_2T = "SolarSys/shaders/2Text.fs.glsl";                         // Multi texturing(2) shader path
};
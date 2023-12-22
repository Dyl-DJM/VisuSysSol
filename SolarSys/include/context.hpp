#pragma once

#define GLFW_INCLUDE_NONE


#include "../include/camera.hpp"
#include "../include/solarSystem.hpp"


class Context{

public:
    Context(Camera & cam, SolarSystem & solarSystem);

    Camera & getCamera();

    SolarSystem & getSolarSys();

private:
    Camera & camera;
    SolarSystem & solarSys;
};
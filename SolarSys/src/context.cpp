#include "include/context.hpp"

Context::Context(Camera & cam, SolarSystem & solarSystem)
    : camera {cam}
    , solarSys {solarSystem}
    {}

Camera &  Context::getCamera(){
    return camera;
}

SolarSystem & Context::getSolarSys(){
    return solarSys;
}
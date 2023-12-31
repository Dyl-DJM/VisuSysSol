/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Light module that describes information about     =
=  any light source.                                 =
=  													 =
======================================================
*/

#include "include/light.hpp"

/**
 * @brief Constructor of the class.
 ********************************************************************************/
Light::Light()
    : _Kd{glm::vec3(1, 1, 1)}, _Ks{glm::vec3(1, .3, .8)}, _shininess{32}, _position{glm::vec3(0, 0, 0)}, _intensity{glm::vec3(30, 30, 30)} // TODO : The inital value for the position will be the center position defined in Matrices for example
{
}

/**
 * @brief Fills in the new settings of the light source.
 *
 * @param kd A vector describing the diffuse coefficient of the material.
 * @param ks A vector describing the reflection coefficient of the material.
 * @param shinniness A float value describing the shininess coefficient of the material.
 * @param pos A vector describing the position of the light source.
 * @param intensity A vector descriving the color of the light.
 ********************************************************************************/
void Light::fill(glm::vec3 kd, glm::vec3 ks, float shininess, glm::vec3 pos, glm::vec3 intensity)
{
    _Kd = kd;
    _Ks = ks;
    _shininess = shininess;
    _position = pos;
    _intensity = intensity;
}
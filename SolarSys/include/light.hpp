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

#pragma once

#include <glimac/glm.hpp>

/**
 * @brief Textured cube representation.
 ********************************************************************************/
class Light
{
public:
    Light()
        : _Kd{glm::vec3(1, 1, 1)}, _Ks{glm::vec3(1, .3, .8)}, _shininess{32}, _position{glm::vec3(0, 0, 2)}, _intensity{glm::vec3(100, 100, 100)} // TODO : The inital value for the position will be the center position defined in Matrices for example
    {
    }

    void fill(glm::vec3 kd, glm::vec3 ks, float shininess, glm::vec3 pos, glm::vec3 intensity)
    {
        _Kd = kd;
        _Ks = ks;
        _shininess = shininess;
        _position = pos;
        _intensity = intensity;
    }
    // Material coefficients
    glm::vec3 _Kd;        // Diffuse reflection
    glm::vec3 _Ks;        // Glossy reflection
    float _shininess = 0; // Shininess of the object

    // Light attributes
    glm::vec3 _position;  // Position in the 3D world
    glm::vec3 _intensity; // Intensity on the axes
};

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
    /**
     * @brief Constructor of the class.
     ********************************************************************************/
    Light();

    /**
     * @brief Fills in the new settings of the light source.
     *
     * @param kd A vector describing the diffuse coefficient of the material.
     * @param ks A vector describing the reflection coefficient of the material.
     * @param shinniness A float value describing the shininess coefficient of the material.
     * @param pos A vector describing the position of the light source.
     * @param intensity A vector descriving the color of the light.
     ********************************************************************************/
    void fill(glm::vec3 kd, glm::vec3 ks, float shininess, glm::vec3 pos, glm::vec3 intensity);

    // Material coefficients
    glm::vec3 _Kd;        // Diffuse reflection
    glm::vec3 _Ks;        // Glossy reflection
    float _shininess = 0; // Shininess of the object

    // Light attributes
    glm::vec3 _position;  // Position in the 3D world
    glm::vec3 _intensity; // Intensity on the axes
};

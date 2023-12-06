/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module gathers all the functions about       =
=  matrices used in 3D rendering.                    =
=													 =
======================================================
*/

#include "include/matrices.hpp"

/**
 * @brief Initialize the matrices.
 *
 * @param w Width used to build the projection matrix (with perspective
 * function).
 * @param h Height used to build the projection matrix (with perspective
 * function).
 * @param rotation A rotation value to represent the rotation based on the
 * ellipse.
 * @param translation A distance on the z axis.
 * @param scale A size transformation value.
 ********************************************************************************/
void Matrices::init(float w, float h, float rotation, float translation, float scale)
{

    std::cout << rotation << scale << std::endl; // TODO : remove when the rotation is handled in this function, it is here to avoid the warning and remove the iostream include in hpp
    _projMatrix = glm::perspective(glm::radians(70.f), w / h, 0.1f, 100.f);

    // Initial position of the object after transformations
    _MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, translation));
    _MVMatrix = glm::rotate(_MVMatrix, rotation, glm::vec3(1, 0, 0));
    _MVMatrix = glm::scale(_MVMatrix, glm::vec3(scale, scale, scale));

    _normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
    _MVPMatrix = _projMatrix * _MVMatrix;
}

/**
 * @brief Retrieves the Projection ModelView matrix.
 *
 * @return A view of the 4x4 Projection ModelView matrix.
 ********************************************************************************/
const glm::mat4 Matrices::getMVPMatrix() const
{
    return _MVPMatrix;
}

/**
 * @brief Retrieves the ModelView matrix.
 *
 * @return A view of the 4x4 ModelView matrix.
 ********************************************************************************/
const glm::mat4 Matrices::getMVMatrix() const
{
    return _MVMatrix;
}

/**
 * @brief Retrieves the Normal matrix.
 *
 * @return A view of the 4x4 Normal matrix.
 ********************************************************************************/
const glm::mat4 Matrices::getNormalMatrix() const
{
    return _normalMatrix;
}

/**
 * @brief Retrieves the Projection matrix.
 *
 * @return A view of the 4x4 Projection matrix.
 ********************************************************************************/
const glm::mat4 Matrices::getProjMatrix() const
{
    return _projMatrix;
}

/**
 * @brief Set a new value to the Projection ModelView matrix.
 *
 * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
 ********************************************************************************/
void Matrices::setMVPMatrix(glm::mat4 newMatrix)
{
    _MVPMatrix = newMatrix;
}

/**
 * @brief Set a new value to the ModelView matrix.
 *
 * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
 ********************************************************************************/
void Matrices::setMVMatrix(glm::mat4 newMatrix)
{
    _MVMatrix = newMatrix;
}

/**
 * @brief Set a new value to the Normal matrix.
 *
 * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
 ********************************************************************************/
void Matrices::setNormalMatrix(glm::mat4 newMatrix)
{
    _normalMatrix = newMatrix;
}
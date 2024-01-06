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

#pragma once

#include <glimac/glm.hpp>

/**
 * @brief Gathers many useful matrices used in 3D computer graphics.
 *
 * There are 4x4 matrices, including:
 *
 *      -> Projection matrix: Represents the transformation from 3D world coordinates
 *                             to 2D homogeneous coordinates for rendering.
 *      -> ModelView matrix: Represents the transformation from the object's local
 *                           coordinate system to the world coordinate system.
 *      -> Normal matrix: Represents the transformation on the normals' coordinates,
 *                        used for correct lighting calculations when transforming objects.
 *      -> Projection ModelView matrix: Represents the combined transformation of both
 *                                      the projection and modelview matrices.
 *
 * When an object is built, these matrices are initialized as identity matrices
 * until they are modified with the `init()` function or specific setters.
 ********************************************************************************/
class Matrices
{
public:
    /**
     * @brief Main constructor of the Matrice class.
     *
     * The class doesn't fill its attributes at this point.
     ********************************************************************************/
    Matrices() {}

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
    void init(float w, float h, float rotation, float translation, float scale);

    /**
     * @brief Retrieves the Projection ModelView matrix.
     *
     * @return A view of the 4x4 matrix that represents the Projection ModelView
     * matrix.
     ********************************************************************************/
    const glm::mat4 getMVPMatrix() const;

    /**
     * @brief Retrieves the ModelView matrix.
     *
     * @return A view of the 4x4 matrix that represents the ModelView matrix.
     ********************************************************************************/
    const glm::mat4 getMVMatrix() const;

    /**
     * @brief Retrieves the Normal matrix.
     *
     * @return A view of the 4x4 matrix that represents the Normal matrix.
     ********************************************************************************/
    const glm::mat4 getNormalMatrix() const;

    /**
     * @brief Retrieves the Projection matrix.
     *
     * @return A view of the 4x4 matrix that represents the Projection matrix.
     ********************************************************************************/
    const glm::mat4 getProjMatrix() const;

    /**
     * @brief Set a new value to the Projection ModelView matrix.
     *
     * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
     ********************************************************************************/
    void setMVPMatrix(glm::mat4 newMatrix);

    /**
     * @brief Set a new value to the ModelView matrix.
     *
     * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
     ********************************************************************************/
    void setMVMatrix(glm::mat4 newMatrix);

    /**
     * @brief Set a new value to the Normaal matrix.
     *
     * @param newMatrix A 4x4 (glm::mat4 provided by the glm library) matrix.
     ********************************************************************************/
    void setNormalMatrix(glm::mat4 newMatrix);

private:
    glm::mat4 _projMatrix;   // Projection matrix
    glm::mat4 _MVMatrix;     // ModelView matrix
    glm::mat4 _normalMatrix; // Normal matrix
    glm::mat4 _MVPMatrix;    // Projection ModelView matrix
};
/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module owns the management of a planet		 =
=  object, this means that we can find all the		 =
=  information we need to draw it            		 =
=  													 =
======================================================
*/
// UNCLEARRRRRRRRRR ^^^^^^^^

#pragma once

#include <vector>
#include <memory>

#include "include/planetData.hpp"
#include "include/shaderManager.hpp"
#include "include/matrices.hpp"

/**
 * @brief Represents a Planet.
 *
 * It contains all the information needed to display it in a 3D scene (textures,
 * shaders, matrices for transformations...)
 ********************************************************************************/
class PlanetObject
{
public:
    /**
     * @brief Constructor of the class.
     *
     * @param textureID An integer that describes the ID of the texture.
     * @param data A PlanetData (defined in the planetData module).
     * @param shader A shared_ptr (defined in the memory librarry) of a
     *               ShaderManager (defined in the shaderManager module).
     ********************************************************************************/
    PlanetObject(GLuint textureID, const PlanetData &data, std::shared_ptr<ShaderManager> shader);

    /**
     * @brief Constructor of the class.
     *
     * @param nbOfTextures Amount of textures.
     * @param textureIDs An array of integer that describes the IDs of the textures.
     * @param data A PlanetData (defined in the planetData module).
     * @param shader A shared_ptr (defined in the memory librarry) of a
     *               ShaderManager (defined in the shaderManager module).
     ********************************************************************************/
    PlanetObject(unsigned int nbOfTextures, GLuint *textureIDs, const PlanetData &data, std::shared_ptr<ShaderManager> shader);

    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    ~PlanetObject()
    {
    }

    /**
     * @brief Initialize all the transformation matrices.
     *
     * Configure the matrices which are going to determine the location of
     * the object in the scene.
     *
     * @param w Width that will be used for the pespective computation.
     * @param h Height that will be used for the pespective computation.
     ********************************************************************************/
    void configureMatrices(float w, float h);

    /**
     * @brief Apply transformations on the matrices.
     *
     * @param rotation A float value that determines how much do we rotate.
     ********************************************************************************/
    void updateMatrices(float rotation);

    /**
     * @brief Retrieves the ID of the textures binded to the planet object.
     *
     * @return A view of an ID vector for the textures this object is binded to.
     ********************************************************************************/
    const std::vector<GLuint> getTextIDs() const;

    /**
     * @brief Retrieves the ShaderManager (class defined in the shaderManager module)
     * of the planet object.
     *
     * @return A shared_ptr (defined in the memory library) of the ShaderManager.
     ********************************************************************************/
    std::shared_ptr<ShaderManager> getShaderManager();

    /**
     * @brief Retrieves the transformation matrices of a planet object.
     *
     * @return A view of the transformation matrices.
     ********************************************************************************/
    const Matrices &getMatrices() const;

private:
    PlanetData _data;                       // Information about the planet
    std::vector<GLuint> _textIDs;           // Textures IDs
    std::shared_ptr<ShaderManager> _shader; // ShaderManager (class defined in the shaderManager module)
    Matrices _matrices;                     // Transformation matrices
    // add the satellites (later)
};
/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module contains the management of a planet	 =
=  object, this means that we can find all the		 =
=  information we need to draw it (textures, shader, =
=  , data, matrices...)	     						 =
=													 =
======================================================
*/

#pragma once

#include <vector>
#include <memory>
#include <stdexcept>

#include "include/planetData.hpp"
#include "include/shaderManager.hpp"
#include "include/matrices.hpp"

// Forward declaration
class SatelliteObject;

/* ========================================================================================================== */
/* =                                                PLANETS                                                 = */
/* ========================================================================================================== */

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
     * @brief Constructor of the class.
     *
     * @param textureID An integer that describes the ID of the texture.
     * @param ringTextureID the ID of the ring texture
     * @param data A PlanetData (defined in the planetData module).
     * @param shader A shared_ptr (defined in the memory librarry) of a
     *               ShaderManager (defined in the shaderManager module).
     * @param ringShader shared_ptr of a ShaderManager pointing to the torus shader
     ********************************************************************************/
    PlanetObject(GLuint textureID, GLuint ringTextureID, const PlanetData &data, std::shared_ptr<ShaderManager> shader, std::shared_ptr<ShaderManager> ringShader);

    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    virtual ~PlanetObject() = default;

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
     * @param updateSatellites If true, then the satellites matrices are also
     *                         updated.
     ********************************************************************************/
    void updateMatrices(float rotation, bool updateSatellites);

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
    std::shared_ptr<ShaderManager> getShaderManager() const;

    /**
     * @brief Retrieves the transformation matrices of a planet object.
     *
     * @return A view of the transformation matrices.
     ********************************************************************************/
    const Matrices &getMatrices() const;

    /**
     * @brief Get the planetObject's size from its data.
     * @return The size of the planet.
     */
    float getSize() const;

    /**
     * @brief Returns wether or not the planet has a ring.
     */
    bool hasRing();

    /**
     * @brief Retrieves the ID of the textures binded to the planet object.
     *
     * @return A view of an ID vector for the textures this object is binded to.
     ********************************************************************************/
    const std::vector<GLuint> getRingTextIDs() const;

    /**
     * @brief Apply transformations on the matrices for the torus transformation.
     *        Note: the transformation of the MVMatrix for the planet must have already been done before calling this function
     ********************************************************************************/
    void updateMatricesTorus();

    /**
     * @brief Retrieves the ShaderManager (class defined in the shaderManager module)
     * of the planet's ring.
     *
     * @return A shared_ptr (defined in the memory library) of the ShaderManager.
     ********************************************************************************/
    std::shared_ptr<ShaderManager> getRingShaderManager();

    /**
     * @brief Accessor for the planet's data.
     */
    PlanetData getPlanetData();

    /**
     * @brief Set an ID for the planet's ring
     */
    void setRingID(int ID);

    /**
     * @brief Accessor for the ring ID
     */
    int getRingID() const;

    /**
     * @brief Adds a satellite to the planet.
     *
     * @param satellite A satellite we want to add to the planet.
     ********************************************************************************/
    virtual void addSatellite(SatelliteObject satellite);

    /**
     * @brief Retrieves the satellites of the planet.
     *
     * @return A view of the satellites stored by the planet.
     ********************************************************************************/
    std::vector<SatelliteObject> &getSatellites();

protected:                                  // We want the attributes to be available by the subclasses
    PlanetData _data;                       // Information about the planet
    std::vector<GLuint> _textIDs;           // Textures IDs
    std::shared_ptr<ShaderManager> _shader; // ShaderManager (class defined in the shaderManager module)
    Matrices _matrices;                     // Transformation matrices
    std::vector<GLuint> _ringTextIDs;
    std::shared_ptr<ShaderManager> _ringShader; // Shader for the ring
    int ringID;                                 // An ID for the ring, used to recover the planet's specific torus
    std::vector<SatelliteObject> _satellites;   // Satellites storage
};

/* ========================================================================================================== */
/* =                                                SATELLITES                                              = */
/* ========================================================================================================== */

class SatelliteObject : public PlanetObject
{
public:
    /**
     * @brief Constructor.
     *
     * @param textureID An integer that describes the ID of the texture.
     * @param data A PlanetData (defined in the planetData module).
     * @param shader A shared_ptr (defined in the memory librarry) of a
     *               ShaderManager (defined in the shaderManager module).
     ********************************************************************************/
    SatelliteObject(GLuint textureID, const PlanetData &data, std::shared_ptr<ShaderManager> shader);

    /**
     * @brief Constructor.
     *
     * @param nbOfTextures Amount of textures.
     * @param textureIDs An array of integer that describes the IDs of the textures.
     * @param data A PlanetData (defined in the planetData module).
     * @param shader A shared_ptr (defined in the memory librarry) of a
     *               ShaderManager (defined in the shaderManager module).
     ********************************************************************************/
    SatelliteObject(unsigned int nbOfTextures, GLuint *textureIDs, const PlanetData &data, std::shared_ptr<ShaderManager> shader);

    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    virtual ~SatelliteObject() = default;

    /**
     * @brief Redefinition of the inherited function.
     *
     * Throw an error because we don't want the satellite to store other satellites.
     *
     * @param satellite A satellite we want to add to the planet.
     ********************************************************************************/
    void addSatellite([[maybe_unused]] SatelliteObject satellite) override;

    /**
     * @brief Compute the satellite matrices thanks to a reference.
     *
     * @param refMatrix A reference matrix, we compute the satellite matrices by
     *                  doing the transformations above this one.
     * @param projMatrix Projection matrix.
     * @param rotation A float number that give information about the time spent.
     ********************************************************************************/
    void fillMatrices(glm::mat4 refMatrix, glm::mat4 projMatrix, float rotation);
};
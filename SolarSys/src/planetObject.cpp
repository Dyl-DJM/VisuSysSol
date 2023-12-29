/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module owns the management of a planet		 =
=  object, this means that we can find all the		 =
=  information we need to draw it            		 =
=													 =
======================================================
*/
// UNCLEARRRRRRRRRR ^^^^^^^^

#include "include/planetObject.hpp"

/**
 * @brief Constructor of the class.
 *
 * @param textureID An integer that describes the ID of the texture.
 * @param data A PlanetData (defined in the planetData module).
 * @param shader A shared_ptr (defined in the memory librarry) of a
 *               ShaderManager (defined in the shaderManager module).
 ********************************************************************************/
PlanetObject::PlanetObject(GLuint textureID, const PlanetData &data, std::shared_ptr<ShaderManager> shader) : _data{data}, _shader{shader}
{
    _textIDs.emplace_back(textureID);
}

/**
 * @brief Constructor of the class.
 *
 * @param nbOfTextures Amount of textures.
 * @param textureIDs An array of integer that describes the IDs of the textures.
 * @param data A PlanetData (defined in the planetData module).
 * @param shader A shared_ptr (defined in the memory librarry) of a
 *               ShaderManager (defined in the shaderManager module).
 ********************************************************************************/
PlanetObject::PlanetObject(unsigned int nbOfTextures, GLuint *textureIDs, const PlanetData &data, std::shared_ptr<ShaderManager> shader)
    : _data{data}, _shader{shader}
{
    for (unsigned int i = 0; i < nbOfTextures; i++)
    {
        _textIDs.emplace_back(textureIDs[i]);
    }
}

/**
 * @brief Initialize all the transformation matrices.
 *
 * Configure the matrices which are going to determine the location of
 * the object in the scene.
 *
 * @param w Width that whill be used for the pespective computation.
 * @param h Height that whill be used for the pespective computation.
 ********************************************************************************/
void PlanetObject::configureMatrices(float w, float h)
{
    _matrices.init(w, h, _data._angle, _data._position - 5, _data._diameter);
}

/**
 * @brief Apply transformations on the matrices.
 *
 * @param rotation A float value taht determines how much do we rotate.
 ********************************************************************************/
void PlanetObject::updateMatrices(float rotation)
{

    // Previous matrices
    // auto previousMVMatrix = _matrices.getMVMatrix();
    auto projMatrix = _matrices.getProjMatrix();

    // auto MVMatrixBasic = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, -5.f));

    // MVMatrix updates <=> transformations that leads to animation

    float rotationDegree = _data._rotationPeriod == 0 ? 0 : rotation * (1. / _data._rotationPeriod); // TODO : Change this computation that doesn't fit realty and put it at a function of the class
    float revolutionDegree = _data._revolutionPeriod == 0 ? 0 : rotation * (1. / _data._revolutionPeriod);
    // TODO : put real conversions iduced by real values of the rotation period, diameter etc..
    // auto MVMatrixBasic = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, 0));       // Central point of the sun : need to put it as a static field of the planet Data instead
    auto MVMatrix = glm::rotate(glm::mat4(1), revolutionDegree, glm::vec3(0, 1, 0)); // Rotation around the central point (the sun)

    MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, _data._position));                         // Distance from the central point (from the sun)
    MVMatrix = glm::rotate(MVMatrix, rotationDegree - revolutionDegree, glm::vec3(0, 1, 0));       // Rotation on itself
    MVMatrix = glm::scale(MVMatrix, glm::vec3(_data._diameter, _data._diameter, _data._diameter)); // Size dimension

    auto normalMatrix = glm::transpose(glm::inverse(MVMatrix));
    auto MVPMatrix = projMatrix * MVMatrix;

    _matrices.setMVMatrix(MVMatrix);
    _matrices.setNormalMatrix(normalMatrix);
    _matrices.setMVPMatrix(MVPMatrix);
}

/**
 * @brief Retrieves the ID of the textures binbed to the planet object.
 *
 * @return A view of an ID vector for the textures this object is binded to.
 ********************************************************************************/
const std::vector<GLuint> PlanetObject::getTextIDs() const
{
    return _textIDs;
}

/**
 * @brief Retrieves the ShaderManager (class defined in the shaderManager module)
 * of the planet object.
 *
 * @return A shared_ptr (defined in the memory library) of the ShaderManager.
 ********************************************************************************/
std::shared_ptr<ShaderManager> PlanetObject::getShaderManager()
{
    return _shader;
}

/**
 * @brief Retrieves the transformation matrices of a planet object.
 *
 * @return A view of the transformation matrices.
 ********************************************************************************/
const Matrices &PlanetObject::getMatrices() const
{
    return _matrices;
}

/**
 * @brief Get the planetObject's size from its data.
 * @return The size of the planet.
*/
float PlanetObject::getSize() const{
    return _data._diameter;
}
/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module defines the RenderEngine class        =
=  containing methods used for the rendering.	     =
=  													 =
======================================================
*/

#include "include/renderEngine.hpp"

/**
 * @brief Clears the display of the scene.   (CLEAR THE SCENE RATHER... MIGHT BE SMART TO RENAME IT clearScene)
 *
 * The current context of the rendered scene is cleared with a colored
 * background.
 ********************************************************************************/
void RenderEngine::clearDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Initialize the 3d configuration.
 *
 * It configures the depth of the scene in OpenGL.
 ********************************************************************************/
void RenderEngine::init3DConfiguration()
{
    glEnable(GL_DEPTH_TEST); // Enable the GPU to take the depth for 3D
}

/**
 * @brief Create a Sphere object, fill the vao and vbo with
 * its data.
 *
 * It configures the depth of the scene in OpenGL
 ********************************************************************************/
void RenderEngine::createSphere()
{
    auto sphere = Sphere(1, 32, 16);
    _nbVertices = sphere.getVertexCount();
    auto ptrVertices = sphere.getDataPointer();

    // Generates VBO buffer and binds it
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, _nbVertices * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
    // Unbind because we need a static draw (we won't modify the data in the buffer in the future)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind thanks to the Buffer ID 0

    // VAO generation
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex Attributes
    const GLuint ATTR_POSITION = 0;
    const GLuint ATTR_NORMAL = 1;
    const GLuint ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_NORMAL);
    glEnableVertexAttribArray(ATTR_TEXTURE);

    // Set the information for GPU on how to read the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position)); // Positions
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));     // Normals
    glVertexAttribPointer(ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords)); // Textures coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                  // Unbind thanks to the Buffer ID 0

    // Unbind the VAO
    glBindVertexArray(0);
}

/**
 * @brief Loads a texture at the given path.
 *
 * @param path Path representation of the texture location.
 ********************************************************************************/
GLuint RenderEngine::createTexture(const char *path)
{
    auto ptrText = loadImgFromPath(path);
    if (ptrText == NULL)
    {
        return ERR_INT_CODE;
    }
    return loadTexture(std::move(ptrText));
}

/**
 * @brief Configures the environment to allow the rendering.
 *
 * Bind the textures of the planet object and the VAO.
 *
 * @param planet A PlanetObject (defined in the planetObject module) we want
 *               to configure the drawing environment for.
 ********************************************************************************/
void RenderEngine::start(const PlanetObject &planet)
{

    // Bind the texture
    auto planetTexts = planet.getTextIDs();
    int i = 0;
    for (auto it = planetTexts.begin(); it != planetTexts.end(); it++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, *it); // Earth texture binded to #0
        i++;
    }

    // Bind the VAO to draw its data
    glBindVertexArray(_vao);
}

/**
 * @brief Launches the rendering of the given planet.
 *
 * @param planet A PlanetObject (defined in the planetObject module) we want
 *               to draw.
 ********************************************************************************/
void RenderEngine::draw(PlanetObject &planet)
{
    auto planetShader = planet.getShaderManager().get();
    auto &planetProgram = planetShader->m_Program; // Use of reference to not call the copy constructor of Program (which is private)

    planetProgram.use();

    auto transfos = planet.getMatrices();
    auto MVPMatrix = transfos.getMVPMatrix();
    auto MVMatrix = transfos.getMVMatrix();
    auto normalMatrix = transfos.getMVPMatrix();

    // Send matrices
    glUniformMatrix4fv(planetShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(planetShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(planetShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // //Send the textures
    int i = 0;
    auto planetTexts = planet.getTextIDs();

    for (auto it = planetTexts.begin(); it != planetTexts.end(); it++)
    {
        glUniform1i(planetShader->uTextures[i], i);
        i++;
    }

    // Draw the vertices
    glDrawArrays(GL_TRIANGLES, 0, _nbVertices);
}

/**
 * @brief Put an end to the current rendering environment.
 *
 * @param planet A PlanetObject (defined in the planetObject module) we want
 *               to put an end to the drawing environment for.
 ********************************************************************************/
void RenderEngine::end(const PlanetObject &planet)
{
    // Unbind textures
    for (unsigned int i = 0; i < planet.getTextIDs().size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Unbind the VAO
    glBindVertexArray(0);
}

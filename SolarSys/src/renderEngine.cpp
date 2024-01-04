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

#include <glimac/glm.hpp>

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
 * @brief Enables the Depth buffer.
 *
 * It configures the depth of the scene in OpenGL.
 ********************************************************************************/
void RenderEngine::enableZBuffer()
{
    glEnable(GL_DEPTH_TEST); // Enable the GPU to take the depth for 3D
}

/**
 * @brief Disable the Depth buffer.
 *
 * It disables the depth of the scene in OpenGL.
 ********************************************************************************/
void RenderEngine::disableZBuffer()
{
    glDisable(GL_DEPTH_TEST); // Disable the GPU to take the depth for 3D
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
 * @brief Create a Torus object, fill the vao and vbo with
 * its data.
 *
 * It configures the depth of the scene in OpenGL
 * @param innerEdgeDist The distance from the center of the inner edge of the torus
 * @param thickness The diameter of the torus pipe
 ********************************************************************************/
void RenderEngine::createTorus(GLfloat innerEdgeDist, GLfloat thickness)
{
    auto radius = innerEdgeDist + thickness;
    auto pipeRadius = thickness;
    std::cout << "radius: " << radius << ", pipeRadius: " << pipeRadius << std::endl;
    auto torus = Torus(radius, pipeRadius, 64, 16);
    _nbVerticesTorus = torus.getVertexCount();
    auto ptrVertices = torus.getDataPointer();

    GLuint vboTorus;
    GLuint vaoTorus;

    // Generates VBO buffer and binds it
    glGenBuffers(1, &vboTorus);
    glBindBuffer(GL_ARRAY_BUFFER, vboTorus);

    glBufferData(GL_ARRAY_BUFFER, _nbVerticesTorus * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbinding vbo

    // VAO generation
    glGenVertexArrays(1, &vaoTorus);
    glBindVertexArray(vaoTorus);

    // Vertex Attributes
    const GLuint ATTR_POSITION = 0;
    const GLuint ATTR_NORMAL = 1;
    const GLuint ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_NORMAL);
    glEnableVertexAttribArray(ATTR_TEXTURE);

    // Set the information for GPU on how to read the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, vboTorus);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position)); // Positions
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));     // Normals
    glVertexAttribPointer(ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords)); // Textures coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                  // Unbind thanks to the Buffer ID 0

    // Unbind the VAO
    glBindVertexArray(0);

    _vaoTorus.emplace_back(vaoTorus);
    _vboTorus.emplace_back(vboTorus);
}

void RenderEngine::createPlanetRing(PlanetObject &planet)
{
    if (planet.hasRing())
    {
        auto data = planet.getPlanetData();
        auto ringDistance = data._ringDist;
        auto ringThickness = data._ringThickness;
        createTorus(ringDistance, ringThickness);
        planet.setRingID(_vaoTorus.size() - 1);
    }
    else
    {
        planet.setRingID(-1);
    }
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
void RenderEngine::draw(const PlanetObject &planet, Camera &camera, const Light &light)
{
    start(planet);
    auto planetShader = planet.getShaderManager().get();
    auto &planetProgram = planetShader->m_Program; // Use of reference to not call the copy constructor of Program (which is private)

    planetProgram.use();

    auto transfos = planet.getMatrices();
    // auto MVPMatrix = transfos.getMVPMatrix();
    auto viewMatrix = camera.getViewMatrix();
    auto normalMatrix = transfos.getNormalMatrix();
    auto projMatrix = transfos.getProjMatrix();
    auto MVMatrix = viewMatrix * transfos.getMVMatrix();
    auto MVPMatrix = projMatrix * MVMatrix;

    normalMatrix = glm::transpose(glm::inverse(MVMatrix));

    // Send matrices
    glUniformMatrix4fv(planetShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(planetShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(planetShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Send Material Information
    glUniform3fv(planetShader->uKd, 1, glm::value_ptr(light._Kd));
    glUniform3fv(planetShader->uKs, 1, glm::value_ptr(light._Ks));
    glUniform1f(planetShader->uShininess, light._shininess);

    // Send Light Information
    glm::vec3 lightPos = glm::vec3(viewMatrix * glm::vec4(light._position, 1)); // The homogeneous coordinate must be 1
    glm::vec3 ambientLight = glm::vec3(0.4, 0.4, 0.4);                          // The homogeneous coordinate must be 1
    glUniform3fv(planetShader->uLightPosition, 1, glm::value_ptr(lightPos));
    glUniform3fv(planetShader->uLightIntensity, 1, glm::value_ptr(light._intensity));
    glUniform1i(planetShader->uIsLighted, true);
    glUniform3fv(planetShader->uAmbientLight, 1, glm::value_ptr(ambientLight));

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

    if (planet.hasRing())
    {

        auto ringShader = planet.getRingShaderManager().get();
        auto &ringProgram = ringShader->m_Program;

        ringProgram.use();

        // Draw torus
        startRing(planet);

        planet.updateMatricesTorus(); // Update the matrices for the torus

        auto transfos = planet.getMatrices();
        auto viewMatrix = camera.getViewMatrix();
        auto normalMatrix = transfos.getNormalMatrix();
        auto projMatrix = transfos.getProjMatrix();
        auto MVMatrix = viewMatrix * transfos.getMVMatrix();
        auto MVPMatrix = projMatrix * MVMatrix;

        // Send matrices
        glUniformMatrix4fv(ringShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(ringShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(ringShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // Send Material Information
        glUniform3fv(ringShader->uKd, 1, glm::value_ptr(light._Kd));
        glUniform3fv(ringShader->uKs, 1, glm::value_ptr(light._Ks));
        glUniform1f(ringShader->uShininess, light._shininess);

        // Send Light Information
        glUniform3fv(ringShader->uLightPosition, 1, glm::value_ptr(lightPos));
        glUniform3fv(ringShader->uLightIntensity, 1, glm::value_ptr(light._intensity));
        glUniform1i(ringShader->uIsLighted, true);
        glUniform3fv(ringShader->uAmbientLight, 1, glm::value_ptr(ambientLight));

        // //Send the textures
        int i = 0;
        auto ringTexts = planet.getRingTextIDs();

        for (auto it = ringTexts.begin(); it != ringTexts.end(); it++)
        {
            glUniform1i(ringShader->uTextures[i], i);
            i++;
        }

        // Draw the vertices
        glDrawArrays(GL_TRIANGLE_STRIP, 0, _nbVerticesTorus);

        endRing(planet);
    }

    end(planet);

    for (auto &satellite : planet.getSatellites())
    {
        draw(satellite, camera, light);
    }
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

/* ========================================================================================================== */
/* =                                                SKYBOX                                                  = */
/* ========================================================================================================== */

/**
 * @brief Integrates information of a skybox.
 *
 * @param skybox A skybox object (see the module skybox) we want its cube shape
 * toe ba drawable by the render engine.
 ********************************************************************************/
void RenderEngine::integrateSkybox(const Skybox &skybox)
{
    _nbVerticesSkybox = skybox.nbVertices();
    auto ptrVertices = skybox.data();

    // Generates VBO buffer and binds it
    glGenBuffers(1, &_vboSkybox);
    glBindBuffer(GL_ARRAY_BUFFER, _vboSkybox);

    glBufferData(GL_ARRAY_BUFFER, _nbVerticesSkybox * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
    // Unbind because we need a static draw (we won't modify the data in the buffer in the future)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind thanks to the Buffer ID 0

    /*********************** IBO *********************/

    glGenBuffers(1, &_ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox.nbIndexes() * sizeof(uint32_t), skybox.getIndexes(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*********************** VAO *********************/

    // VAO generation
    glGenVertexArrays(1, &_vaoSkybox);
    glBindVertexArray(_vaoSkybox);

    // Bind the VBO to the current VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

    // Vertex Attributes
    const GLuint ATTR_POSITION = 0;
    const GLuint ATTR_NORMAL = 1;
    const GLuint ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_NORMAL);
    glEnableVertexAttribArray(ATTR_TEXTURE);

    // Set the information for GPU on how to read the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, _vboSkybox);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position)); // Positions
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));     // Normals
    glVertexAttribPointer(ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords)); // Textures coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                  // Unbind thanks to the Buffer ID 0

    // Unbind the VAO
    glBindVertexArray(0);
}

/**
 * @brief Configures the environment to allow the rendering.
 *
 * Bind the textures of the skybox object and the VAO.
 *
 * @param skybox A Skybox (see the skybox module) we want
 *               to configure the drawing environment for.
 ********************************************************************************/
void RenderEngine::start(const Skybox &skybox)
{
    // Bind the texture
    auto skyboxTexts = skybox.getTextIDs();
    int i = 0;
    for (auto it = skyboxTexts.begin(); it != skyboxTexts.end(); it++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, *it); // Earth texture binded to #0
        i++;
    }

    // Bind the VAO to draw its data
    glBindVertexArray(_vaoSkybox);
}

/**
 * @brief Launches the rendering of the given skybox.
 *
 * @param skybox A Skybox (defined in the skybix module) we want
 *               to draw.
 ********************************************************************************/
void RenderEngine::draw(Skybox &skybox)
{
    auto skyboxShader = skybox.getShaderManager().get();
    auto &skyboxProgram = skyboxShader->m_Program; // Use of reference to not call the copy constructor of Program (which is private)

    skyboxProgram.use();

    auto transfos = skybox.getMatrices();
    auto MVPMatrix = transfos.getMVPMatrix();
    auto MVMatrix = transfos.getMVMatrix();
    auto normalMatrix = transfos.getNormalMatrix();

    // Send matrices
    glUniformMatrix4fv(skyboxShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(skyboxShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(skyboxShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    glUniform1i(skyboxShader->uIsLighted, false); // We don't want the cube to be lighted

    // //Send the textures
    int i = 0;
    auto skyboxTexts = skybox.getTextIDs();

    for (auto it = skyboxTexts.begin(); it != skyboxTexts.end(); it++)
    {
        glUniform1i(skyboxShader->uTextures[i], i);
        i++;
    }

    glDrawElements(GL_TRIANGLES, skybox.nbIndexes(), GL_UNSIGNED_INT, 0);
}

/**
 * @brief Put an end to the current rendering environment.
 *
 * @param skybox A Skybox object (defined in the skybox module) we want
 *               to put an end to the drawing environment for.
 ********************************************************************************/
void RenderEngine::end(const Skybox &skybox)
{
    // Unbind textures
    for (unsigned int i = 0; i < skybox.getTextIDs().size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // Unbind the VAO
    glBindVertexArray(0);
}

/**
 * @brief Configures the environment to allow the rendering.
 *
 * Bind the textures of the torus object and the VAO.
 *
 * @param planet The planet whose ring's texture we want to configure
 ********************************************************************************/
void RenderEngine::startRing(const PlanetObject &planet)
{
    auto ringTextIDs = planet.getRingTextIDs();
    int i = 0;
    for (auto it = ringTextIDs.begin(); it != ringTextIDs.end(); it++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, *it); // Earth texture binded to #0

        // GL_MIRRORED_REPEAT to repeat the texture above and below the torus in a mirrored way
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        i++;
    }

    // Bind the VAO to draw its data
    glBindVertexArray(_vaoTorus[planet.getRingID()]);
}

/**
 * @brief Put an end to the current rendering environment.
 *
 * @param planet A PlanetObject (defined in the planetObject module) we want
 *               to put an end to the drawing environment for.
 ********************************************************************************/
void RenderEngine::endRing(const PlanetObject &planet)
{
    // Unbind textures
    for (unsigned int i = 0; i < planet.getRingTextIDs().size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // Unbind the VAO
    glBindVertexArray(0);
}
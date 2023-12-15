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

#pragma once

#include <glad/glad.h>
#include <glimac/Sphere.hpp>

#include "include/textures.hpp"
#include "include/tools.hpp"
#include "include/planetObject.hpp"
#include "include/skybox.hpp"

#include <glimac/glm.hpp> // TODO delete when the skybox is finished/well defined

/**
 * @brief Represents all the render engine part of the application.
 *
 * It uses OpenGL libary.
 ********************************************************************************/
class RenderEngine
{
public:
    /**
     * @brief Constructor of the class.
     ********************************************************************************/
    RenderEngine() {}

    /**
     * @brief Clears the display of the scene.   (CLEAR THE SCENE RATHER... MIGHT BE SMART TO RENAME IT clearScene)
     *
     * The current context of the rendered scene is cleared with a colored
     * background.
     ********************************************************************************/
    static void clearDisplay();

    /**
     * @brief Initialize the 3d configuration.
     *
     * It configures the depth of the scene in OpenGL.
     ********************************************************************************/
    static void init3DConfiguration();

    /**
     * @brief Loads a texture at the given path.
     *
     * @param path Path representation of the texture location.
     ********************************************************************************/
    static GLuint createTexture(const char *path);

    /**
     * @brief Create a Sphere object, fill the vao and vbo with
     * its data.
     *
     * It configures the depth of the scene in OpenGL
     ********************************************************************************/
    void createSphere();

    /**
     * @brief Configures the environment to allow the rendering.
     *
     * Bind the textures of the planet object and the VAO.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to configure the drawing environment for.
     ********************************************************************************/
    void start(const PlanetObject &planet);

    /**
     * @brief Launches the rendering of the given planet.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to draw.
     ********************************************************************************/
    void draw(PlanetObject &planet);

    /**
     * @brief Put an end to the current rendering environment.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to put an end to the drawing environment for.
     ********************************************************************************/
    void end(const PlanetObject &planet);

    void integrateSkybox(const Skybox &skybox)
    {
        _nbVerticesSkybox = skybox.nbVertices();
        auto ptrVertices = skybox.data();

        // Generates VBO buffer and binds it
        glGenBuffers(1, &_vboSkybox);
        glBindBuffer(GL_ARRAY_BUFFER, _vboSkybox);

        glBufferData(GL_ARRAY_BUFFER, _nbVerticesSkybox * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
        // Unbind because we need a static draw (we won't modify the data in the buffer in the future)
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind thanks to the Buffer ID 0

        // VAO generation
        glGenVertexArrays(1, &_vaoSkybox);
        glBindVertexArray(_vaoSkybox);

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

    void start(const Skybox &skybox)
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

    void draw(Skybox &skybox)
    {
        auto skyboxShader = skybox.getShaderManager().get();
        auto &skyboxProgram = skyboxShader->m_Program; // Use of reference to not call the copy constructor of Program (which is private)

        skyboxProgram.use();

        auto transfos = skybox.getMatrices();
        auto MVPMatrix = transfos.getMVPMatrix();
        auto MVMatrix = transfos.getMVMatrix();
        auto normalMatrix = transfos.getMVPMatrix();

        // Send matrices
        glUniformMatrix4fv(skyboxShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
        glUniformMatrix4fv(skyboxShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(skyboxShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // //Send the textures
        int i = 0;
        auto skyboxTexts = skybox.getTextIDs();

        for (auto it = skyboxTexts.begin(); it != skyboxTexts.end(); it++)
        {
            glUniform1i(skyboxShader->uTextures[i], i);
            i++;
        }

        // Draw the vertices
        glDrawArrays(GL_POLYGON, 0, _nbVerticesSkybox);
    }

    /**
     * @brief Put an end to the current rendering environment.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to put an end to the drawing environment for.
     ********************************************************************************/
    void end(const Skybox &skybox)
    {
        // Unbind textures
        for (unsigned int i = 0; i < skybox.getTextIDs().size(); i++)
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        // Unbind the VAO
        glBindVertexArray(0);
    }

private:
    GLuint _vbo;                  // VertexBufferObject ID
    GLuint _vao;                  // VertexArrayObject ID
    unsigned int _nbVertices = 0; // Amount of vertices to draw

    // Skybox
    GLuint _vboSkybox;
    GLuint _vaoSkybox;
    unsigned int _nbVerticesSkybox = 0;
};
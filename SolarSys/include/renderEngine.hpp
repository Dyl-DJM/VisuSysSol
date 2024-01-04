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
#include "include/events.hpp"
#include "include/skybox.hpp"
#include "include/light.hpp"
#include "include/torus.hpp"

#include <glimac/glm.hpp> // TODO : Delete when the skybox is finished/well defined

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
     * @brief Enables the Depth buffer.
     *
     * It configures the depth of the scene in OpenGL.
     ********************************************************************************/
    static void enableZBuffer();

    /**
     * @brief Disable the Depth buffer.
     *
     * It disables the depth of the scene in OpenGL.
     ********************************************************************************/
    static void disableZBuffer();

    /**
     * @brief Loads a texture at the given path.
     *
     * @param path Path representation of the texture location.
     ********************************************************************************/
    static GLuint createTexture(const char *path);

    /* ========================================================================================================== */
    /* =                                                PLANET                                                  = */
    /* ========================================================================================================== */

    /**
     * @brief Create a Sphere object, fill the vao and vbo with
     * its data.
     *
     * It configures the depth of the scene in OpenGL
     ********************************************************************************/
    void createSphere();

    /**
     * @brief Create a Torus object, fill the vao and vbo with
     * its data.
     *
     * It configures the depth of the scene in OpenGL
     * @param innerEdgeDist The distance from the center of the inner edge of the torus
     * @param thickness The diameter of the torus pipe
     ********************************************************************************/
    void createTorus(GLfloat innerEdgeDist, GLfloat thickness);

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
    void draw(PlanetObject &planet, Camera &camera, const Light &light);

    /**
     * @brief Put an end to the current rendering environment.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to put an end to the drawing environment for.
     ********************************************************************************/
    void end(const PlanetObject &planet);

    /* ========================================================================================================== */
    /* =                                                SKYBOX                                                  = */
    /* ========================================================================================================== */

    /**
     * @brief Integrates information of a skybox.
     *
     * @param skybox A skybox object (see the module skybox) we want its cube shape
     * toe ba drawable by the render engine.
     ********************************************************************************/
    void integrateSkybox(const Skybox &skybox);

    /**
     * @brief Configures the environment to allow the rendering.
     *
     * Bind the textures of the skybox object and the VAO.
     *
     * @param skybox A Skybox (see the skybox module) we want
     *               to configure the drawing environment for.
     ********************************************************************************/
    void start(const Skybox &skybox);

    /**
     * @brief Launches the rendering of the given skybox.
     *
     * @param skybox A Skybox (defined in the skybix module) we want
     *               to draw.
     ********************************************************************************/
    void draw(Skybox &skybox);

    /**
     * @brief Put an end to the current rendering environment.
     *
     * @param skybox A Skybox object (defined in the skybox module) we want
     *               to put an end to the drawing environment for.
     ********************************************************************************/
    void end(const Skybox &skybox);

    /**
     * @brief Configures the environment to allow the rendering.
     *
     * Bind the textures of the torus object and the VAO.
     *
     * @param planet The planet whose ring's texture we want to configure
     ********************************************************************************/
    void startRing(const PlanetObject &planet);

    /**
     * @brief Launches the rendering of the given planet.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to draw.
     ********************************************************************************/
    void drawRing(PlanetObject &planet, Camera &camera);

    /**
     * @brief Put an end to the current rendering environment.
     *
     * @param planet A PlanetObject (defined in the planetObject module) we want
     *               to put an end to the drawing environment for.
     ********************************************************************************/
    void endRing(const PlanetObject &planet);

    void createPlanetRing(PlanetObject & planet);

private:
    // Planets
    GLuint _vbo;                  // VertexBufferObject ID
    GLuint _vao;                  // VertexArrayObject ID
    unsigned int _nbVertices = 0; // Amount of vertices to draw

    std::vector<GLuint> _vboTorus;
    std::vector<GLuint> _vaoTorus;
    unsigned int _nbVerticesTorus = 0;

    // Skybox                          // TODO : Put it inside a map to store all the type of VBOs etc for each shape (sphere, cube, rings etc)
    GLuint _vboSkybox;
    GLuint _vaoSkybox;
    GLuint _ibo;
    unsigned int _nbVerticesSkybox = 0;
};
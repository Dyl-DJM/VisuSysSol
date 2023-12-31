/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module introduces the class used to          =
=  manage the shaders and the uniform values         =
=  easily.                                           =
=													 =
======================================================
*/

#include "include/shaderManager.hpp"

/* ================================= SHADER MANAGER ======================================= */

/**
 * @brief Constructor of the class.
 *
 * @param applicationPath A FilePath (defined in the glimac library) describing
 *                        the location where the app is ran.
 * @param vertexShaderPath A path to the vertex shader.
 * @param fragmentShaderPath A path to the fragment shader.
 ********************************************************************************/
ShaderManager::ShaderManager(const FilePath &applicationPath, const char *vertexShaderPath, const char *fragmentShaderPath) : m_Program(loadProgram(applicationPath.dirPath() + vertexShaderPath,
                                                                                                                                                    applicationPath.dirPath() + fragmentShaderPath))
{
    // Matrices
    uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");

    // Textures
    uTextures.emplace_back(glGetUniformLocation(m_Program.getGLId(), "uTexture"));

    // Light
    uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
    uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
    uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
    uLightPosition = glGetUniformLocation(m_Program.getGLId(), "uLightPos");
    uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    uIsLighted = glGetUniformLocation(m_Program.getGLId(), "uIsLighted");
}

/* ================================= SHADER1FULLYLIGHTEDTEXTURE ======================================= */

/**
 * @brief Constructor of the class.
 *
 * @param applicationPath A FilePath (defined in the glimac library) describing
 *                        the location where the app is ran.
 ********************************************************************************/
Shader1FullyLightedTexture::Shader1FullyLightedTexture(const FilePath &applicationPath)
    : ShaderManager(applicationPath, PathStorage::RELATIVE_PATH_VERTEX, PathStorage::RELATIVE_PATH_FRAGMENT_FULLYLIGHTED1T)
{
}

/* ================================= SHADER1TEXTURE ======================================= */

/**
 * @brief Constructor of the class.
 *
 * @param applicationPath A FilePath (defined in the glimac library) describing
 *                        the location where the app is ran.
 ********************************************************************************/
Shader1Texture::Shader1Texture(const FilePath &applicationPath)
    : ShaderManager(applicationPath, PathStorage::RELATIVE_PATH_VERTEX, PathStorage::RELATIVE_PATH_FRAGMENT_1T)
{
}

/* ================================= SHADER2TEXTURE ======================================= */

/**
 * @brief Constructor of the class.
 *
 * @param applicationPath A FilePath (defined in the glimac library) describing
 *                        the location where the app is ran.
 ********************************************************************************/
Shader2Texture::Shader2Texture(const FilePath &applicationPath) : ShaderManager(applicationPath, PathStorage::RELATIVE_PATH_VERTEX, PathStorage::RELATIVE_PATH_FRAGMENT_2T)
{
    uTextures.emplace_back(glGetUniformLocation(m_Program.getGLId(), "uSecondTexture"));
}
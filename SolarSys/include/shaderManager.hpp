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

#pragma once

#include <vector>
#include <glimac/Program.hpp>

#include "include/pathStorage.hpp"

using namespace glimac;

/**
 * @brief Structure that allows for better management of the shaders.
 ********************************************************************************/
class ShaderManager
{
protected:
    /**
     * @brief Constructor of the class.
     *
     * @param applicationPath A FilePath (defined in the glimac library) describing
     *                        the location where the app is ran.
     * @param vertexShaderPath A path to the vertex shader.
     * @param fragmentShaderPath A path to the fragment shader.
     ********************************************************************************/
    ShaderManager(const FilePath &applicationPath, const char *vertexShaderPath, const char *fragmentShaderPath);

public:
    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    virtual ~ShaderManager() {}

    Program m_Program;            // GLSL Program (defined in glimac library)
    GLint uMVPMatrix;             // Uniform ID for Projection ModelView matrix
    GLint uMVMatrix;              // Uniform ID for ModelView matrix
    GLint uNormalMatrix;          // Uniform ID for Normal matrix
    std::vector<GLint> uTextures; // Texture IDs

    // Light components
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightPosition;
    GLint uLightIntensity;
    GLint uIsLighted;
};

/**
 * @brief Shader structure for single texture.
 ********************************************************************************/
class Shader1Texture : public ShaderManager
{
public:
    /**
     * @brief Constructor of the class.
     *
     * @param applicationPath A FilePath (defined in the glimac library) describing
     *                        the location where the app is ran.
     ********************************************************************************/
    Shader1Texture(const FilePath &applicationPath);
};

/**
 * @brief Shader structure for two textures.
 ********************************************************************************/
class Shader2Texture : public ShaderManager
{
public:
    /**
     * @brief Constructor of the class.
     *
     * @param applicationPath A FilePath (defined in the glimac library) describing
     *                        the location where the app is ran.
     ********************************************************************************/
    Shader2Texture(const FilePath &applicationPath);
};
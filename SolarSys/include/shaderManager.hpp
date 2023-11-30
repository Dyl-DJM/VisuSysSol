/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module introduces the structure used to      =
=  manage the shaders and the uniform values         =
=  easily.                                           =
=													 =
======================================================
*/

#pragma once


#include <glimac/Program.hpp>

#include "include/pathStorage.hpp"

using namespace glimac;


struct ShaderManager{
protected:
    ShaderManager(const FilePath &applicationPath, const char *vertexShaderPath, const char *fragmentShaderPath) : m_Program(loadProgram(applicationPath.dirPath() + vertexShaderPath,
                                                                     applicationPath.dirPath() + fragmentShaderPath))
    {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTextures.emplace_back(glGetUniformLocation(m_Program.getGLId(), "uTexture"));
    }

public:
    virtual ~ShaderManager(){}

    Program m_Program;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    std::vector<GLint> uTextures;
    
};


// Shader structure for single texture
struct Shader1Texture : public ShaderManager
{
public:
    Shader1Texture(const FilePath &applicationPath) 
    : ShaderManager(applicationPath, PathStorage::RELATIVE_PATH_VERTEX, PathStorage::RELATIVE_PATH_FRAGMENT_1T)
    {}
};


// Shader structure for multitexturing (2)
struct Shader2Texture : public ShaderManager
{
public:
    Shader2Texture(const FilePath &applicationPath) : ShaderManager(applicationPath, PathStorage::RELATIVE_PATH_VERTEX, PathStorage::RELATIVE_PATH_FRAGMENT_2T) 
    {
        uTextures.emplace_back(glGetUniformLocation(m_Program.getGLId(), "uSecondTexture"));
    }
};
/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Skybox definition, it represents a textured cube  =
=  this object can be used in an index buffer.       =
=  													 =
======================================================
*/

#pragma once

#include <vector>
#include <memory>

#include "include/shaderManager.hpp"

#include <glimac/FilePath.hpp>
#include <glimac/common.hpp> // Must be after the shaderManager import
#include "include/matrices.hpp"

using namespace glimac;

/**
 * @brief Textured cube representation.
 ********************************************************************************/
class Skybox
{
public:
    /**
     * @brief Builds a textured cube.
     *
     * Makes a skybox representation using the index buffer system.
     * This means that there are both a data storage and an index one.
     *
     * @param filePath A FilePath object (see the FilePath class in glimac).
     * @param textID An ID that describes a texture that has been loaded.
     * @param w The width of the window (used for the projection matrix).
     * @param h The height of the window (used for the projection matrix).
     ********************************************************************************/
    Skybox(FilePath filePath, GLuint textID, float w, float h);

    /**
     * @brief Retrieves the number of vertices.
     *
     * It gives the amount of vertices which describes the cube. (8 vertices minimum)
     *
     * @return The amount of vertices of the cube.
     ********************************************************************************/
    GLsizei nbVertices() const;

    /**
     * @brief Retrieves the vertices objects of the cube.
     *
     * The vertices retrieved are ShapeVertex objects (see the common module
     * in glimac).
     * These objects contains information about the 3D coordinates for a vertex,
     * its texture coordinates and its normals.
     *
     * @return A pointer on all the vertices of the cube.
     ********************************************************************************/
    const ShapeVertex *data() const;

    /**
     * @brief Retrieves all the texture IDs binded to the cube.
     *
     * @return A reference on a vector that contains all the textures binded to the
     * cube.
     ********************************************************************************/
    const std::vector<GLuint> &getTextIDs() const;

    /**
     * @brief Retrieves the ShaderManager of the cube.
     *
     * The ShaderManager (see the ShaderManager module) allows the cube to send
     * its information to the shaders.
     *
     * @return A pointer on the ShaderManager binded to this cube.
     ********************************************************************************/
    std::shared_ptr<ShaderManager> getShaderManager();

    /**
     * @brief Retrieves the transformation matrices of the cube.
     *
     * Brings a Matrices object (see the Matrices module), that contains MV, MVP and
     * normals matrices.
     *
     * @return A reference on the matrices.
     ********************************************************************************/
    const Matrices &getMatrices() const;

    /**
     * @brief Retrieves the indexes that describe the cube triangles.
     *
     * The indexes are refering to one of the points that describe the cube. In
     * this case, the cube is drawn thanks to triangle shapes.
     *
     * The triangles defined by three points are given by three indexes.
     *
     * @return A pointer on the indexes.
     ********************************************************************************/
    const uint32_t *getIndexes() const;

    /**
     * @brief Retrieves the number of indexes stored.
     *
     * @return The amount of indexes used for this cube.
     ********************************************************************************/
    uint nbIndexes() const;

private:
    /**
     * @brief Builds the cube representing the skybox.
     *
     * Creates a cube in 3D dimension thanks to 8 points defined and indexes that
     * describe how this shape can be drawn with triangles.
     *
     * @param filePath A FilePath object.
     * @param textID An integer index describing the information of the texture to
     *               send to the shader.
     * @param w The width of the window (used for the projection matrix).
     * @param h The height of the window (used for the projection matrix).
     ********************************************************************************/
    void build(FilePath filePath, GLuint textID, float w, float h);

    std::vector<ShapeVertex> _cube;         // Vertices that describe the shape
    std::shared_ptr<ShaderManager> _shader; // Shader binded to the cube
    Matrices _matrices;                     // Transformation matrices of the cube
    std::vector<GLuint> _texts;             // Textures Ids
    std::vector<uint32_t> _indexes;         // Indexes representing the triangles that draw the cube in 3D
};
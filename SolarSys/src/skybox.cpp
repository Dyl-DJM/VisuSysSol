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

#include "include/skybox.hpp"

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
Skybox::Skybox(FilePath filePath, GLuint textID, float w, float h)
{
    build(filePath, textID, w, h);
}

/**
 * @brief Retrieves the number of vertices.
 *
 * It gives the amount of vertices which describes the cube. (8 vertices minimum)
 *
 * @return The amount of vertices of the cube.
 ********************************************************************************/
GLsizei Skybox::nbVertices() const
{
    return _cube.size();
}

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
const ShapeVertex *Skybox::data() const
{
    return _cube.data();
}

/**
 * @brief Retrieves all the texture IDs binded to the cube.
 *
 * @return A reference on a vector that contains all the textures binded to the
 * cube.
 ********************************************************************************/
const std::vector<GLuint> &Skybox::getTextIDs() const
{
    return _texts;
}

/**
 * @brief Retrieves the ShaderManager of the cube.
 *
 * The ShaderManager (see the ShaderManager module) allows the cube to send
 * its information to the shaders.
 *
 * @return A pointer on the ShaderManager binded to this cube.
 ********************************************************************************/
std::shared_ptr<ShaderManager> Skybox::getShaderManager()
{
    return _shader;
}

/**
 * @brief Retrieves the transformation matrices of the cube.
 *
 * Brings a Matrices object (see the Matrices module), that contains MV, MVP and
 * normals matrices.
 *
 * @return A reference on the matrices.
 ********************************************************************************/
const Matrices &Skybox::getMatrices() const
{
    return _matrices;
}

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
const uint32_t *Skybox::getIndexes() const
{
    return _indexes.data();
}

/**
 * @brief Retrieves the number of indexes stored.
 *
 * @return The amount of indexes used for this cube.
 ********************************************************************************/
uint Skybox::nbIndexes() const
{
    return _indexes.size();
}

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
void Skybox::build(FilePath filePath, GLuint textID, float w, float h)
{
    /*
          5   *---------*    4
             /|        /|
        0   *---------* |  3
            | |       | |
           6| |_______|_*  7
            |/        |/
         1  *---------*  2

    */

    GLfloat points[8][3] = {
        // Foreground square
        {-1.0, 1.0, 1.0},  // Point 1
        {-1.0, -1.0, 1.0}, // Point 2
        {1.0, -1.0, 1.0},  // Point 3
        {1.0, 1.0, 1.0},   // Point 4

        // Background square
        {1.0, 1.0, -1.0},   // Point 5
        {-1.0, 1.0, -1.0},  // Point 6
        {-1.0, -1.0, -1.0}, // Point 7
        {1.0, -1.0, -1.0}   // Point 8
    };

    int text2DCoords[4][2] = {
        // Face text
        {0, 0}, // Point 1
        {0, 1}, // Point 2
        {1, 0}, // Point 3
        {1, 1}, // Point 4
    };

    for (int i = 0; i < 8; i++)
    {
        ShapeVertex vertex;

        vertex.position = glm::vec3(points[i][0], points[i][1], points[i][2]);
        vertex.texCoords.x = text2DCoords[i % 4][0];
        vertex.texCoords.y = text2DCoords[i % 4][1];
        vertex.normal = glm::normalize(vertex.position);

        _cube.push_back(vertex);
    }

    // Initialize the attributes of the class
    _matrices.init(w, h, 0, 0, 0.5); // 0.5 scale to have a 1x1x1 cube
    _shader = std::make_shared<Shader1Texture>(filePath);
    _texts.push_back(textID);
    _indexes = {
        // Front face
        0, 1, 2, // Triangle 1
        2, 0, 3, // Triangle 2

        // Upper face
        3, 4, 5, // Triangle 3
        5, 0, 3, // Triangle 4

        // Right face
        3, 4, 7, // Triangle 5
        7, 3, 2, // Triangle 6

        // Lower face
        2, 7, 6, // Triangle 7
        6, 2, 1, // Triangle 8

        // Left Face
        1, 0, 5, // Triangle 9
        5, 1, 6, // Triangle 10

        // Back Face
        6, 5, 4, // Triangle 9
        4, 6, 7  // Triangle 10
    };
}



#pragma once

#include <vector>
#include <memory>

#include "include/shaderManager.hpp"

#include <glimac/FilePath.hpp>
#include <glimac/common.hpp> // Must be after the shaderManager import
#include "include/matrices.hpp"

using namespace glimac;

class Skybox
{
public:
    Skybox(FilePath filePath, GLuint textID)
    {
        build(filePath, textID);
    }

    GLsizei nbVertices() const
    {
        return _cube.size();
    }

    const ShapeVertex *data() const
    {
        return _cube.data();
    }

    const std::vector<GLuint> getTextIDs() const
    {
        return _texts;
    }

    std::shared_ptr<ShaderManager> getShaderManager()
    {
        return _shader;
    }

    const Matrices &getMatrices() const
    {
        return _matrices;
    }

    const uint32_t *getIndexes() const
    {
        return _indexes.data();
    }

    uint nbIndexes() const
    {
        return _indexes.size();
    }

private:
    void
    build(FilePath filePath, GLuint textID)
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

        _matrices.init(1000, 1000, 0, 0, 0.5);

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

    std::vector<ShapeVertex>
        _cube;
    std::shared_ptr<ShaderManager> _shader;
    Matrices _matrices;

    std::vector<GLuint> _texts;

    std::vector<uint32_t> _indexes;
};
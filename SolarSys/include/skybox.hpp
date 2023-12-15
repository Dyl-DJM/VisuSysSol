

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

private:
    void
    build(FilePath filePath, GLuint textID)
    {
        /*
              6   *---------*    5
                 /|        /|
            1   *---------* |  4
                | |       | |
               7| |_______|_*  8
                |/        |/
             2  *---------*  3

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

        _matrices.init(1000, 1000, 20, -5, 1);

        _shader = std::make_shared<Shader1Texture>(filePath);

        _texts.push_back(textID);
    }

    std::vector<ShapeVertex>
        _cube;
    std::shared_ptr<ShaderManager> _shader;
    Matrices _matrices;

    std::vector<GLuint> _texts;
};
#pragma once

#include <vector>

#include <glimac/common.hpp>

class Torus
{
    void build(GLfloat radius, GLfloat thickness, GLsizei discLat, GLsizei discLong);

public:
    // Constructeur: alloue le tableau de données et construit les attributs des vertex
    Torus(GLfloat radius, GLfloat thickness, GLsizei discLat, GLsizei discLong) : m_nVertexCount(0)
    {
        build(radius, thickness, discLat, discLong); // Construction (voir le .cpp)
    }

    // Renvoit le pointeur vers les données
    const glimac::ShapeVertex *getDataPointer() const
    {
        return &m_Vertices[0];
    }

    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const
    {
        return m_nVertexCount;
    }

private:
    std::vector<glimac::ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
    std::vector<GLuint> texts;
};

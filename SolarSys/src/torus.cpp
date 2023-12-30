#include "../include/torus.hpp"




// Inspired by the code presented in https://electronut.in/torus/#torus-geometry
void Torus::build(GLfloat radius, GLfloat thickness, GLsizei discLat, GLsizei discLong){

    auto step_u = 2 * M_PI / discLat;
    auto step_v = 2 * M_PI / discLong;

    for (GLsizei i = 0; i <= discLat; i++){

        float u = step_u * i;

        for (GLsizei j = 0; j <= discLong; j++){

            float v = step_v * (j % discLong);

            for (GLsizei k = 0; k < 2; k++){

                glimac::ShapeVertex vertex;

                float u2 = u + (k * step_u); 

                // auto thicknessZ = (i > 10) ? thickness / 2 : thickness;

                // Computing position
                vertex.position.x = (radius + thickness * cos(v)) * cos(u2);
                vertex.position.y = (radius + thickness * cos(v)) * sin(u2);
                vertex.position.z = thickness / 10 * sin(v); // Division by 10 to "flatten" the torus

                // Computing normals
                vertex.normal.x = cos(v) * cos(u2);
                vertex.normal.y = cos(v) * sin(u2);
                vertex.normal.z = sin(v);

                // Computing textCoord
                vertex.texCoords.x = u2 / (2 * M_PI);
                vertex.texCoords.y = v / (2 * M_PI);
                // vertex.texCoords.x = j / discLong;
                // vertex.texCoords.y = i / discLat;

                m_Vertices.push_back(vertex);

            }
        }
    }

    m_nVertexCount = (discLat + 1) * (discLong + 1) * 2;
}

/*
======================================================
=  													 =
=     Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  Gathers the tasks linked to the rendering.        =
=													 =
=  This module role is to be the render engine of 	 =
=  global app.										 =
=  													 =
======================================================
*/

#include "include/renderEngine.hpp"

/**
 * @brief Clears the display on a window.
 *
 * The current context of the rendered scene is cleared with a colored background
 ********************************************************************************/
void clearDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint createTexture(const char *path)
{
    auto ptrText = loadImgFromPath(path);

    if (ptrText == NULL)
    {
        return ERR_INT_CODE;
    }

    return loadTexture(std::move(ptrText));
}

void init3DConfiguration()
{
    glEnable(GL_DEPTH_TEST); // Enable the GPU to take the depth for 3D
}



void RenderEngine::create3DSphere()
{
    auto sphere = Sphere(1, 32, 16);
    _nbVertices = sphere.getVertexCount();
    auto ptrVertices = sphere.getDataPointer();

    // Generates buffer of the VBO and binds it
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, _nbVertices * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
    // Unbind due to we need a static draw (we won't modify the data in the buffer in the future)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind thanks to the Buffer ID 0

    // VAO generation
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    // Vertex Attributes
    const GLuint ATTR_POSITION = 0;
    const GLuint ATTR_NORMAL = 1;
    const GLuint ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_NORMAL);
    glEnableVertexAttribArray(ATTR_TEXTURE);

    // Set the information for GPU of how to read the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position)); // Positions
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));     // Normals
    glVertexAttribPointer(ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords)); // Textures coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                  // Unbind thanks to the Buffer ID 0

    // Unbind the VAO to not modify again
    glBindVertexArray(0);
}



void RenderEngine::start(const PlanetObject& planet){

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, planet.getTextID());

    // Bind the VAO to draw its data
    glBindVertexArray(_vao);

}


void RenderEngine::draw(PlanetObject& planet){

    auto planetShader = planet.getShaderManager();
    auto& planetProgram = planetShader->m_Program; // Use of reference to not call the copy constructor of Program (which is private)

    planetProgram.use();

    auto transfos = planet.getMatrices();
    auto MVPMatrix = transfos.getMVPMatrix();
    auto MVMatrix = transfos.getMVMatrix();
    auto normalMatrix = transfos.getMVPMatrix();
    
    std::cout << "ARRRRRRFFGGGGGH : " << planetShader->uTexture << std::endl;

    // Send matrices
    glUniformMatrix4fv(planetShader->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));
    glUniformMatrix4fv(planetShader->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(planetShader->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Send Texture
    glUniform1i(planetShader->uTexture, planet.getTextID());

    // Draw the vertices
    glDrawArrays(GL_TRIANGLES, 0, _nbVertices);
}


void RenderEngine::end(const PlanetObject& planet){

    // UnBind the texture
    glBindTexture(GL_TEXTURE_2D, planet.getTextID()); // Put it in a loop for number of active textures

    // Unbind the VAO
    glBindVertexArray(0);
}
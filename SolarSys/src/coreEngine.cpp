/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This is the core engine module, it is the         =
=  gathering of the whole system that manages the    =
=  behaviour of the app.                             =
=													 =
=  We can find the main loop that manages the        =
=  simulation.										 =
=													 =
======================================================
*/

#include "include/coreEngine.hpp"

#include <glimac/Image.hpp> // LoadImage
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>

using namespace glimac;

struct SunData
{
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uSunTexture;

    SunData(const FilePath &applicationPath) : m_Program(loadProgram(applicationPath.dirPath() + "SolarSys/shaders/3D.vs.glsl",
                                                                     applicationPath.dirPath() + "SolarSys/shaders/3D.fs.glsl"))
    {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");

        uSunTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

/**
 * @brief Renders the whole 3D simulation
 *
 * Launches the main loop that allows the program to run the 3D simulation.
 * It manages the computations of trasnformations, the window management,
 * and the rendering of a 3D environment.
 *
 * @param relativePath A path location where the app is ran.
 *
 * @return The code error of the core engine part.
 ********************************************************************************/
int render3DScene(char *relativePath)
{

    /*************** WINDOW CREATION *****************/
    float windowWidth = 1000;
    float windowHeight = 1000;

    if (!Window::initWindowLib())
    {
        return ERR_INT_CODE;
    }

    auto window = Window(windowWidth, windowHeight, "App");

    if (!window.isCreated())
    {
        return ERR_INT_CODE;
    }

    window.configureEvents();

    /*************** TEXTURE LOAD *****************/
    // Sun
    auto PATH_TEXTURE_SUN = "../assets/sunMap.jpeg"; // Upgrade with applicationPath
    auto ptrTextSun = loadImage(PATH_TEXTURE_SUN);

    if (ptrTextSun == NULL)
    {
        std::cout << "Please check the path of the texture image (Sun)" << std::endl;
        return ERR_INT_CODE;
    }

    // Texture Object
    GLuint main_texture;
    glGenTextures(1, &main_texture);
    glBindTexture(GL_TEXTURE_2D, main_texture);

    // Send the image texture to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ptrTextSun->getWidth(), ptrTextSun->getHeight(), 0, GL_RGBA, GL_FLOAT, ptrTextSun->getPixels());

    // FIlters OPenGL will apply when using the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    /********************* SHADERS IMPORT/ UNIFORM/ PROGRAMMS ********************/
    FilePath applicationPath(relativePath);

    // Programs of lighted objects
    SunData sunProgram(applicationPath);

    /********************* INITIALIZATION ********************/
    glEnable(GL_DEPTH_TEST); // Enable the GPU to take the depth for 3D

    /*************** MATRICES *****************/

    glm::mat4 projMatrix, MVMatrix, normalMatrix, MVPMatrix;
    glm::mat4 MVMatrix_rotation, normalMatrix_rotation, MVPMatrix_rotation;

    projMatrix = glm::perspective(glm::radians(70.f), windowWidth / windowHeight, 0.1f, 100.f);
    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, -5.f));
    normalMatrix = glm::transpose(glm::inverse(MVMatrix));
    MVPMatrix = projMatrix * MVMatrix;

    /*************** VAO & VBO ****************/

    // Sphere object
    auto sphere = Sphere(1, 32, 16);
    auto nbVertices = sphere.getVertexCount();
    auto ptrVertices = sphere.getDataPointer();

    GLuint vbo;
    // Generates buffer of the VBO and binds it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, nbVertices * sizeof(ShapeVertex), ptrVertices, GL_STATIC_DRAW);
    // Unbind due to we need a static draw (we won't modify the data in the buffer in the future)
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind thanks to the Buffer ID 0

    // VAO generation
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Attributes
    const GLuint ATTR_POSITION = 0;
    const GLuint ATTR_NORMAL = 1;
    const GLuint ATTR_TEXTURE = 2;

    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_NORMAL);
    glEnableVertexAttribArray(ATTR_TEXTURE);

    // Set the information for GPU of how to read the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, position)); // Positions
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, normal));     // Normals
    glVertexAttribPointer(ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid *)offsetof(ShapeVertex, texCoords)); // Textures coords
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                  // Unbind thanks to the Buffer ID 0

    // Unbind the VAO to not modify again
    glBindVertexArray(0);

    float rot = 1;

    while (window.isWindowOpen())
    {
        clearDisplay();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /**************** RENDERING *****************/

        sunProgram.m_Program.use();

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, main_texture);

        // Send the matrices
        rot += .1;
        MVMatrix_rotation = glm::rotate(MVMatrix, rot, glm::vec3(0, 1, 0));
        normalMatrix_rotation = glm::transpose(glm::inverse(MVMatrix_rotation));
        MVPMatrix_rotation = projMatrix * MVMatrix_rotation;

        std::cout << sunProgram.uNormalMatrix << std::endl;

        glUniformMatrix4fv(sunProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix_rotation));
        glUniformMatrix4fv(sunProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix_rotation));
        glUniformMatrix4fv(sunProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix_rotation));

        glUniform1i(sunProgram.uSunTexture, 0); // Earth Texture

        // Bind the VAO to draw its data
        glBindVertexArray(vao);

        // ===== Earth =====
        glDrawArrays(GL_TRIANGLES, 0, nbVertices);

        // UnBind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Unbind the VAO
        glBindVertexArray(0);

        window.manageWindow(); // Make the window active (events) and swap the buffers
    }

    Window::freeCurrentWindow();

    return SUCCESS_INT_CODE;
}
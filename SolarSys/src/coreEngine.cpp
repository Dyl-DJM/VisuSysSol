/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This is the core engine module, it gathers        =
=  the whole system that manages the behaviour       =
=  of the app.                                       =
=													 =
=  We can find the main loop that manages the        =
=  simulation.										 =
=													 =
======================================================
*/

#include "include/coreEngine.hpp"

/**
 * @brief Build a Planet object.
 *
 * Thanks to IDs, it loads the corresponding textures to fill the planet to
 * create. It also needs information about the Data type we want to put inside
 * and the type of shader manager.
 * With these information it is possible to create a Planet Object and set its
 * initial matrices.
 * After the call of this function, it will be possible to display this object in
 * a 3D scene.
 *
 * @tparam DataType A type with information to bind to the planet, must be a PlanetData
 *         or a derived class.
 * @tparam ShaderType A type that gathers information about the shader management of the
 *         planet object, must be a ShaderManager or a derived class.
 * @param applicationPath A FilePath object (class of the glimac folder) to the folder where we find the shader files.
 * @param nbTextures Amount of textures to load from the given array.
 * @param textures An array of integers that contains textures ids.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 *
 * @return A PlanetObject, the object that can be displayed in a 3D scene.
 ********************************************************************************/
template <typename DataType = PlanetData, typename ShaderType = ShaderManager>
PlanetObject createPlanet(FilePath applicationPath, int nbTextures, unsigned int *textures, float windowWidth, float windowHeight)
{
    auto planetData = DataType();
    auto shader = std::make_shared<ShaderType>(applicationPath); // Need a shared_ptr here to avoid C pointers
    auto planet = PlanetObject(nbTextures, textures, planetData, shader);
    planet.configureMatrices(windowWidth, windowHeight); // Build the initial matrices linked to this planet
    return planet;
}

/**
 * @brief Build a Planet object.
 *
 * Thanks to an ID, it loads the corresponding texture to fill the planet to
 * create. It also needs information about the Data type we want to put inside
 * and the type of shader manager.
 * With these information it is possible to create a Planet Object and set its
 * initial matrices.
 * After the call of this function, it will be possible to display this object in
 * a 3D scene.
 *
 * @tparam DataType A type with information to bind to the planet, must be a PlanetData
 *         or a derived class.
 * @tparam ShaderType A type that gathers information about the shader management of the
 *         planet object, must be a ShaderManager or a derived class.
 * @param applicationPath A FilePath object (class of the glimac folder) to the folder where we find the shader files.
 * @param texture An integer ID of the texture we want to bind.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 *
 * @return A PlanetObject, the object that can be displayed in a 3D scene.
 ********************************************************************************/
template <typename DataType, typename ShaderType = ShaderManager>
PlanetObject createPlanet(FilePath applicationPath, unsigned int texture, float windowWidth, float windowHeight)
{
    auto planetData = DataType();
    auto shader = std::make_shared<ShaderType>(applicationPath); // Need a shared_ptr here to avoid C pointers
    auto planet = PlanetObject(texture, planetData, shader);
    planet.configureMatrices(windowWidth, windowHeight); // Build the initial matrices linked to this planet
    return planet;
}

/**
 * @brief Fills an empty solar sytem with all the information about it (planets...).
 *
 *  Creates planets and add them inside the given solar system object.
 *  It starts by creating and loading textures (at the Path stored in the PathStorage class
 *  defined in the pathStorage module).
 *  Then, it creates PlanetObject objects (class defined in the planetObject module) and store
 *  it inside a SolarSytem object (defined in the solarSystem module).
 *
 * @param relativePath Path location where the app is ran.
 * @param windowWidth Width of the window.
 * @param windowHeight Height of the window.
 * @param solarSys A SolarSystem object we want to fill.
 ********************************************************************************/
void createSolarSys(char *relativePath, float windowWidth, float windowHeight, SolarSystem &solarSys)
{

    FilePath applicationPath(relativePath);

    // Textures loading
    unsigned int sunText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_SUN);

    unsigned int mercuryText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MERCURY);
    unsigned int mercuryBumpText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MERCURY_BUMP);



    unsigned int earthText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_EARTH);
    unsigned int cloudText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_CLOUDS);

    // Sun
    PlanetObject sun = createPlanet<SunData, Shader1Texture>(applicationPath, sunText, windowWidth, windowHeight);

    // Mercury
    unsigned int mercuryTextures[] = {mercuryText, mercuryBumpText};
    PlanetObject mercury = createPlanet<MercuryData, Shader2Texture>(applicationPath, 2, mercuryTextures, windowWidth, windowHeight);

    // Earth
    unsigned int earthTextures[] = {earthText, cloudText};
    PlanetObject earth = createPlanet<EarthData, Shader2Texture>(applicationPath, 2, earthTextures, windowWidth, windowHeight); // TODO : When the data linking is done, no need to add 1 to the width

    // // Fill the solar system
    solarSys.addPlanet(std::make_unique<PlanetObject>(sun));
    solarSys.addPlanet(std::make_unique<PlanetObject>(mercury));
    solarSys.addPlanet(std::make_unique<PlanetObject>(earth));
}

/**
 * @brief Renders the whole 3D simulation
 *
 * Launches the main loop that allows the program to run the 3D simulation.
 * It manages the computations of transformations, the window management,
 * and the rendering of a 3D environment.
 *
 * @param relativePath Path location where the app is ran.
 *
 * @return The code error of the core engine part.
 ********************************************************************************/
int render3DScene(char *relativePath)
{
    /*************** WINDOW CREATION *****************/
    float windowWidth = 1000;
    float windowHeight = 1000;

    if (!Window::initWindowLib()) // Initialize the window library
    {
        return ERR_INT_CODE; // defined inside the tools module
    }
    auto window = std::make_unique<Window>(windowWidth, windowHeight, "== * Solar System * ==");

    if (!window->isCreated())
    {
        return ERR_INT_CODE; // defined inside the tools module
    }

    /********************* GRAPHIC OBJECTS CREATION ********************/

    auto solarSys = std::make_unique<SolarSystem>();
    createSolarSys(relativePath, windowWidth, windowHeight, *solarSys);
    Camera camera = Camera();

    /********************* CONTEXT OBJECT CREATION ********************/

    Context context = Context(camera, *solarSys);

    /********************* SETTING EVENTS AND PASSING CONTEXT ********************/

    window->configureEvents(context);

    /***************** INITIALIZE THE 3D CONFIGURATION (DEPTH) *******************/

    RenderEngine::init3DConfiguration();
    auto renderEng = std::make_unique<RenderEngine>();
    renderEng->createSphere();

    /********************* RENDERING LOOP ********************/
    while (window->isWindowOpen())
    {
        RenderEngine::clearDisplay(); // Allows the scene to update its rendering by clearing the display

        for (auto &planet : (*solarSys))
        {
            renderEng->start(planet);         // Binds textures and vao
            planet.updateMatrices(getTime()); // Update the matrices regarding the time
            context.update_camera();
            renderEng->draw(planet, camera);          // Draw the current planet
            renderEng->end(planet);           // Unbind the resources
        }

        window->manageWindow(); // Make the window active (events) and swap the buffers
    }

    // Reset the resources before the reset of the window library
    solarSys.reset();
    renderEng.reset();
    window->freeCurrentWindow();
    window.reset();

    // Ends the lib
    Window::endWindowLib();

    return SUCCESS_INT_CODE; // defined inside the tools module
}
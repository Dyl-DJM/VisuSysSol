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
template <typename DataType = PlanetData, typename ShaderType = ShaderManager, typename CelestialType = PlanetObject>
CelestialType createPlanet(FilePath applicationPath, int nbTextures, unsigned int *textures, float windowWidth, float windowHeight)
{
    auto planetData = DataType();
    auto shader = std::make_shared<ShaderType>(applicationPath); // Need a shared_ptr here to avoid C pointers
    auto planet = CelestialType(nbTextures, textures, planetData, shader);
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
template <typename DataType, typename ShaderType = ShaderManager, typename CelestialType = PlanetObject>
CelestialType createPlanet(FilePath applicationPath, unsigned int texture, float windowWidth, float windowHeight)
{
    auto planetData = DataType();
    auto shader = std::make_shared<ShaderType>(applicationPath); // Need a shared_ptr here to avoid C pointers
    auto planet = CelestialType(texture, planetData, shader);
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
template <typename DataType, typename ShaderType = ShaderManager, typename RingShaderType = ShaderManager>
PlanetObject createPlanetWithRing(FilePath applicationPath, unsigned int texture, unsigned int ringText, float windowWidth, float windowHeight)
{
    auto planetData = DataType();
    auto shader = std::make_shared<ShaderType>(applicationPath); // Need a shared_ptr here to avoid C pointers
    auto ringShader = std::make_shared<RingShaderType>(applicationPath);
    auto planet = PlanetObject(texture, ringText, planetData, shader, ringShader);
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

    unsigned int venusText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_VENUS);

    unsigned int earthText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_EARTH);
    unsigned int cloudText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_CLOUDS);
    unsigned int moonText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MOON);

    unsigned int marsText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MARS);
    unsigned int phobosText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_PHOBOS);
    unsigned int deimosText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_DEIMOS);

    unsigned int jupiterText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_JUPITER);
    unsigned int callistoText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_CALLISTO);
    unsigned int ganymedeText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_GANYMEDE);
    unsigned int europaText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_EUROPA);
    unsigned int ioText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_IO);

    unsigned int saturnText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_SATURN);
    unsigned int saturnRingText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_SATURN_RING);
    unsigned int mimasText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MIMAS);
    unsigned int enceladusText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_ENCELADUS);
    unsigned int tethysText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_TETHYS);
    unsigned int dioneText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_DIONE);
    unsigned int rehaText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_REHA);
    unsigned int titanText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_TITAN);
    unsigned int hyperionText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_HYPERION);
    unsigned int iapetusText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_IAPETUS);

    unsigned int uranusText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_URANUS);
    unsigned int uranusRingText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_URANUS_RING);
    unsigned int arielText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_ARIEL);
    unsigned int umbrielText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_UMBRIEL);
    unsigned int titaniaText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_TITANIA);
    unsigned int oberonText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_OBERON);
    unsigned int mirandaText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_MIRANDA);

    unsigned int neptuneText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_NEPTUNE);
    unsigned int tritonText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_TRITON);
    unsigned int nereidText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_NEREID);

    unsigned int plutoText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_PLUTO);
    unsigned int charonText = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_CHARON);

    // Sun
    PlanetObject sun = createPlanet<SunData, Shader1FullyLightedTexture>(applicationPath, sunText, windowWidth, windowHeight); // The sun is fully lighted and doesn't depend on any source of light

    // Mercury
    PlanetObject mercury = createPlanet<MercuryData, Shader1Texture>(applicationPath, mercuryText, windowWidth, windowHeight);

    // Venus
    PlanetObject venus = createPlanet<VenusData, Shader1Texture>(applicationPath, venusText, windowWidth, windowHeight);

    // Earth
    unsigned int earthTextures[] = {earthText, cloudText};
    PlanetObject earth = createPlanet<EarthData, Shader2Texture>(applicationPath, 2, earthTextures, windowWidth, windowHeight);
    SatelliteObject moon = createPlanet<MoonData, Shader1Texture, SatelliteObject>(applicationPath, moonText, windowWidth, windowHeight);
    earth.addSatellite(moon);

    // Mars
    PlanetObject mars = createPlanet<MarsData, Shader1Texture>(applicationPath, marsText, windowWidth, windowHeight);
    SatelliteObject phobos = createPlanet<PhobosData, Shader1Texture, SatelliteObject>(applicationPath, phobosText, windowWidth, windowHeight);
    SatelliteObject deimos = createPlanet<DeimosData, Shader1Texture, SatelliteObject>(applicationPath, deimosText, windowWidth, windowHeight);

    mars.addSatellite(phobos);
    mars.addSatellite(deimos);

    // Jupiter
    PlanetObject jupiter = createPlanet<JupiterData, Shader1Texture>(applicationPath, jupiterText, windowHeight, windowHeight);
    SatelliteObject callisto = createPlanet<CallistoData, Shader1Texture, SatelliteObject>(applicationPath, callistoText, windowWidth, windowHeight);
    SatelliteObject ganymede = createPlanet<GanymedeData, Shader1Texture, SatelliteObject>(applicationPath, ganymedeText, windowWidth, windowHeight);
    SatelliteObject europa = createPlanet<EuropaData, Shader1Texture, SatelliteObject>(applicationPath, europaText, windowWidth, windowHeight);
    SatelliteObject io = createPlanet<IoData, Shader1Texture, SatelliteObject>(applicationPath, ioText, windowWidth, windowHeight);

    jupiter.addSatellite(callisto);
    jupiter.addSatellite(ganymede);
    jupiter.addSatellite(europa);
    jupiter.addSatellite(io);

    // Saturn
    PlanetObject saturn = createPlanetWithRing<SaturnData, Shader1Texture, ShaderTorusTexture>(applicationPath, saturnText, saturnRingText, windowWidth, windowHeight);
    SatelliteObject mimas = createPlanet<MimasData, Shader1Texture, SatelliteObject>(applicationPath, mimasText, windowWidth, windowHeight);
    SatelliteObject enceladus = createPlanet<EnceladusData, Shader1Texture, SatelliteObject>(applicationPath, enceladusText, windowWidth, windowHeight);
    SatelliteObject tethys = createPlanet<TethysData, Shader1Texture, SatelliteObject>(applicationPath, tethysText, windowWidth, windowHeight);
    SatelliteObject dione = createPlanet<DioneData, Shader1Texture, SatelliteObject>(applicationPath, dioneText, windowWidth, windowHeight);
    SatelliteObject rhea = createPlanet<RheaData, Shader1Texture, SatelliteObject>(applicationPath, rehaText, windowWidth, windowHeight);
    SatelliteObject titan = createPlanet<TitanData, Shader1Texture, SatelliteObject>(applicationPath, titanText, windowWidth, windowHeight);
    SatelliteObject hyperion = createPlanet<HyperionData, Shader1Texture, SatelliteObject>(applicationPath, hyperionText, windowWidth, windowHeight);
    SatelliteObject iapetus = createPlanet<IapetusData, Shader1Texture, SatelliteObject>(applicationPath, iapetusText, windowWidth, windowHeight);
    saturn.addSatellite(mimas);
    saturn.addSatellite(enceladus);
    saturn.addSatellite(tethys);
    saturn.addSatellite(dione);
    saturn.addSatellite(rhea);
    saturn.addSatellite(titan);
    saturn.addSatellite(hyperion);
    saturn.addSatellite(iapetus);

    // Uranus
    PlanetObject uranus = createPlanetWithRing<UranusData, Shader1Texture, ShaderTorusTexture>(applicationPath, uranusText, uranusRingText, windowWidth, windowHeight);
    SatelliteObject ariel = createPlanet<ArielData, Shader1Texture, SatelliteObject>(applicationPath, arielText, windowWidth, windowHeight);
    SatelliteObject umbriel = createPlanet<UmbrielData, Shader1Texture, SatelliteObject>(applicationPath, umbrielText, windowWidth, windowHeight);
    SatelliteObject titania = createPlanet<TitaniaData, Shader1Texture, SatelliteObject>(applicationPath, titaniaText, windowWidth, windowHeight);
    SatelliteObject oberon = createPlanet<OberonData, Shader1Texture, SatelliteObject>(applicationPath, oberonText, windowWidth, windowHeight);
    SatelliteObject miranda = createPlanet<MirandaData, Shader1Texture, SatelliteObject>(applicationPath, mirandaText, windowWidth, windowHeight);

    uranus.addSatellite(ariel);
    uranus.addSatellite(umbriel);
    uranus.addSatellite(titania);
    uranus.addSatellite(oberon);
    uranus.addSatellite(miranda);

    // Neptune
    PlanetObject neptune = createPlanet<NeptuneData, Shader1Texture>(applicationPath, neptuneText, windowWidth, windowHeight);
    SatelliteObject triton = createPlanet<TritonData, Shader1Texture, SatelliteObject>(applicationPath, tritonText, windowWidth, windowHeight);
    SatelliteObject nereid = createPlanet<NereidData, Shader1Texture, SatelliteObject>(applicationPath, nereidText, windowWidth, windowHeight);

    neptune.addSatellite(triton);
    neptune.addSatellite(nereid);

    // Pluto
    PlanetObject pluto = createPlanet<PlutoData, Shader1Texture>(applicationPath, plutoText, windowWidth, windowHeight);
    SatelliteObject charon = createPlanet<CharonData, Shader1Texture, SatelliteObject>(applicationPath, charonText, windowWidth, windowHeight);

    pluto.addSatellite(charon);

    // Fill the solar system
    solarSys.addPlanet(std::make_unique<PlanetObject>(sun));
    solarSys.addPlanet(std::make_unique<PlanetObject>(mercury));
    solarSys.addPlanet(std::make_unique<PlanetObject>(venus));
    solarSys.addPlanet(std::make_unique<PlanetObject>(earth));
    solarSys.addPlanet(std::make_unique<PlanetObject>(mars));
    solarSys.addPlanet(std::make_unique<PlanetObject>(jupiter));
    solarSys.addPlanet(std::make_unique<PlanetObject>(saturn));
    solarSys.addPlanet(std::make_unique<PlanetObject>(uranus));
    solarSys.addPlanet(std::make_unique<PlanetObject>(neptune));
    solarSys.addPlanet(std::make_unique<PlanetObject>(pluto));
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

    // Solar System
    auto solarSys = std::make_unique<SolarSystem>();
    createSolarSys(relativePath, windowWidth, windowHeight, *solarSys);

    // Camera initialization
    Camera camera = Camera();

    // Light source
    auto sunLight = Light();

    /********************* CONTEXT OBJECT CREATION ********************/

    Context context = Context(camera, *solarSys, sunLight);
    float inProgramElapsedTime = getTime();
    float currentElapsedTime = getTime();

    /********************* SETTING EVENTS AND PASSING CONTEXT ********************/

    window->configureEvents(context);

    // Skybox
    FilePath applicationPath(relativePath);
    auto textID = RenderEngine::createTexture(PathStorage::PATH_TEXTURE_SKYBOX);
    auto skybox = std::make_unique<Skybox>(applicationPath, textID, windowWidth, windowHeight);

    /***************** INITIALIZE THE 3D CONFIGURATION (DEPTH) *******************/

    auto renderEng = std::make_unique<RenderEngine>();
    renderEng->createSphere();

    for (auto &planet : (*solarSys))
    {
        renderEng->createPlanetRing(planet);
    }

    renderEng->integrateSkybox(*skybox); // Allows the render engine to add the cube of the skybox in vaos and vbos

    /********************* RENDERING LOOP ********************/

    float step = 0;

    while (window->isWindowOpen())
    {
        RenderEngine::clearDisplay(); // Allows the scene to update its rendering by clearing the display

        RenderEngine::disableZBuffer();

        renderEng->start((*skybox));
        renderEng->draw((*skybox));
        renderEng->end((*skybox));

        RenderEngine::enableZBuffer();

        step = getTime() - currentElapsedTime;
        currentElapsedTime = getTime();

        for (auto &planet : (*solarSys))
        {
            inProgramElapsedTime += step * context.getSpeedMultiplier();
            inProgramElapsedTime += context.consumeTimeLeap();

            // Update the matrices regarding the time, we want the satellites to update its matrices only in the focused mode
            planet.updateMatrices(inProgramElapsedTime, context.isCamFocused());
            context.update_camera();
            renderEng->draw(planet, camera, sunLight); // Draw the current planet
        }

        window->manageWindow(); // Make the window active (events) and swap the buffers
    }

    // Reset the resources before the reset of the window library
    solarSys.reset();
    skybox.reset();
    renderEng.reset();
    window->freeCurrentWindow();
    window.reset();

    // Ends the lib
    Window::endWindowLib();

    return SUCCESS_INT_CODE; // defined inside the tools module
}
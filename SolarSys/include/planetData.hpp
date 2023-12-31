/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  This module contains the definition of classes    =
=  used to create instances of Planets.              =
=  These classes contains the planet's data such as  =
=  diameter, rotation period, ...                    =
=													 =
======================================================
*/

#pragma once

/**
 * @brief Class containing a planet's data.
 *
 * It stores data such as the rotation period of the planet, its size..
 ********************************************************************************/
class PlanetData
{
protected:
    /**
     * @brief Constructor of the class.
     *
     * @param rotation Rotation period of the planet in hour
     * @param diameter Size of the planet in km
     * @param position Position of the planet relative to the sun in km
     * @param orbitInclination The angle of inclination of the planet's orbit in degree
     * @param angle Axial tilt of the planet in degree
     * @param revPeriod Revolution period of the planet in Earth days
     * @param hasRing Whether or not the planet has a ring
     * @param ringDist The ring's distance in km from the planet's center
     * @param ringThickness The ring's size from the inner edge to the outer edge in km
     ********************************************************************************/
    PlanetData(float rotation, float diameter, float position, float orbitInclination, float angle, float revPeriod, bool hasRing, float ringDist, float ringThickness);

    // These are protexted beacause we want to retrieve them from a getter
    // to be sure we are taking the right value between these two
    const float _position;      // Unreal distances form the sun (Better for visualisation)
    const float _largePosition; // Real distances from the sun

public:
    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    virtual ~PlanetData() {}

    /**
     * @brief Retrieves the value of the planet position from the sun.
     ********************************************************************************/
    float getPosition();

    const float _rotationPeriod;   // Rotation period of the planet
    const float _diameter;         // Size of the planet
    const float _orbitInclination; // Angle of the inclination of the planet's orbit in degree
    const float _angle;            // Angle of rotation of the ellipse in degree
    const float _revolutionPeriod; // Revolution period of the planet
    const bool _hasRing;           // Boolean describing the presence of a ring or not.
    const float _ringDist;         // Distance of the ring from center of planet
    const float _ringThickness;    // Thickness of the ring

    static const float sizeUnit;     // The homothety unit we'll use to downscale the solar system
    static const float rotationUnit; // Homothety unit we'll use to reduce the time of rotation
    static const float distanceUnit;
    constexpr static const float satelliteOffset = 1000000;

    // Computation on the range of the solar system (For the visualisation distances)
    constexpr static const float x0 = 58000000;   // Position of the nearest planet
    constexpr static const float x1 = 5910000000; // Position of the farest planet
    constexpr static const float y0 = 30000000;   // Wanted position of the nearest planet
    constexpr static const float y1 = 99000000;   // Wanted position of the farest planet
    static bool _largeView;                       // Flag for the type of position (large distances or not)
};

inline const float PlanetData::sizeUnit = 139822. * 4; // We are setting 1 unit to 3 times 139822 km (Jupiter's size)
inline const float PlanetData::rotationUnit = 6.;      // We are setting 1 unit to 6 hours
inline const float PlanetData::distanceUnit = 8000000.;

/**
 * @brief Contains data about the Sun.
 *
 * A SunData object is a kind of PlanetData.
 ********************************************************************************/
class SunData : public PlanetData
{
public:
    /**
     * @brief Constructor of the class.
     ********************************************************************************/
    SunData();
};

class MercuryData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    MercuryData();
};

class VenusData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    VenusData();
};

/**
 * @brief Contains data about the Earth.
 *
 * A EarthData object is a kind of PlanetData.
 ********************************************************************************/
class EarthData : public PlanetData
{
public:
    /**
     * @brief Constructor of the class.
     ********************************************************************************/
    EarthData();
};

class MarsData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    MarsData();
};

class JupiterData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    JupiterData();
};

class SaturnData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    SaturnData();
};

class UranusData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    UranusData();
};

class NeptuneData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    NeptuneData();
};

class PlutoData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    PlutoData();
};

/* ========================================================================================================== */
/* =                                                SATELLITES                                              = */
/* ========================================================================================================== */

// ----------------------------------------- EARTH  -----------------------------------------
class MoonData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    MoonData();
};

// ----------------------------------------- MARS  -----------------------------------------
class PhobosData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    PhobosData();
};

class DeimosData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    DeimosData();
};

// ----------------------------------------- JUPITER  -----------------------------------------

class CallistoData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    CallistoData();
};

class GanymedeData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    GanymedeData();
};

class EuropaData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    EuropaData();
};

class IoData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    IoData();
};

// ----------------------------------------- SATURN  -----------------------------------------

class MimasData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    MimasData();
};

class EnceladusData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    EnceladusData();
};

class TethysData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    TethysData();
};

class DioneData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    DioneData();
};

class RheaData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    RheaData();
};

class TitanData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    TitanData();
};

class HyperionData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    HyperionData();
};

class IapetusData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    IapetusData();
};

// ----------------------------------------- URANUS  -----------------------------------------

class ArielData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    ArielData();
};

class UmbrielData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    UmbrielData();
};

class TitaniaData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    TitaniaData();
};

class OberonData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    OberonData();
};

class MirandaData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    MirandaData();
};

// ----------------------------------------- NEPTUNE  -----------------------------------------

class TritonData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    TritonData();
};

class NereidData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    NereidData();
};

// ----------------------------------------- PLUTO  -----------------------------------------

class CharonData : public PlanetData
{
public:
    /**
     * @brief Constructor
     */
    CharonData();
};

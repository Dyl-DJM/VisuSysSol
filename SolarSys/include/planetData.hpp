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
     * @param rotation Float value that describes the rotation period of the
     *                 planet.
     * @param diameter Size of the planet.
     * @param position Position value relative to the sun's position.
     * @param angle  Angle of the ellipse.
     ********************************************************************************/
    PlanetData(float rotation, float diameter, float position, float angle, float revPeriod, bool hasRing, float ringDist, float ringThickness);

public:
    /**
     * @brief Destructor of the class.
     ********************************************************************************/
    virtual ~PlanetData() {}

    const float _rotationPeriod;   // Rotation period of the planet
    const float _diameter;         // Size of the planet
    const float _position;         // Position of the planet relative to the sun
    const float _angle;            // Angle of rotation of the ellipse
    const float _revolutionPeriod; // Revolution period of the planet
    const bool _hasRing;          // Boolean describing the presence of a ring or not.
    const float _ringDist;        // Distance of the ring from center of planet
    const float _ringThickness;   // Thickness of the ring

    static const float sizeUnit;  // The homothety unit we'll use to downscale the solar system
    static const float rotationUnit;  // Homothety unit we'll use to reduce the time of rotation
    static const float distanceUnit;

};

inline const float PlanetData::sizeUnit = 142984.; // We are setting 1 unit to 142984 km (Jupiter's size)
inline const float PlanetData::rotationUnit = 6.;  // We are setting 1 unit to 6 hours
inline const float PlanetData::distanceUnit = 5000000.;  

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
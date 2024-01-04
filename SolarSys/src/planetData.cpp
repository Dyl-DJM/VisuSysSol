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

#include "include/planetData.hpp"

/*================================== PLANET DATA ====================================*/

/**
 * @brief Constructor of the class.
 *
 * @param rotation Rotation period of the planet in hour
 * @param diameter Size of the planet in km
 * @param position Position of the planet relative to the sun
 * @param angle Axial tilt of the planet
 * @param revPeriod Revolution period of the planet in Earth days
 * @param hasRing Whether or not the planet has a ring
 * @param ringDist The ring's distance in km from the planet's center
 * @param ringThickness The ring's size from the inner edge to the outer edge in km
 ********************************************************************************/
PlanetData::PlanetData(float rotation, float diameter, float position, float angle, float revPeriod, bool hasRing = false, float ringDist = 0, float ringThickness = 0)
    : _rotationPeriod{rotation / PlanetData::rotationUnit}
    , _diameter{diameter / PlanetData::sizeUnit}
    , _position{position / PlanetData::distanceUnit}
    , _angle{angle}
    , _revolutionPeriod{revPeriod * (24.f / PlanetData::rotationUnit)} // Since we count the revolution period as Earth days (24 hours)                                                                                                                                                                                                                              // And the rotationUnit is 6h, we multiply it by 4 .
    , _hasRing{hasRing},
     _ringDist{ringDist / (PlanetData::sizeUnit / 2)}, // Divide the unit by 2 because it's a radius and not a diameter
      _ringThickness{ringThickness / PlanetData::sizeUnit}
{
}

/*================================== SUN DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
SunData::SunData() : PlanetData(609.12, 1392680, 0, 0, 0)
{
}

// Mercury

MercuryData::MercuryData() : PlanetData(4222.6, 4879.4, 58000000, 0.01, 87.969)
{
}

// Venus

VenusData::VenusData() : PlanetData(2802.0, 12103.6, 108208930, 177.4, 224.701)
{
}

/*================================== EARTH DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
EarthData::EarthData() : PlanetData(24., 12742, 149597871, 23.5, 365.256)
{
}

// Mars
MarsData::MarsData() : PlanetData(24.6597, 6779, 227900000, 25.19, 686.980)
{
}

// Jupiter
JupiterData::JupiterData() : PlanetData(9.9259, 139822, 778000000, 3.13, 4332.589)
{
}

// Saturn
SaturnData::SaturnData() : PlanetData(10.656, 116464, 1434000000, 26.73, 10759.22, true, 66900, 72926) // We display only until the F ring
{
}

// Uranus
UranusData::UranusData() : PlanetData(17.24, 50724, 2871000000, 97.77, 30685.4, true, 41837, 9312) // Display until epsilon ring
{
}

// Neptune
NeptuneData::NeptuneData() : PlanetData(16.11, 49244, 4495000000, 28.32, 60189.)
{
}

// Pluto
PlutoData::PlutoData() : PlanetData(153.282, 2376, 5910000000, 119.61, 90560)
{
}
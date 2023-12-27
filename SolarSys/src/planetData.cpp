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
 * @param angle Angle of rotation of the ellipse
 * @param revPeriod Revolution period of the planet in Earth days
 ********************************************************************************/
PlanetData::PlanetData(float rotation, float diameter, float position, float angle, float revPeriod)
    : _rotationPeriod{rotation / PlanetData::rotationUnit}
    , _diameter{diameter / PlanetData::sizeUnit}
    , _position{position / PlanetData::distanceUnit}
    , _angle{angle}
    , _revolutionPeriod{revPeriod}  // Since we've set the rotation unit to 1 Earth day (24h) 
                                    // There's no need to modify the revolution as it is already expressed in Earth days
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

MercuryData::MercuryData() : PlanetData(4222.6, 4881, 58000000, 0, 87.969)
{
}

//Venus

VenusData::VenusData() : PlanetData(2802.0, 12103.6, 108208930, 0, 224.701)
{
}

/*================================== EARTH DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
EarthData::EarthData() : PlanetData(24., 12756, 149597871, 0, 365.256)
{
}

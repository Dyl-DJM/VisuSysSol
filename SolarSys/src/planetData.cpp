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

MercuryData::MercuryData() : PlanetData(1407.6, 4879.4, 58000000, 0.01, 87.969)
{
}

// Venus

VenusData::VenusData() : PlanetData(5832.6, 12103.6, 108208930, 177.4, 224.701)
{
}

/*================================== EARTH DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
EarthData::EarthData() : PlanetData(23.9345, 12742, 149597871, 23.5, 365.256)
{
}

// Mars
MarsData::MarsData() : PlanetData(24.6229, 6779, 227900000, 25.19, 686.980)
{
}

// Jupiter
JupiterData::JupiterData() : PlanetData(9.9250, 139822, 778000000, 3.13, 4332.589)
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
PlutoData::PlutoData() : PlanetData(-153.2928, 2376, 5910000000, 119.61, 90560)
{
}

/* ========================================================================================================== */
/* =                                                SATELLITES                                              = */
/* ========================================================================================================== */

// ----------------------------------------- EARTH  -----------------------------------------
MoonData::MoonData() : PlanetData(27.32, 3474, 384400 + satelliteOffset, -6.68, 27.32)
{
}

// ----------------------------------------- MARS  -----------------------------------------
PhobosData::PhobosData() : PlanetData(0.31891, 22.0, 9378 + satelliteOffset, 0, 0.31891)
{
}

DeimosData::DeimosData() : PlanetData(30.3, 12.4, 23460 + satelliteOffset, 0, 30.3)
{
}

// ----------------------------------------- JUPITER  -----------------------------------------
CallistoData::CallistoData() : PlanetData(16.689, 4800, 1882700 + satelliteOffset, 0, 16.689)
{
}

GanymedeData::GanymedeData() : PlanetData(7.155, 5.268, 1070412 + satelliteOffset, 0, 7.155)
{
}

EuropaData::EuropaData() : PlanetData(3.551, 3.121, 671034 + satelliteOffset, 0, 3.551)
{
}

IoData::IoData() : PlanetData(1.769, 3.643, 421800 + satelliteOffset, 0, 1.769)
{
}

// ----------------------------------------- SATURN  -----------------------------------------

MimasData::MimasData() : PlanetData(0.942, 396.4, 185520 + satelliteOffset, 0, 0.942)
{
}

EnceladusData::EnceladusData() : PlanetData(0.0, 504.2, 238020 + satelliteOffset, 0, 0.0)
{
}

TethysData::TethysData() : PlanetData(1.888, 1060.4, 294660 + satelliteOffset, 0, 1.888)
{
}

DioneData::DioneData() : PlanetData(0.524, 1122.8, 377400 + satelliteOffset, 0, 0.524)
{
}

RheaData::RheaData() : PlanetData(1.08, 1527.6, 527040 + satelliteOffset, 0, 1.08)
{
}

TitanData::TitanData() : PlanetData(0.174, 5150, 1221870 + satelliteOffset, 0, 0.174)
{
}

HyperionData::HyperionData() : PlanetData(0.629, 360.4, 1470900 + satelliteOffset, 0, 0.629)
{
}

IapetusData::IapetusData() : PlanetData(15.967, 1469, 3561300 + satelliteOffset, 0, 15.967)
{
}

// ----------------------------------------- URANUS  -----------------------------------------

ArielData::ArielData() : PlanetData(0.0, 1158.8, 191020 + satelliteOffset, 0, 0.0)
{
}

UmbrielData::UmbrielData() : PlanetData(0.0, 1169.4, 266300 + satelliteOffset, 0, 0.0)
{
}

TitaniaData::TitaniaData() : PlanetData(0.0, 1576.8, 435910 + satelliteOffset, 0, 0.0)
{
}

OberonData::OberonData() : PlanetData(0.0, 1522.8, 583520 + satelliteOffset, 0, 0.0)
{
}

MirandaData::MirandaData() : PlanetData(0.0, 471.6, 129390 + satelliteOffset, 0, 0.0)
{
}

// ----------------------------------------- NEPTUNE  -----------------------------------------

TritonData::TritonData() : PlanetData(156.865, 2706, 354759 + satelliteOffset, 0, 156.865)
{
}

NereidData::NereidData() : PlanetData(0.0, 340, 5513400 + satelliteOffset, 0, 0.0)
{
}

// ----------------------------------------- PLUTO  -----------------------------------------

CharonData::CharonData() : PlanetData(0.0, 1207, 19591 + satelliteOffset, 0, 0.0)
{
}
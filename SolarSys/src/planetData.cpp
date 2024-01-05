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

bool PlanetData::_largeView = true; // We want to take the real distances by default

/*================================== PLANET DATA ====================================*/

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
PlanetData::PlanetData(float rotation, float diameter, float position, float orbitInclination, float angle, float revPeriod, bool hasRing = false, float ringDist = 0, float ringThickness = 0)
    : _position{(position == 0 ? 0 : (y0 + (((position - x0) * (y1 - y0)) / (x1 - x0)))) / PlanetData::distanceUnit}, _largePosition{position / PlanetData::distanceUnit}, _rotationPeriod{rotation / PlanetData::rotationUnit}, _diameter{diameter / PlanetData::sizeUnit}, _orbitInclination{orbitInclination}, _angle{angle}, _revolutionPeriod{revPeriod * (24.f / PlanetData::rotationUnit)} // Since we count the revolution period as Earth days (24 hours)                                                                                                                                                                                                                              // And the rotationUnit is 6h, we multiply it by 4 .
      ,
      _hasRing{hasRing},
      _ringDist{ringDist / (PlanetData::sizeUnit / 2)}, // Divide the unit by 2 because it's a radius and not a diameter
      _ringThickness{ringThickness / PlanetData::sizeUnit}
{
}

/**
 * @brief Retrieves the value of the planet position from the sun.
 ********************************************************************************/
float PlanetData::getPosition()
{
  if (_largeView)
  {
    return _largePosition;
  }
  return _position;
}

/*================================== SUN DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
SunData::SunData() : PlanetData(609.12, 1392680, 0, 0, 0, 0)
{
}

// Mercury

MercuryData::MercuryData() : PlanetData(1407.6, 4879.4, 58000000, 6.3, 0.01, 87.969)
{
}

// Venus

VenusData::VenusData() : PlanetData(5832.6, 12103.6, 108208930, 2.2, 177.4, 224.701)
{
}

/*================================== EARTH DATA ====================================*/

/**
 * @brief Constructor of the class.
 ********************************************************************************/
EarthData::EarthData() : PlanetData(23.9345, 12742, 149597871, 1.6, 23.5, 365.256)
{
}

// Mars
MarsData::MarsData() : PlanetData(24.6229, 6779, 227900000, 1.7, 25.19, 686.980)
{
}

// Jupiter
JupiterData::JupiterData() : PlanetData(9.9250, 139822, 778000000, 0.3, 3.13, 4332.589)
{
}

// Saturn
SaturnData::SaturnData() : PlanetData(10.656, 116464, 1434000000, 0.9, 26.73, 10759.22, true, 66900, 72926) // We display only until the F ring
{
}

// Uranus
UranusData::UranusData() : PlanetData(17.24, 50724, 2871000000, 1.0, 97.77, 30685.4, true, 41837, 9312) // Display until epsilon ring
{
}

// Neptune
NeptuneData::NeptuneData() : PlanetData(16.11, 49244, 4495000000, 0.7, 28.32, 60189.)
{
}

// Pluto
PlutoData::PlutoData() : PlanetData(-153.2928, 2376, 5910000000, 17.0, 119.61, 90560)
{
}

/* ========================================================================================================== */
/* =                                                SATELLITES                                              = */
/* ========================================================================================================== */

// ----------------------------------------- EARTH  -----------------------------------------
MoonData::MoonData() : PlanetData(655.720, 3474, 384400 + satelliteOffset, 28.58, 6.68, 27.32)
{
}

// ----------------------------------------- MARS  -----------------------------------------
PhobosData::PhobosData() : PlanetData(7.65384, 22.0, 9378 + satelliteOffset, 1.093, 0, 0.31891)
{
}

DeimosData::DeimosData() : PlanetData(30.312, 12.4, 23460 + satelliteOffset, 0.93, 0, 1.263)
{
}

// ----------------------------------------- JUPITER  -----------------------------------------
CallistoData::CallistoData() : PlanetData(400.536, 4800, 1882700 + satelliteOffset, 2.017, 0, 16.689)
{
}

GanymedeData::GanymedeData() : PlanetData(171.72, 5.268, 1070412 + satelliteOffset, 2.214, 0.33, 7.155)
{
}

EuropaData::EuropaData() : PlanetData(85.224, 3.121, 671034 + satelliteOffset, 0.470, 0.1, 3.551)
{
}

IoData::IoData() : PlanetData(42.456, 3.643, 421800 + satelliteOffset, 0.05, 0, 1.769)
{
}

// ----------------------------------------- SATURN  -----------------------------------------

MimasData::MimasData() : PlanetData(22.608, 396.4, 185520 + satelliteOffset, 1.53, 0, 0.942)
{
}

EnceladusData::EnceladusData() : PlanetData(32.885, 504.2, 238020 + satelliteOffset, 0.009, 0, 1.370)
{
}

TethysData::TethysData() : PlanetData(45.312, 1060.4, 294660 + satelliteOffset, 1.86, 0, 1.888)
{
}

DioneData::DioneData() : PlanetData(65.68596, 1122.8, 377400 + satelliteOffset, 0.02, 0, 2.736915)
{
}

RheaData::RheaData() : PlanetData(108.42, 1527.6, 527040 + satelliteOffset, 0.35, 0, 4.517500)
{
}

TitanData::TitanData() : PlanetData(382.690, 5150, 1221870 + satelliteOffset, 0.33, 0, 15.945)
{
}

HyperionData::HyperionData() : PlanetData(510.624, 360.4, 1470900 + satelliteOffset, 0.43, 0, 21.276)
{
}

IapetusData::IapetusData() : PlanetData(1903.92, 1469, 3561300 + satelliteOffset, 14.72, 0, 79.330)
{
}

// ----------------------------------------- URANUS  -----------------------------------------

MirandaData::MirandaData() : PlanetData(33.912, 471.6, 129390 + satelliteOffset, 4.34, 0, 1.413)
{
}

ArielData::ArielData() : PlanetData(60.4872, 1158.8, 191020 + satelliteOffset, 0.04, 0, 2.5203)
{
}

UmbrielData::UmbrielData() : PlanetData(99.456, 1169.4, 266300 + satelliteOffset, 0.13, 0, 4.144)
{
}

TitaniaData::TitaniaData() : PlanetData(208.92, 1576.8, 435910 + satelliteOffset, 0.08, 0, 8.705)
{
}

OberonData::OberonData() : PlanetData(323.112, 1522.8, 583520 + satelliteOffset, 0.07, 0, 13.463)
{
}

// ----------------------------------------- NEPTUNE  -----------------------------------------

TritonData::TritonData() : PlanetData(141.044, 2706, 354759 + satelliteOffset, 157.345, 0, 5.876)
{
}

NereidData::NereidData() : PlanetData(8643.264, 340, 5513400 + satelliteOffset, 7.23, 0, 360.136)
{
}

// ----------------------------------------- PLUTO  -----------------------------------------

CharonData::CharonData() : PlanetData(153.6, 1207, 19591 + satelliteOffset, 0.080, 0, 6.4)
{
}
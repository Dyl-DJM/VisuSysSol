/*
======================================================
=  													 =
=      Made by Kevin QUACH and Dylan DE JESUS	     =
=													 =
=													 =
=  The tools module allows the definition of
=  helpful stuff that may be used by the other       =
=  modules.                                           =
=                                                    =
=													 =
======================================================
*/

#pragma once

#include <glimac/glm.hpp>

// Errors code for integer return values
#define ERR_INT_CODE 0
#define SUCCESS_INT_CODE 1

/**
 * @brief Converts a fraction into a degree value.
 *
 * @param num A float number that represents the fraction numerator.
 * @param denom A float number that represents the fraction denominator.
 *
 * @return A float number in degree.
 ********************************************************************************/
float fractionToDegrees(float num, float denom);

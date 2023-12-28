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

#include "include/tools.hpp"

/**
 * @brief Converts a fraction into a degree value.
 *
 * @param num A float number that represents the fraction numerator.
 * @param denom A float number that represents the fraction denominator.
 *
 * @return A float number in degree.
 ********************************************************************************/
float fractionToDegrees(float num, float denum)
{
    return glm::degrees(std::acos(1.0 - (num / denum)));
}

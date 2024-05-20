#pragma once

#include "Vec3.hpp"

namespace mathUtils
{

constexpr double pi = 3.1425;

class CoordinatesChange
{
  public:
	static Vec3 cartesianToSpherical(Vec3& vecInCartesian);
    static double getRadiousInCaresian(Vec3& vecInSpherical);
	static Vec3 sphericalToCartesian(Vec3& vecInSpherical);
};

} // namespace mathUtils

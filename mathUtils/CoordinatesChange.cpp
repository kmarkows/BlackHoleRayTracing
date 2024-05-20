#include "CoordinatesChange.hpp"

#include <cmath>

namespace mathUtils
{

Vec3 CoordinatesChange::cartesianToSpherical(Vec3& vecInCartesian)
{
	double r =
		std::pow(vecInCartesian.get()[0] * vecInCartesian.get()[0] + vecInCartesian.get()[1] * vecInCartesian.get()[1] +
					 vecInCartesian.get()[2] * vecInCartesian.get()[2],
				 0.5);
	double theta = std::acos(vecInCartesian.get()[2] / r);
    double fi = std::atan(vecInCartesian.get()[1] / vecInCartesian.get()[0]);
	Vec3 vecInSpherical({r, theta, fi});
	return vecInSpherical;
}

double CoordinatesChange::getRadiousInCaresian(Vec3& vecInSpherical)
{
    const auto& pos = vecInSpherical.get();
    return std::pow(pos[0] * pos[0] + pos[1] * pos[1] + pos[2] * pos[2], 0.5);
}

Vec3 CoordinatesChange::sphericalToCartesian(Vec3& vecInSpherical)
{
    double x = vecInSpherical.get()[0] * std::sin(vecInSpherical.get()[1]) * std::cos(vecInSpherical.get()[2]);
    double y = vecInSpherical.get()[0] * std::sin(vecInSpherical.get()[1]) * std::sin(vecInSpherical.get()[2]);
    double z = vecInSpherical.get()[0] * std::cos(vecInSpherical.get()[1]);
    Vec3 vecInCartesian({x, y, z});
	return vecInCartesian;
}

} // namespace mathUtils

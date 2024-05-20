#include "GeodesisGenerator.hpp"
#include <iostream>

int main()
{
	uint32_t steps = 10000;

	mathUtils::Vec3 startingPosition({20, 0.0, 0.0});
	mathUtils::Vec3 startingDirection({-1, 0.4, 0.0});
	double startingTime = 0;

	GeodesisGenerator geodesisGenerator;
	geodesisGenerator.trace(steps, startingPosition, startingDirection, startingTime);
}
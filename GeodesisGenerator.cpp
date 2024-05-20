#include "GeodesisGenerator.hpp"

void GeodesisGenerator::trace(uint32_t steps, mathUtils::Vec3 &startPos, mathUtils::Vec3 &startDir, double startTime)
{
	outputPositionData.push_back(startPos);
	outputTimeData.push_back(startTime);
	mathUtils::Vec4 x(startTime, startPos.get());
	mathUtils::Vec3 startPosCaretsian = mathUtils::CoordinatesChange::sphericalToCartesian(startPos);
	mathUtils::Vec4 p = getNullMomentum(x, startDir);
	std::pair<mathUtils::Vec4, mathUtils::Vec4> afterValues{};
	for (uint32_t i = 0; i < steps; i++)
	{
		afterValues = integrationSetp(x, p);

		mathUtils::Vec4 afterX = afterValues.first;
		mathUtils::Vec4 afterP = afterValues.second;

		mathUtils::Vec3 afterPosition = afterX.getSpacialCoordinates();
		afterPosition.print();

        mathUtils::Vec3 afterDir = afterP.getSpacialCoordinates();
        afterDir.print();

		std::cout << afterX.getTimeCoordinates() << std::endl;
		std::cout << (afterPosition.get()[0] - x.getSpacialCoordinates().get()[0]) << std::endl;
		;
		std::cout << (afterX.getTimeCoordinates() - x.getTimeCoordinates()) << std::endl;
		std::cout << std::endl;

		outputPositionData.push_back(afterX.getSpacialCoordinates());
		outputTimeData.push_back(afterX.getTimeCoordinates());

		if (mathUtils::CoordinatesChange::getRadiousInCaresian(afterPosition) < ((2 * G * M) / (c * c)))
		{
			std::cout << "osobliwosc" << std::endl;
			break;
		}

		x = afterX;
		p = afterP;
	}

	saveDataToFile();
}

std::pair<mathUtils::Vec4, mathUtils::Vec4> GeodesisGenerator::integrationSetp(mathUtils::Vec4 &x, mathUtils::Vec4 &p)
{
	const float timeStep = 0.01;
	mathUtils::Vec4 hamiltonianDiff = HamiltonianGradient(x, p) * timeStep;
    std::cout << "hamiltoniaDiff" << std::endl;
    hamiltonianDiff.print();
	mathUtils::Vec4 afterP = p - hamiltonianDiff;

	mathUtils::Mat4 metricsInv = getMetrix(x).inverse();
	mathUtils::Vec4 pMetrics = metricsInv * afterP;
	mathUtils::Vec4 pMetricsDiff = pMetrics * timeStep;
	mathUtils::Vec4 afterX = x + pMetricsDiff;
	return {afterX, afterP};
}

mathUtils::Vec4 GeodesisGenerator::HamiltonianGradient(mathUtils::Vec4 &x, mathUtils::Vec4 &p)
{
	const float eps = 0.001;
	mathUtils::Vec4 deltaX0({eps, 0, 0, 0});
	mathUtils::Vec4 deltaX1({0, eps, 0, 0});
	mathUtils::Vec4 deltaX2({0, 0, eps, 0});
	mathUtils::Vec4 deltaX3({0, 0, 0, eps});
	mathUtils::Vec4 xPlusDeltaX0 = x + deltaX0;
	mathUtils::Vec4 xPlusDeltaX1 = x + deltaX1;
	mathUtils::Vec4 xPlusDeltaX2 = x + deltaX2;
	mathUtils::Vec4 xPlusDeltaX3 = x + deltaX3;
	mathUtils::Vec4 hamiltonian({Hamiltonian(x, p), Hamiltonian(x, p), Hamiltonian(x, p), Hamiltonian(x, p)});
	mathUtils::Vec4 hamiltonianPlusDeltaX({Hamiltonian(xPlusDeltaX0, p), Hamiltonian(xPlusDeltaX1, p),
										   Hamiltonian(xPlusDeltaX2, p), Hamiltonian(xPlusDeltaX3, p)});

	return hamiltonianPlusDeltaX - hamiltonian;
}

double GeodesisGenerator::Hamiltonian(mathUtils::Vec4 &x, mathUtils::Vec4 &p)
{
	mathUtils::Mat4 metricsInv = getMetrix(x).inverse();
	return 0.5 * (metricsInv * p).dot(p);
}

mathUtils::Vec4 GeodesisGenerator::getNullMomentum(mathUtils::Vec4 &x, mathUtils::Vec3 &startDir)
{
	mathUtils::Vec3 startDirNorm = mathUtils::Normalize::normalize(startDir);
	mathUtils::Vec4 p(1.0, startDirNorm.get());
	std::cout << std::endl;
	mathUtils::Vec4 nullMomentum = getMetrix(x) * p;
	return nullMomentum;
}

mathUtils::Mat4 GeodesisGenerator::getMetrix(mathUtils::Vec4 &x)
{
	double a = 0.0;
	double m = 1.0;
	double Q = 0.0;

	mathUtils::Vec3 spaceCoordinates = x.getSpacialCoordinates();
	double rho = spaceCoordinates.dot(spaceCoordinates) - a * a;
	const auto &pos = spaceCoordinates.get();

	double r = std::pow(0.5 * (rho + std::pow(rho * rho + 4.0 * a * a * pos[2] * pos[2], 0.5)), 0.5);
	mathUtils::Vec4 k(
		{1, (r * pos[0] + a * pos[1]) / (r * r + a * a), (r * pos[1] - a * pos[0]) / (r * r + a * a), pos[2] / r});
	float f = r * r * ((2.0 * m * r) - (Q * Q)) / (std::pow(r, 4) + (a * a * pos[2] * pos[2]));

    mathUtils::Vec4 k0 = k * k.get()[0];
    mathUtils::Vec4 k1 = k * k.get()[1];
    mathUtils::Vec4 k2 = k * k.get()[2];
    mathUtils::Vec4 k3 = k * k.get()[3];

    mathUtils::Mat4 kerrNewmanMetricsOnlyVec(k0, k1, k2, k3);
    mathUtils::Mat4 flatTimeSpaceMetrics({{{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}});
    mathUtils::Mat4 kerrNewmanMetricsWithoutMinkowskiMetrics = kerrNewmanMetricsOnlyVec * f;
    mathUtils::Mat4 kerrNewmanMetrics = kerrNewmanMetricsWithoutMinkowskiMetrics + flatTimeSpaceMetrics;

	return kerrNewmanMetrics;
}

void GeodesisGenerator::saveDataToFile()
{
	std::ofstream filePosCartesian;
	filePosCartesian.open("./data/positionDataCaretsian.txt");
	for (uint32_t i = 0; i < outputPositionData.size(); i++)
	{
		auto &position = outputPositionData[i].get();
		filePosCartesian << position[0] << " " << position[1] << " " << position[2];
		filePosCartesian << std::endl;
	}
	filePosCartesian.close();

	std::ofstream filePosSpherical;
	filePosSpherical.open("./data/positionDataSpherical.txt");
	for (uint32_t i = 0; i < outputPositionData.size(); i++)
	{
        mathUtils::Vec3 outputPositionDataSpherical =
			mathUtils::CoordinatesChange::cartesianToSpherical(outputPositionData[i]);
		auto &position = outputPositionDataSpherical.get();
		filePosSpherical << position[0] << " " << position[1] << " " << position[2];
		filePosSpherical << std::endl;
	}
	filePosSpherical.close();

	std::ofstream fileTime;
	fileTime.open("./data/timeData.txt");
	for (uint32_t i = 0; i < outputTimeData.size(); i++)
	{
		fileTime << outputTimeData[i] << std::endl;
		;
	}
	fileTime.close();
}
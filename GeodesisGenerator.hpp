#include "./mathUtils/CoordinatesChange.hpp"
#include "./mathUtils/Mat4.hpp"
#include "./mathUtils/Normalize.hpp"
#include "./mathUtils/Vec3.hpp"
#include "./mathUtils/Vec4.hpp"
#include <cstdint>
#include <fstream>
#include <vector>

constexpr double c = 1;
constexpr double G = 1;
constexpr double M = 1;
constexpr double pi = 3.141592653589793238462643;

class GeodesisGenerator
{
  public:
	void trace(uint32_t steps, mathUtils::Vec3 &startPos, mathUtils::Vec3 &startDir, double startTime);

  private:
	std::pair<mathUtils::Vec4, mathUtils::Vec4> integrationSetp(mathUtils::Vec4 &x, mathUtils::Vec4 &p);
	mathUtils::Vec4 getNullMomentum(mathUtils::Vec4 &x, mathUtils::Vec3 &startDir);
	mathUtils::Vec4 HamiltonianGradient(mathUtils::Vec4 &x, mathUtils::Vec4 &p);
	mathUtils::Mat4 getMetrix(mathUtils::Vec4 &x);
	double Hamiltonian(mathUtils::Vec4 &x, mathUtils::Vec4 &p);
	void saveDataToFile();

	std::vector<mathUtils::Vec3> outputPositionData;
	std::vector<double> outputTimeData;
};

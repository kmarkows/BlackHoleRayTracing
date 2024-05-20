#pragma once

namespace mathUtils
{

class Normalize
{
  public:
	template <typename T> static T normalize(T &vec)
	{
		auto vector = vec.get();
		double sumOfElementsSquared = 0;
		for (const double element : vector)
		{
			sumOfElementsSquared += element * element;
		}

		for (uint8_t i = 0; i < vector.size(); i++)
		{
			vector[i] = vector[i] / std::pow(sumOfElementsSquared, 0.5);
		}
		return vector;
	}
};

} // namespace mathUtils

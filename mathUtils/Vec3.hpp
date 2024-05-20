#pragma once

#include <array>
#include <iostream>

namespace mathUtils
{

constexpr uint8_t vec3Size = 3;

class Vec3
{
  public:
	Vec3() : vec3({0, 0, 0}){};
	Vec3(std::array<double, vec3Size> givenVector) : vec3(givenVector){};

    double dot(mathUtils::Vec3 &otherVec3)
    {
        double product{};
        for (uint8_t i = 0; i < vec3Size; i++)
        {
            product += vec3[i] * otherVec3.get()[i];
        }
        return product;
    }

	void print()
	{
		for (const double element : vec3)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
	std::array<double, vec3Size> &get()
	{
		return vec3;
	};

  private:
	std::array<double, vec3Size> vec3;
};

} // namespace mathUtils

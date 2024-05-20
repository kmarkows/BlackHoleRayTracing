#pragma once

#include "Vec3.hpp"
#include <array>
#include <iostream>

namespace mathUtils
{

constexpr uint8_t vec4Size = 4;

class Vec4
{
  public:
	Vec4() : vec4({0, 0, 0, 0}){};
	Vec4(std::array<double, vec4Size> givenVector) : vec4(givenVector){};
	Vec4(double timeCoordinate, std::array<double, 3>& givenSpaceCoordinates);

	Vec4 operator+(Vec4 &otherVec4);
	Vec4 operator-(Vec4 &otherVec4);
	Vec4 operator*(double scalar);
	double dot(mathUtils::Vec4 &otherVec4);

	std::array<double, vec4Size> &get();
	Vec3 getSpacialCoordinates();
	double getTimeCoordinates();
	void print();

  private:
	std::array<double, vec4Size> vec4;
};

} // namespace mathUtils

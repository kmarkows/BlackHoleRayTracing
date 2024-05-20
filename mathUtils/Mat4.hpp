#pragma once

#include "Vec4.hpp"
#include <array>
#include <cstdint>

namespace mathUtils
{

constexpr uint8_t mat4Size = 4;

class Mat4
{
  public:
    Mat4() = default;
	Mat4(std::array<std::array<double, mat4Size>, mat4Size> givenMatrix) : mat(givenMatrix){};
    Mat4(Vec4& col0, Vec4& col1, Vec4& col2, Vec4& col3);

    Mat4 operator*(double scalar);
	Vec4 operator*(Vec4 &givenFourarray);
    Mat4 operator+(Mat4 &givenFourMatrix);
	Mat4 inverse();
	double det();

	std::array<std::array<double, mat4Size>, mat4Size> &get();
	void print();

  private:
	std::array<std::array<double, mat4Size>, mat4Size> mat;
};

} // namespace mathUtils

#include "Vec4.hpp"

namespace mathUtils
{

Vec4::Vec4(double timeCoordinate, std::array<double, 3>& givenSpaceCoordinates)
{
	vec4.at(0) = timeCoordinate;
	vec4.at(1) = givenSpaceCoordinates.at(0);
	vec4.at(2) = givenSpaceCoordinates.at(1);
	vec4.at(3) = givenSpaceCoordinates.at(2);
}

Vec4 Vec4::operator+(Vec4 &otherVec4)
{
	Vec4 product{};
	for (uint8_t i = 0; i < vec4Size; i++)
	{
		product.get()[i] = vec4[i] + otherVec4.get()[i];
	}
	return product;
}

Vec4 Vec4::operator-(Vec4 &otherVec4)
{
	Vec4 product{};
	for (uint8_t i = 0; i < vec4Size; i++)
	{
		product.get()[i] = vec4[i] - otherVec4.get()[i];
	}
	return product;
}

Vec4 Vec4::operator*(double scalar)
{
	Vec4 product{};
	for (uint8_t i = 0; i < vec4Size; i++)
	{
		product.get()[i] = scalar * vec4[i];
	}
	return product;
}

double Vec4::dot(mathUtils::Vec4 &otherVec4)
{
	double product{};
	for (uint8_t i = 0; i < vec4Size; i++)
	{
		product += vec4[i] * otherVec4.get()[i];
	}
	return product;
}

std::array<double, vec4Size> &Vec4::get()
{
	return vec4;
}

Vec3 Vec4::getSpacialCoordinates()
{
	Vec3 spacialCoordinates({vec4[1], vec4[2], vec4[3]});
	return spacialCoordinates;
}

double Vec4::getTimeCoordinates()
{
	return vec4[0];
}

void Vec4::print()
{
	for (const double element : vec4)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

} // namespace mathUtils

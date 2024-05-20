#include "Mat4.hpp"

namespace mathUtils
{

Mat4::Mat4(Vec4& col0, Vec4& col1, Vec4& col2, Vec4& col3)
{
    std::array<std::array<double, mat4Size>, mat4Size> tempMat{};
    for (uint8_t row = 0; row < mat4Size; row++)
	{
        tempMat[row][0] = col0.get()[row];
        tempMat[row][1] = col1.get()[row];
        tempMat[row][2] = col2.get()[row];
        tempMat[row][3] = col3.get()[row];
	}
    mat = tempMat;
}


Mat4 Mat4::operator*(double scalar)
{
    Mat4 multiplicationProduct{};
	for (uint8_t row = 0; row < mat4Size; row++)
	{
		for (uint8_t col = 0; col < mat4Size; col++)
		{
			multiplicationProduct.get()[row][col] += scalar * mat[row][col];
		}
	}
    return multiplicationProduct;
}

Vec4 Mat4::operator*(Vec4 &givenFourVector)
{
	Vec4 dotProd{};
	for (uint8_t row = 0; row < mat4Size; row++)
	{
		for (uint8_t col = 0; col < mat4Size; col++)
		{
			dotProd.get()[row] += mat[row][col] * givenFourVector.get()[col];
		}
	}
	return dotProd;
}

Mat4 Mat4::operator+(Mat4 &givenFourMatrix)
{
    Mat4 additionProduct{};
    for (uint8_t row = 0; row < mat4Size; row++)
	{
		for (uint8_t col = 0; col < mat4Size; col++)
		{
            additionProduct.get()[row][col] = mat[row][col] + givenFourMatrix.get()[row][col];
		}
	}
	return additionProduct;
}

Mat4 Mat4::inverse()
{
	std::array<std::array<double, mat4Size>, mat4Size> tempInversedProd{};
	double a2323 = mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2];
	double a1323 = mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1];
	double a1223 = mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1];
	double a0323 = mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0];
	double a0223 = mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0];
	double a0123 = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0];
	double a2313 = mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2];
	double a1313 = mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1];
	double a1213 = mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1];
	double a2312 = mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2];
	double a1312 = mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1];
	double a1212 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
	double a0313 = mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0];
	double a0213 = mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0];
	double a0312 = mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0];
	double a0212 = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
	double a0113 = mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0];
	double a0112 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

	double invDet = 1 / det();

	tempInversedProd[0][0] = invDet * (mat[1][1] * a2323 - mat[1][2] * a1323 + mat[1][3] * a1223);
	tempInversedProd[0][1] = invDet * -(mat[0][1] * a2323 - mat[0][2] * a1323 + mat[0][3] * a1223);
	tempInversedProd[0][2] = invDet * (mat[0][1] * a2313 - mat[0][2] * a1313 + mat[0][3] * a1213);
	tempInversedProd[0][3] = invDet * -(mat[0][1] * a2312 - mat[0][2] * a1312 + mat[0][3] * a1212);
	tempInversedProd[1][0] = invDet * -(mat[1][0] * a2323 - mat[1][2] * a0323 + mat[1][3] * a0223);
	tempInversedProd[1][1] = invDet * (mat[0][0] * a2323 - mat[0][2] * a0323 + mat[0][3] * a0223);
	tempInversedProd[1][2] = invDet * -(mat[0][0] * a2313 - mat[0][2] * a0313 + mat[0][3] * a0213);
	tempInversedProd[1][3] = invDet * (mat[0][0] * a2312 - mat[0][2] * a0312 + mat[0][3] * a0212);
	tempInversedProd[2][0] = invDet * (mat[1][0] * a1323 - mat[1][1] * a0323 + mat[1][3] * a0123);
	tempInversedProd[2][1] = invDet * -(mat[0][0] * a1323 - mat[0][1] * a0323 + mat[0][3] * a0123);
	tempInversedProd[2][2] = invDet * (mat[0][0] * a1313 - mat[0][1] * a0313 + mat[0][3] * a0113);
	tempInversedProd[2][3] = invDet * -(mat[0][0] * a1312 - mat[0][1] * a0312 + mat[0][3] * a0112);
	tempInversedProd[3][0] = invDet * -(mat[1][0] * a1223 - mat[1][1] * a0223 + mat[1][2] * a0123);
	tempInversedProd[3][1] = invDet * (mat[0][0] * a1223 - mat[0][1] * a0223 + mat[0][2] * a0123);
	tempInversedProd[3][2] = invDet * -(mat[0][0] * a1213 - mat[0][1] * a0213 + mat[0][2] * a0113);
	tempInversedProd[3][3] = invDet * (mat[0][0] * a1212 - mat[0][1] * a0212 + mat[0][2] * a0112);

	Mat4 inversedProd(tempInversedProd);
	return inversedProd;
}

double Mat4::det()
{
	double det{};
	det = mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0] - mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0] -
		  mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0] + mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0] +
		  mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0] - mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0] -
		  mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1] + mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1] +
		  mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1] - mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1] -
		  mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1] + mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1] +
		  mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2] - mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2] -
		  mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2] + mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2] +
		  mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2] - mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2] -
		  mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3] + mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3] +
		  mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3] - mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3] -
		  mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3] + mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3];
	return det;
}

std::array<std::array<double, mat4Size>, mat4Size> &Mat4::get()
{
	return mat;
}

void Mat4::print()
{
	for (const auto &row : mat)
	{
		for (const double num : row)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
}

} // namespace mathUtils

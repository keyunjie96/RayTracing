#include "Vector3.h"
#include <iostream>
#include <math.h>
using namespace std;

const double epsilon = 1e-5;
Vector3::Vector3()
{
}

Vector3::Vector3(double xx, double yy, double zz) : x(xx), y(yy), z(zz)
{
}

Vector3::~Vector3()
{
}

void Vector3::read(std::ifstream & fin)
{
	fin >> x >> y >> z;
}

double Vector3::operator[](const int & index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

double & Vector3::operator[](const int & index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

double Vector3::DotProduct(const Vector3 & rhs) const
{
	return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

Vector3 Vector3::GetRegulation() const
{
	double det = sqrt(x*x + y*y + z*z);
	if(det) return Vector3(x / det, y / det, z / det);
	else return Vector3(0, 0, 0);
}

Vector3 Vector3::GetVertical() const
{
	Vector3 vertical = (*this) * Vector3(1, 0, 0);
	if (vertical.EqualZero())
	{
		return Vector3(0, 1, 0);
	}
	else
		return vertical;
}

Vector3 Vector3::GetReflection(const Vector3 &axis) const
{
	return -2 * DotProduct(axis) * axis + (*this);//-- => +
}

Vector3 Vector3::GetRefraction(const Vector3 & axis, double ratio) const
{
	Vector3 axis_;
	if (DotProduct(axis) < -epsilon) { //注意入射光与轴夹角大于90°即可认为是外部结点
		ratio = 1 / ratio;
		axis_ = axis;
	}
	else
	{
		axis_ = Vector3(0, 0, 0) - axis;
	}
	double cosTheta1 = -DotProduct(axis_);
	double cosTheta2_ = 1 - pow(ratio, 2) * (1 - pow(cosTheta1, 2));
	if (cosTheta2_ > epsilon)
	{
		return  (*this) * ratio + axis_ * (ratio * cosTheta1 - sqrt(cosTheta2_));
	}
	else
	{
		//cout << "dd";
		return GetReflection(axis_);
	}
}

double Vector3::GetCosIncludedAngle(const Vector3 & axis) const
{
	return DotProduct(axis) / (this->GetModule2() * axis.GetModule2());
}

bool Vector3::isIllegal()
{
	return x < -epsilon && y < -epsilon && z < -epsilon;
}

double Vector3::GetModule2() const
{
	return x*x  + y * y + z * z;
}

double Vector3::GetDist(const Vector3 & rhs) const
{
	return sqrt(((*this) - rhs).GetModule2());
}

bool Vector3::EqualZero()
{
	return fabs(x) < epsilon && fabs(y) < epsilon && fabs(z) < epsilon;
}

std::ostream & operator<<(std::ostream & os, const Vector3 & rhs)
{
	char buffer[50]; sprintf(buffer, "%.2f %.2f %.2f\n", rhs.x, rhs.y, rhs.z);
	os << buffer; return os;
}

bool operator==(const Vector3 & lhs, const Vector3 & rhs)
{
	return fabs(lhs.x - rhs.x) < epsilon && fabs(lhs.y - rhs.y) < epsilon && fabs(lhs.z - rhs.z) < epsilon;
}

Vector3 operator+(const Vector3 & lhs, const Vector3 & rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator+=(Vector3 & lhs, const Vector3 & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 operator-=(Vector3 & lhs, const Vector3 & rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

Vector3 operator*(const Vector3 & lhs, const Vector3 & rhs)
{
	return Vector3(
		lhs.y * rhs.z - lhs.z * rhs.y, 
		lhs.z * rhs.x - lhs.x * rhs.z, 
		lhs.x * rhs.y - lhs.y * rhs.x);
}

Vector3 operator*(const Vector3 & lhs, double rhs)
{
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3 operator*(double lhs, const Vector3 & rhs)
{
	return rhs * lhs;
}

Vector3 operator*=(Vector3 & lhs, double rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Vector3 operator/(const Vector3 & lhs, double rhs)
{
	return lhs * (1 / rhs);
}

Vector3 operator/=(Vector3 & lhs, double rhs)
{
	lhs = lhs / rhs;
	return lhs;
}

bool operator<(const Vector3 & lhs, const Vector3 & rhs)
{
	return (lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z);
}

bool operator>(const Vector3 & lhs, const Vector3 & rhs)
{
	return (lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z);
}

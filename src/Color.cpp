#include "Color.h"
#include <math.h>
using namespace std;
const double epsilon = 1e-5;
Color::Color()
	:r(1), g(1), b(1)
{
}

Color::Color(double rr, double gg, double bb)
	:r(rr), g(gg), b(bb)
{
}


Color::~Color()
{
}

std::ostream & operator<<(std::ostream & os, const Color & rhs)
{
	char buffer[50]; sprintf(buffer, "%.2f %.2f %.2f\n", rhs.r, rhs.g, rhs.b);
	os << buffer; return os;
}

bool operator==(const Color & lhs, const Color & rhs)
{
	return fabs(lhs.r - rhs.r) < epsilon && fabs(lhs.g - rhs.g) < epsilon && fabs(lhs.b - rhs.b) < epsilon;
}

Color operator+(const Color & lhs, const Color & rhs)
{
	return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
}

Color operator+=(Color & lhs, const Color & rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

Color operator-(const Color & lhs, const Color & rhs)
{
	return Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
}

Color operator-=(Color & lhs, const Color & rhs)
{
	lhs = lhs - rhs;
	return lhs;
}

Color operator*(const Color & lhs, const Color & rhs)
{
	return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
}

Color operator*=(Color & lhs, const Color & rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Color operator*(const Color & lhs, double rhs)
{
	return Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs);
}

Color operator*(double lhs, const Color & rhs)
{
	return rhs * lhs;
}

Color operator*=(Color & lhs, double rhs)
{
	lhs = lhs * rhs;
	return lhs;
}

Color operator/(const Color & lhs, double rhs)
{
	return lhs * (1 / rhs);
}

Color operator/=(Color & lhs, double rhs)
{
	lhs = lhs / rhs;
	return lhs;
}

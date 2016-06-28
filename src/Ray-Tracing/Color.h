#pragma once
#include <iostream>
class Color
{
public:
	Color();
	Color(double rr, double gg, double bb);
	~Color();
	friend std::ostream& operator <<(std::ostream& os, const Color & rhs);
	friend bool operator ==(const Color & lhs, const Color & rhs);
	friend Color operator +(const Color & lhs, const Color & rhs);
	friend Color operator +=(Color & lhs, const Color & rhs);
	friend Color operator -(const Color & lhs, const Color & rhs);
	friend Color operator -=(Color & lhs, const Color & rhs);
	friend Color operator *(const Color & lhs, const Color & rhs);
	friend Color operator *(const Color & lhs, double rhs);
	friend Color operator*=(Color & lhs, const Color & rhs);
	friend Color operator *(double lhs, const Color & rhs);
	friend Color operator*=(Color & lhs, double rhs);
	friend Color operator *=(Color & lhs, double rhs);
	friend Color operator /(const Color & lhs, double rhs);
	friend Color operator /=(Color & lhs, double rhs);
	double r, g, b;
};


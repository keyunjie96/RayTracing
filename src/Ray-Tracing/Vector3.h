#pragma once
#include <fstream>
class Vector3
{
public:
	Vector3();
	Vector3(double xx, double yy, double zz);
	~Vector3();
	void read(std::ifstream & fin);
	friend std::ostream& operator <<(std::ostream& os, const Vector3 & rhs);
	friend bool operator ==(const Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator +(const Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator +=(Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator -(const Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator -=(Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator *(const Vector3 & lhs, const Vector3 & rhs);
	friend Vector3 operator *(const Vector3 & lhs, double rhs);
	friend Vector3 operator *(double lhs, const Vector3 & rhs);
	friend Vector3 operator *=(Vector3 & lhs, double rhs);
	friend Vector3 operator /(const Vector3 & lhs, double rhs);
	friend Vector3 operator /=(Vector3 & lhs, double rhs);
	friend bool operator < (const Vector3 & lhs, const Vector3 & rhs);
	friend bool operator > (const Vector3 & lhs, const Vector3 & rhs);
	double operator [](const int & index) const;
	double & operator [](const int & index);
	double DotProduct(const Vector3& rhs) const;
	Vector3 GetRegulation() const;
	Vector3 GetVertical() const; 
	Vector3 GetReflection(const Vector3 & axis) const;
	Vector3 GetRefraction(const Vector3 & axis, double ratio) const;
	double GetCosIncludedAngle(const Vector3 & axis) const;
	bool isIllegal();
	double GetModule2() const;
	double GetDist(const Vector3 &rhs) const;
	bool EqualZero();
	double x, y, z;
};


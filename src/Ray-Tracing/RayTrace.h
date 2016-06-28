#pragma once
#include "Color.h"
#include "Scene.h"
#include "Vector3.h"
#include <fstream>
#include <string>
#include <thread>
class Ray
{
public:
	Ray();
	Ray(const Vector3 &lp, const Vector3 &rp);
	~Ray();
	friend std::ostream& operator <<(std::ostream& os, const Ray & rhs);
	Ray GetNewTrace(const Vector3 & newTrace) const;
	Vector3 launchPoint, rayPath;
	double refractRatio, Energy;
};
class RayTrace
{
public:
	RayTrace();
	~RayTrace();
	Color Trace(const Ray & ray, int depth);
	void Run();
	void RunRange(int H0, int H1, int W0, int W1, bool output);
	void Read(std::string fileName);
	void Write(std::string fileName);
	int maxDepth;
	double sampling;
	Scene *scene;
};


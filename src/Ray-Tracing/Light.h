#pragma once
#include <vector>
#include <fstream>
#include "RayTrace.h"
#include "Object.h"
#include "Scene.h"
#include "Vector3.h"
class Ray;
class Object;
class Scene;
class Inter;
class Light
{
public:
	Light();
	virtual ~Light();
	virtual void read(std::ifstream & fin) = 0;
	virtual double calColor(Object *obj, Scene& scene) = 0;
	Vector3 lightPosi;
};

class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();
	void read(std::ifstream & fin);
	double calColor(Object *obj, Scene& scene);
};

class PlaneLight :
	public Light
{
public:
	PlaneLight();
	~PlaneLight();
	void read(std::ifstream & fin);
	double calColor(Object *obj, Scene& scene);
	Vector3 axis_X, axis_Y;
};

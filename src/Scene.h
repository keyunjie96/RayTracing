#pragma once
#include <vector>
#include <fstream>

class Camera;
class Color;
class Light;
class Object;
class Ray;
class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Object *> obj; void readObj(std::ifstream & fin);
	std::vector<Light *> light; void readLight(std::ifstream & fin);
	Camera* camera;
	Object* nearestObj; bool isCalNearestObj;
 
	double GetNearestInterDist(const Ray & ray);
	int GetNearestInterIndex(const Ray & ray);
	Object* GetNearestObject(const Ray & ray);
	Color GetLightColor();
	Color GetBackgroundColor(const Ray & ray);
};


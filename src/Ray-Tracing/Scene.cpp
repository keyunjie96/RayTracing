#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "Scene.h"
#include <limits>
using namespace std;

Scene::Scene()
{
	camera = new Camera;
}


Scene::~Scene()
{
	for (int i = 0; i < light.size(); ++i)
	{
		delete light[i];
	}
	for (int i = 0; i < obj.size(); ++i)
	{
		delete obj[i];
	}
}

void Scene::readObj(std::ifstream & fin)
{

	char cbuffer[50]; fin >> cbuffer; string buffer(cbuffer);
	if (buffer == "Sphere")
	{
		Object *oo = new Sphere;
		oo->read(fin);
		obj.push_back(oo);
	}
	else if (buffer == "Plane")
	{
		Object *oo = new Plane;
		oo->read(fin);
		obj.push_back(oo);
	}
	else if (buffer == "Box")
	{
		Object *oo = new Box;
		oo->read(fin);
		obj.push_back(oo);
	}
	else if (buffer == "Model")
	{
		Object *oo = new Model;
		oo->read(fin);
		obj.push_back(oo);
	}
}

void Scene::readLight(std::ifstream & fin)
{

	char cbuffer[50]; fin >> cbuffer; string buffer(cbuffer);
	
	if (buffer == "Point")
	{
		Light *ll = new PointLight;
		ll->read(fin);
		light.push_back(ll);

	}
	else if (buffer == "Plane")
	{
		Light *ll = new PlaneLight;
		ll->read(fin);
		light.push_back(ll);
	}
}

double Scene::GetNearestInterDist(const Ray & ray)
{
	double nearestDist = INT_MAX; int nearestIndex = 0, index = 0;
	for (auto obj_p : obj)
	{
		if (obj_p->CalIntersect(ray))
		{
			double dist = ray.rayPath.GetDist(obj_p->GetIntersection());
			if (dist < nearestDist)
			{
				nearestDist = dist; nearestIndex = index;
			}
			++index;
		}
		else
		{
			continue;
		}
	}
	return nearestDist;
}

int Scene::GetNearestInterIndex(const Ray & ray)
{
	double nearestDist = INT_MAX; int nearestIndex = -1, index = -1;
	for (auto obj_p : obj)
	{
		index++;
		if (obj_p->CalIntersect(ray))
		{
			double dist = obj_p->inter.interDist;
			if (dist < nearestDist)
			{
				nearestDist = dist; nearestIndex = index;
			}
		}
		else
		{
			continue;
		}
	}
	return nearestIndex;
}

Object * Scene::GetNearestObject(const Ray & ray)
{	
	int index = GetNearestInterIndex(ray);
	if (index >= 0)
		nearestObj = obj[index];
	else
		nearestObj = NULL;
	return nearestObj;
}

Color Scene::GetLightColor()
{
	if (nearestObj)
	{
		double ratio = 0;
		for (int i = 0; i < light.size(); ++i)
		{
			Object *obj = nearestObj;
			ratio += light[i]->calColor(nearestObj, *this);
			nearestObj = obj;
		}
		ratio /= light.size();
		return Color() * ratio;
	}
	else
		return Color(1,1,1);
}

Color Scene::GetBackgroundColor(const Ray & ray)
{
	return Color(0,0,0);
}

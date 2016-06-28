#include "Light.h"
#include "Object.h"
#include <math.h>
using namespace std;
const double epsilon = 1e-5;
const double pi = 3.142;
Light::Light()
{
}


Light::~Light()
{
}


PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::read(std::ifstream & fin)
{
	while (true)
	{
		char cbuffer[50]; fin >> cbuffer; string buffer(cbuffer);
		if (buffer == "x=")
		{
			lightPosi.read(fin);
		}
		else if (buffer == "end")
		{
			break;
		}
	}
}

double PointLight::calColor(Object *nearestObj, Scene& scene)
{
	double enRatio = 0; Inter inter = nearestObj->inter;
	Ray ray(inter.interPosi, lightPosi - inter.interPosi);
	Object* blockObj = scene.GetNearestObject(ray);
	double rayDist = ray.launchPoint.GetDist(lightPosi);
	if (blockObj && ((blockObj->inter.interDist > epsilon && blockObj->inter.interDist < rayDist)))
	{
	}
	else
	{
		double cosTheta = ray.rayPath.DotProduct(inter.axis);
		enRatio += fabs(cosTheta) * nearestObj->material->difReflectEnRatio;
		enRatio += pow(cosTheta, 50) * nearestObj->material->difSpecEnRatio;
	}
	nearestObj->inter = inter;
	return enRatio;
}


PlaneLight::PlaneLight()
{
}


PlaneLight::~PlaneLight()
{
}

void PlaneLight::read(std::ifstream & fin)
{
	while (true)
	{
		char cbuffer[50]; fin >> cbuffer; string buffer(cbuffer);
		if (buffer == "x=")
		{
			lightPosi.read(fin);
		}
		else if (buffer == "axis=")
		{
			axis_X.read(fin); axis_Y.read(fin);
		}
		else if (buffer == "end")
		{
			break;
		}
	}
}

double PlaneLight::calColor(Object * nearestObj, Scene & scene)
{
	Vector3 axis_X_unit = axis_X / 4, axis_Y_unit = axis_Y / 4;
	PointLight randLight; double ret = 0; 
	for(int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Vector3 lebtm = lightPosi + axis_X_unit * i + axis_Y_unit * j;
			for (int k = 0; k < 1; ++k)
			{
				Vector3 randPosi = lebtm;
				randPosi += axis_X_unit * ((double)rand() / RAND_MAX);
				randPosi += axis_Y_unit * ((double)rand() / RAND_MAX);
				randLight.lightPosi = randPosi;
				ret += randLight.calColor(nearestObj, scene);
			}
		}
	}
	return ret / 16;
}

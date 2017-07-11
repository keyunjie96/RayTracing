#pragma once
#include <vector>
#include <fstream>
#include "bmp.h"
#include "Color.h"
#include "Vector3.h"
#include "RayTrace.h"
class Camera
{
public:
	Camera();
	~Camera();
	void SetHW(int H, int W);
	void SetCameraPosi(int x, int y, int z);
	void read(std::ifstream & fin);
	void write();
	Bmp *bmp;
	int Image_H, Image_W;
	std::vector<std::vector<Color>> Picture;
	Vector3 CameraPosi; //我们假定照相平面为xz平面。y < 0, x z > 0
	void EmitRays();
	Ray EmitRay(double h, double w);
};


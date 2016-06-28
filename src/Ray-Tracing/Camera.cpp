#include <iostream>
#include "Camera.h"


using namespace std;

Camera::Camera()
{
	bmp = new Bmp;
}

Camera::~Camera()
{
	Picture.clear();
}

void Camera::SetHW(int H, int W)
{
	Picture.clear();
	Image_H = H; Image_W = W;
	for (int i = 0; i < Image_H; ++i)
	{
		vector<Color> rowColor;
		rowColor.resize(Image_W);
		Picture.push_back(rowColor);
	}
}

void Camera::SetCameraPosi(int x, int y, int z)
{
	CameraPosi = Vector3(x, y, z);
}

void Camera::read(std::ifstream & fin)
{
	while (true)
	{
		char cbuffer[50]; fin >> cbuffer; string buffer(cbuffer);
		if (buffer == "x=")
		{
			CameraPosi.read(fin);
		}
		else if (buffer == "HW=")
		{
			int H, W;
			fin >> H >> W;
			SetHW(H, W);
		}
		else if (buffer == "end")
		{
			break;
		}
	}
}

void Camera::write()
{
	bmp->Initialize(Image_H, Image_W);

	for (int i = 0; i < Image_H; i++)
		for (int j = 0; j < Image_W; j++)
			bmp->SetColor(i, j, Picture[i][j]);
}

void Camera::EmitRays()
{
	for (int i = 0; i < Image_H; ++i)
	{
		for (int j = 0; j < Image_W; ++j)
		{

		}
	}
}

Ray Camera::EmitRay(double h, double w)
{
	return Ray(CameraPosi, Vector3(w, 0, h) - CameraPosi);
}

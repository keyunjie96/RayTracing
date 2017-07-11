#include "Vector3.h"
#include "RayTrace.h"
#include "Object.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	RayTrace *rt = new RayTrace;
	Vector3 v1(400, -1000, 400), v2(796, 93, 122);
	Vector3 ray = v2 - v1; Vector3 axis(-0.79, -0.57, 0.21);
	ray = ray.GetRegulation();
	double ratio = 1.7;
	std::cout << ray.GetRefraction(axis, ratio) << std::endl;
	rt->Read(argv[1]);
	rt->Run();
	rt->Write(argv[2]);
	return 0;
}



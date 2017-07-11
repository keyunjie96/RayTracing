#pragma once
#include "Color.h"
#include "Vector3.h"
#include "RayTrace.h"
#include <assert.h>
#include <fstream>
class Bmp;
class Inter
{
public:
	Inter();
	~Inter();
	void SetInterPosi(const Vector3 & posi, const Ray & ray);
	Vector3 interPosi; double interDist; Vector3 axis;
	bool hasInterSection;
};
class Material
{
public:
	Material();
	~Material();
	Color color;
	Bmp *bmp;
	Vector3 bmpAxis1, bmpAxis2;
	double refractRatio;
	double reflectEnRatio, difReflectEnRatio, difSpecEnRatio, refractEnRatio;
};

class Object
{
public:
	Object();
	virtual ~Object();
	virtual void read(std::ifstream & fin) = 0;
	bool objectRead(std::string flag, std::ifstream & fin);
	virtual Color GetMaterialColor() = 0;
 	virtual bool CalIntersect(const Ray& ray) = 0;
	Vector3 GetIntersection();
	Ray GetReflection(const Ray & ray) const;
	Ray GetRefracion(const Ray & ray) const;
	Material *material;
	Inter inter;
};

class Sphere :
	public Object
{
public:
	Sphere();
	~Sphere();
	void read(std::ifstream & fin);
	Vector3 center;
	double radius;
	Color GetMaterialColor();
	bool CalIntersect(const Ray& ray);
};

class Plane :
	public Object
{
public:
	Plane();
	~Plane();
	void read(std::ifstream & fin);
	Vector3 angle; double d;
	Color GetMaterialColor();
	bool CalIntersect(const Ray& ray);
};

class Mesh :
	public Object
{
public:
	Mesh();
	~Mesh();
	Mesh(const Mesh & mesh);
	void read(std::ifstream & fin);
	Color GetMaterialColor();
	bool CalIntersect(const Ray& ray);
	std::vector<Vector3> points;
	Vector3 cg; double d; Vector3 edges[3];
};

class Box :
	public Object
{
public:
	Box();
	Box(Vector3 offset_, Vector3 length_);
	~Box();
	void read(std::ifstream & fin);
	Color GetMaterialColor();
	bool CalIntersect(const Ray& ray);
	Vector3 offset; Vector3 length;

};

class Node
{
public:
	Node();
	~Node();
	int leftChild, rightChild, parent;
	Box box;
	std::vector<int> meshesIndex;
};

class Box_
{
public:
	Box_();
	Box_(Vector3 offset_, Vector3 length_);
	bool CalIntersect(const Ray & ray);
	Vector3 offset;
	Vector3 length;
};

class Model :
	public Object
{
public:
	Model();
	~Model();
	void read(std::ifstream & fin); void GetMehes(std::string fileName);
	Color GetMaterialColor();
	bool CalIntersect(const Ray& ray);
	Vector3 offset; double largeRatio;


	void buildKDTree();
	void buildSubKDTree(int rootIndex, int axis, std::vector<int>& meshesIndex, std::vector<Mesh> & meshes);
	bool searchNode(int nodeIndex, const Ray & ray, std::vector<int> & suspectedMeshesIndex);
	std::vector<Node> nodes;
	std::vector<Mesh> meshes;
};
	



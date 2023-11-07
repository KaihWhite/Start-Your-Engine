#pragma once
class Quad
{
public:
	float* vertices;
	unsigned int * indices;
	//Quad(float*, unsigned int*)
	Quad(float*,unsigned int*);
	void load();
};


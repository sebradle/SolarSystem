#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Engine/ModelBatch.h>
class Rings
{
public:
	Rings(float day, float year, float orbit, float scale, GLuint texture);
	~Rings();

	void update();
	void draw(Engine::ModelBatch& batch, GLint modelID);

private:
	float mDay;
	float mYear;
	float mOrbit;
	float mScale;
	float mYr;
	float mDy;
	const float PI = 3.14159265358979323846;
	GLuint mTexture;

};


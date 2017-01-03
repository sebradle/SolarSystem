#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Engine/ModelBatch.h>

class Satellite 
{
public:
	Satellite(float planetYear, float planetOrbit, float distanceToPlanet, float moonYear , float moonDay, float scale, GLuint texture);
	virtual ~Satellite();
	void update();
	void draw(Engine::ModelBatch& batch, GLint modelID);
	float getDistance() { return distance; }
	float getMYr() { return mYr; }
	float getOrbit() { return pOrbit; }
	float getPYr() { return pYr; }

private:
	float pYear;
	float pOrbit;
	float distance;
	float mYear;
	float mDay;
	float mScale;
	float mYr;
	float mDy;
	float pYr;
	GLuint mTexture;

};


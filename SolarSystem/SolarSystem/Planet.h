#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Engine/ModelBatch.h>
#include <vector>

#include "Satellite.h"
#include "Rings.h"
#include <iostream>


class Planet
{
public:
	Planet(std::string planet, float day, float year, float orbit, float scale, GLuint texture);
	~Planet(); 
	void update();
	void draw(Engine::ModelBatch& batch, GLint modelID);
	void addMoon(float planetYear, float planetOrbit, float distanceToPlanet, float moonYear, float moonDay, float scale, GLuint texture);
	void addRings(float day, float year, float orbit, float scale, GLuint texture);

	std::string getName() { return mName; }
	float getOrbit() { return mOrbit; }
	float getYr() { return mYr; }
	Satellite* getMoons() { return moons.back(); }

private:
	std::string mName;
	float mDay;
	float mYear;
	float mOrbit;
	float mScale;
	float mYr;
	float mDy;
	GLuint mTexture;
	std::vector<Satellite*> moons;
	std::vector<Rings*> rings;

};


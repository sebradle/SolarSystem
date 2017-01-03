#include "Planet.h"
#include "AstroConstants.h"
#include <glm/gtc/matrix_transform.hpp>


Planet::Planet(std::string name, float day, float year, float orbit, float scale, GLuint texture) :
	mName(name),
	mDay(day),
	mYear(year),
	mOrbit(orbit),
	mScale(scale),
	mTexture(texture),
	mYr(0.0f),
	mDy(0.0f)
{
}

Planet::~Planet()
{
	for (int i = 0; i < rings.size(); i++) {
		delete rings[i];
	}

	for (int i = 0; i < moons.size(); i++) {
		delete moons[i];
	}
}

void Planet::update() {
	mYr += 1.0f / mYear;
	mDy += 0.1f / mDay;

	for (int i = 0; i < rings.size(); i++) {
		rings[i]->update();
	}
	for (int i = 0; i < moons.size(); i++) {
		moons[i]->update();
	}

	if (mYr > 2 * M_PI) {
		mYr -= 2 * M_PI;
	}
}

void Planet::draw(Engine::ModelBatch& batch , GLint modelID) {
	

	glm::mat4 yr = glm::rotate(glm::mat4(1.0), mYr, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::translate(yr, glm::vec3(mOrbit, 0.0f, 0.0f));
	yr = glm::rotate(yr, mDy, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::scale(yr, glm::vec3(mScale, mScale, mScale));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &yr[0][0]);
	batch.drawSphere(mTexture);

	glm::mat4 ln = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &ln[0][0]);
	batch.drawOrbit(mOrbit, mScale);

	for (int i = 0; i < rings.size(); i++) {
		rings[i]->draw(batch, modelID);
	}
	for (int i = 0; i < moons.size(); i++) {
		moons[i]->draw(batch, modelID);
	}
}


void Planet::addMoon(float planetYear, float planetOrbit, float distanceToPlanet, float moonYear, float moonDay, float scale, GLuint texture) {
	moons.push_back(new Satellite(planetYear, planetOrbit, distanceToPlanet, moonYear, moonDay, scale, texture));
}

void Planet::addRings(float day, float year, float orbit, float scale, GLuint texture) {
	rings.push_back(new Rings(day, year, orbit, scale, texture));
}
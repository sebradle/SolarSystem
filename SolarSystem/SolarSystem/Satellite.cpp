#include "Satellite.h"
#include <glm/gtc/matrix_transform.hpp>
#include "AstroConstants.h"


Satellite::Satellite(float planetYear, float planetOrbit, float distanceToPlanet, float moonYear, float moonDay, float scale, GLuint texture) :
	pYear(planetYear),
	pOrbit(planetOrbit),
	distance(distanceToPlanet),
	mYear(moonYear),
	mDay(moonDay),
	mScale(scale),
	mTexture(texture),
	mYr(0.0f),
	mDy(0.0f),
	pYr(0.0f)
{
}


Satellite::~Satellite()
{
}


void Satellite::update() {
	pYr += 1.0f / pYear;
	mDy += 0.1f / mDay;
	mYr += 1.0f / mYear;

	if (mYr > 2 * M_PI) {
		mYr -= 2 * M_PI;
	}

	if (pYr > 2 * M_PI) {
		pYr -= 2 * M_PI;
	}
}

void Satellite::draw(Engine::ModelBatch& batch, GLint modelID) {
	glm::mat4 ln = glm::rotate(glm::mat4(), pYr, glm::vec3(0.0f, 1.0f, 0.0f));
	ln = glm::translate(ln, glm::vec3(pOrbit, 0.0f, 0.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &ln[0][0]);
	batch.drawOrbit(distance, mScale);


	// Rotate around planet at rate mYr and a distance away
	glm::mat4 yr = glm::rotate(glm::mat4(1.0), pYr, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::translate(yr, glm::vec3(pOrbit, 0.0f, 0.0f));

	// Rotate around sun at rate pYr and a distance pOrbit away
	yr = glm::rotate(yr, mYr, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::translate(yr, glm::vec3(distance, 0.0f, 0.0f));

	// Rotate on your own axis at rate mDy
	yr = glm::rotate(yr, mDy, glm::vec3(0.0f, 1.0f, 0.0f));

	// Scale to size
	yr = glm::scale(yr, glm::vec3(mScale, mScale, mScale));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &yr[0][0]);
	batch.drawSphere(mTexture);
}

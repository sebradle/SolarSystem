#include "Rings.h"
#include <glm/gtc/matrix_transform.hpp>

Rings::Rings(float day, float year, float orbit, float scale, GLuint texture) :
	mDay(day),
	mYear(year),
	mOrbit(orbit),
	mScale(scale),
	mTexture(texture),
	mYr(0.0f),
	mDy(0.0f)
{
}


Rings::~Rings()
{
}


void Rings::update() {
	mYr += 1.0f / mYear;
	mDy += 0.1f / mDay;
}

void Rings::draw(Engine::ModelBatch& batch, GLint modelID) {
	glm::mat4 yr = glm::rotate(glm::mat4(1.0), mYr, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::translate(yr, glm::vec3(mOrbit, 0.0f, 0.0f));
	yr = glm::rotate(yr, mDy, glm::vec3(0.0f, 1.0f, 0.0f));
	yr = glm::scale(yr, glm::vec3(mScale * 2.0f, 0.1f, mScale * 2.0f));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &yr[0][0]);
	//batch.drawSphere(mTexture);

	double theta = 0.0;
	double textureY = 0.0;
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glBegin(GL_QUAD_STRIP);
	//set the ringInnerEdge and RingWidth according to our scale factors.
	double rie = 0.15 * mScale;
	double rw = 0.2 * mScale;
	for (theta = -PI; theta < PI; theta += PI / 32.0) {
		glTexCoord2d(0.0, textureY);
		glNormal3d(rie * cos(theta), 0, rie * sin(theta));
		glVertex3d(rie * cos(theta), 0, rie * sin(theta));
		glTexCoord2d(1.0, textureY);
		glNormal3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
		glVertex3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
		textureY += 1.0 / 32.0;
	}
	glTexCoord2d(0.0, 1.0);
	glNormal3d(rie * cos(theta), 0, rie * sin(theta));
	glVertex3d(rie * cos(theta), 0, rie * sin(theta));
	glTexCoord2d(0.0, 1.0);
	glNormal3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
	glVertex3d((rie + rw) * cos(theta), 0, (rie + rw) * sin(theta));
	glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}
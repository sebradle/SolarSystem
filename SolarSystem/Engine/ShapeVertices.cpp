#include "ShapeVertices.h"
#include <iostream>


namespace Engine {

	GLuint sphere(std::vector<Vertex>& vertices, GLuint slices, float radius) {
		Vertex vertex;
		const int SPHERE_VERTS = (slices * VERTICES_QUAD * (slices - 2)) + (slices * VERTICES_TRI * 2);
		vertices.resize(SPHERE_VERTS);


		int index = 0;
		float phi_top = ((float)((slices / 2) - 1) / (float)(slices / 2)) * PI / 2.0;
		float phi_bot = -phi_top;

		for (int n = 0; n < slices; n++)
		{
			GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
			GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0, MODEL_TOP, 0.0);
			vertices[index].setUV(0.0, 0.0);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_top) * cos(THETA_0) * radius, sin(phi_top) * radius, cos(phi_top) * sin(THETA_0) * radius);
			vertices[index].setUV(THETA_0 / (2 * PI), -(phi_top - PI/2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_top) * cos(THETA_1) * radius, sin(phi_top) * radius, cos(phi_top) * sin(THETA_1) * radius);
			vertices[index].setUV(THETA_1 / (2 * PI), -(phi_top - PI / 2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
		}

		for (int m = 1; m < slices - 1; m++)
		{
			float phi_0 = PI / 2.0 - m * PI / (float)slices;
			float phi_1 = PI / 2.0 - (m + 1) * PI / (float)slices;

			int num;
			for (int n = 0; n < slices; n++)
			{
				num = 0;
				float x = 0.0, y = 0.0, r = 0.5;

				GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
				GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

				// top left
				vertices[index].setPosition(cos(phi_1)*cos(THETA_0) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// top right
				vertices[index].setPosition(cos(phi_1)*cos(THETA_1) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom right
				vertices[index].setPosition(cos(phi_0)*cos(THETA_1) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// top left
				vertices[index].setPosition(cos(phi_1)*cos(THETA_0) * radius, sin(phi_1) * radius, cos(phi_1)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_1 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom right
				vertices[index].setPosition(cos(phi_0)*cos(THETA_1) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_1) * radius);
				vertices[index].setUV(THETA_1 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

				// bottom left
				vertices[index].setPosition(cos(phi_0)*cos(THETA_0) * radius, sin(phi_0) * radius, cos(phi_0)*sin(THETA_0) * radius);
				vertices[index].setUV(THETA_0 / (2 * PI), -(phi_0 - PI / 2.0f) / PI);
				vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
			}
		}

		for (int n = 0; n < slices; n++)
		{
			GLfloat const THETA_0 = 2 * PI * (float)n / (float)slices;
			GLfloat const THETA_1 = 2 * PI * (float)(n + 1) / (float)slices;

			vertices[index].setPosition(0.0, MODEL_BOT, 0.0);
			vertices[index].setUV(0.0, 1.0);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_bot) * cos(THETA_0) * radius, sin(phi_bot) * radius, cos(phi_bot) * sin(THETA_0) * radius);
			vertices[index].setUV(THETA_0 / (2 * PI), -(phi_bot - PI / 2.0f) / PI);
			vertices[index++].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);

			vertices[index].setPosition(cos(phi_bot) * cos(THETA_1) * radius, sin(phi_bot) * radius, cos(phi_bot) * sin(THETA_1) * radius);
			vertices[index].setUV(THETA_1 / (2 * PI), -(phi_bot - PI / 2.0f) / PI);
			vertices[index].setNormal(vertices[index].position.x, vertices[index].position.y, vertices[index].position.z);
		}

		return SPHERE_VERTS;
	}

	GLuint cube(std::vector<Vertex>& vertices) {
		Vertex vertex;
		vertices.resize(36);

		glm::vec3 vert[8] = {
			glm::vec3(0.5, 0.5, 0.5),
			glm::vec3(-0.5, 0.5, 0.5),
			glm::vec3(-0.5, -0.5, 0.5),
			glm::vec3(-0.5, -0.5, -0.5),
			glm::vec3(-0.5, 0.5, -0.5),
			glm::vec3(0.5, -0.5, 0.5),
			glm::vec3(0.5, -0.5, -0.5),
			glm::vec3(0.5, 0.5, -0.5)
		};

		return 0;
	}

	GLuint torus(std::vector<Vertex>& vertices, GLuint numVertices) {
		return 0;
	}

	GLuint cylinder(std::vector<Vertex>& vertices, GLuint slices) {
		return 0;
	}
}
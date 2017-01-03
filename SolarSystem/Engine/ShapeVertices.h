#pragma once
#include <vector>
#include "Vertex.h"

namespace Engine {
	extern GLuint sphere(std::vector<Vertex>& vertices, GLuint slices, float radius);
	extern GLuint cube(std::vector<Vertex>& vertices);
	extern GLuint torus(std::vector<Vertex>& vertices, GLuint numVertices);
	extern GLuint cylinder(std::vector<Vertex>& vertices, GLuint numVertices);

	const int VERTICES_QUAD = 6;
	const int VERTICES_TRI = 3;
	const float PI = 3.14159265358979323846;
	const float MODEL_TOP = 0.5;
	const float MODEL_BOT = -0.5;
}
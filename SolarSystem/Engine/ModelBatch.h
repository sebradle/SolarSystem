#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "ShapeVertices.h"

namespace Engine {

	class RenderBatch {
		public:
			RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
			GLuint offset;
			GLuint numVertices;
			GLuint texture;
	};


	class ModelBatch
	{
	public:
		ModelBatch();
		~ModelBatch();

		void init();

		void drawSphere(GLuint texture);
		void drawCube(GLuint texture);
		void drawOrbit(float distance, float scale);

	private:

		GLuint mVBO;
		GLuint mVAO;
		
		size_t cubeOffset, cylinderOffset, sphereOffset, torusOffset;

		std::vector<Vertex> mCubeBuffer;
		std::vector<Vertex> mCylinderBuffer;
		std::vector<Vertex> mSphereBuffer;
		std::vector<Vertex> mTorusBuffer;

		const int mCubeVertices = 36;
		int mCylinderVertices = 0;
		int mSphereVertices = 0;
		int mTorusVertices = 0;

		size_t CUBE_OFFSET;
		size_t CYLINDER_OFFSET;
		size_t SPHERE_OFFSET;
		size_t TORUS_OFFSET;


	};
}


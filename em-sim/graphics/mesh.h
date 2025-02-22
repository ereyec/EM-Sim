#ifndef MESH_H
#define MESH_H

#include "../context.h"
#include "../common.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct quadMesh{
	inline static glm::vec3 v1 = glm::vec3(-1.0f, 1.0f, 0.0f);
	inline static glm::vec3 v2 = glm::vec3(1.0f, 1.0f, 0.0f);
	inline static glm::vec3 v3 = glm::vec3(-1.0f, -1.0f, 0.0f);
	inline static glm::vec3 v4 = glm::vec3(1.0f, -1.0f, 0.0f);
	inline static glm::vec2 t1 = glm::vec2(0, 1);
	inline static glm::vec2 t2 = glm::vec2(1, 1);
	inline static glm::vec2 t3 = glm::vec2(0, 0);
	inline static glm::vec2 t4 = glm::vec2(1, 0);
};

void meshQuad(Context& context){
	pushV3T2(context.quadVertexData, quadMesh::v1, quadMesh::t1);
	pushV3T2(context.quadVertexData, quadMesh::v2, quadMesh::t2);
	pushV3T2(context.quadVertexData, quadMesh::v3, quadMesh::t3);
	pushV3T2(context.quadVertexData, quadMesh::v2, quadMesh::t2);
	pushV3T2(context.quadVertexData, quadMesh::v3, quadMesh::t3);
	pushV3T2(context.quadVertexData, quadMesh::v4, quadMesh::t4);

	glGenVertexArrays(1, &context.qVAO);
	glGenBuffers(1, &context.qVBO);
	glBindVertexArray(context.qVAO);
	glBindBuffer(GL_ARRAY_BUFFER, context.qVBO);
	glBufferData(GL_ARRAY_BUFFER, context.quadVertexData.size() * sizeof(float), 	context.quadVertexData.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

#endif


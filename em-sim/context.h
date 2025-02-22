#ifndef CONTEXT_H
#define CONTEXT_H

#include <iostream>
#include <vector>
#include "../include/engine/Camera.h"
#include "../include/engine/Shader.h"
#include "../include/engine/Texture.h"

/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Context{
	GLFWwindow* window = nullptr;	

	unsigned int windowWidth = 1200;
	unsigned int windowHeight = 900;
	std::string windowName = "EM-Sim";

	std::vector<float> quadVertexData; //use: main rendering

	unsigned int qVAO;
	unsigned int qVBO;

	Shader textureShader;

	Texturef fieldTextureEx;
};

Context context;

#endif
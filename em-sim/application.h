#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "context.h"
#include "common.h"

#include "./simulator/solver.h"
#include "./graphics/fieldExTexture.h"
#include "./graphics/mesh.h"

class Application{
public:
	Application(){}
	
	int init(Context& context);
	void run(Context& context);
	void cleanup(Context& context);
};

int Application::init(Context& context){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	context.window = glfwCreateWindow(context.windowWidth, context.windowHeight, context.windowName.c_str(), nullptr, nullptr);
	if(context.window == nullptr){
		std::cout << "Window could not be created. " << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(context.window);
	glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        	std::cout << "Failed to initialize GLAD. " << std::endl;
        	return -1;
    	}
	
	context.textureShader = Shader("./em-sim/graphics/shaders/tVertex.vs", "./em-sim/graphics/shaders/tFragment.fs", true);
	context.fieldTextureEx = Texturef(200, 200); //!!!
	context.fieldTextureEx.data = (float*)malloc(200 * 200 * 4 * sizeof(float)); //!!!
	
	return 0;
}

void Application::run(Context& context){
	simulationParams sp = {200, 1, 200, 0.01, 0.01, 0.01, 0.0005}; //0.0005
	simulationState ss(sp);	
	meshQuad(context);

while (!glfwWindowShouldClose(context.window)){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.227f, 0.4f, 0.6f, 1.0f);
	
	solveSingleIteration(sp, ss); //update simulation
	updateFieldExTexture(ss, context); //update texture

	//use program, set uniforms
	glUseProgram(context.textureShader.ID);
	glBindTexture(GL_TEXTURE_2D, context.fieldTextureEx.ID);
	glUniform1i(glGetUniformLocation(context.textureShader.ID, "ourTexture"), 0);

	//bind texture, draw arrays
	glBindVertexArray(context.qVAO);
	glDrawArrays(GL_TRIANGLES, 0, context.quadVertexData.size() / 5);

	glfwSwapBuffers(context.window);
        glfwPollEvents();
}

}

void Application::cleanup(Context& context){

}

#endif
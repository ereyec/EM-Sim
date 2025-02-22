#ifndef FIELDEXTEXTURE_H
#define FIELDEXTEXTURE_H

#include "../context.h"
#include "../common.h"

void updateFieldExTexture(simulationState& ss, Context& context){
for(int z = 0; z < 200; z++){ for(int x = 0; x < 200; x++){
	int index = (200 * z + x) * 4;
	float fieldValue = ss.yeeGrid.getCell(x,0,z).ex.current;

	glm::vec3 color = glm::vec3(0,0,0);
	if(fieldValue >= 0){
		float ExClamped = glm::clamp(fieldValue, 0.f, 100.f);
		float lerpT = ExClamped / 100.f;
		float blue = 1 - lerpT;
		float red = lerpT;
		color = glm::vec3(red, 0, blue);
		
	}else{
		float ExClamped = glm::clamp(fieldValue, -100.f, 0.f);
		float lerpT = ExClamped / -100.f;
		float blue = 1 - lerpT;
		float green = lerpT;
		color = glm::vec3(0, green, blue);
	}

	context.fieldTextureEx.data[index] = color.x;
	context.fieldTextureEx.data[index + 1] = color.y;
	context.fieldTextureEx.data[index+ 2] = color.z;
	context.fieldTextureEx.data[index+ 3] = 1.f;
}}
	//buffer texture data:
	glBindTexture(GL_TEXTURE_2D, context.fieldTextureEx.ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 200, 200, 0, GL_RGBA, GL_FLOAT, context.fieldTextureEx.data);
	glBindTexture(GL_TEXTURE_2D, 0);

}

#endif

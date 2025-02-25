#ifndef FIELDTEXTURE_H
#define FIELDTEXTURE_H

void updateFieldTexture(Context& context, simulationParams& sp, simulationState& ss){
const int nrChannels = 4;
glm::vec3 blue = glm::vec3(0,0,1);
Texturef fieldTextureXZ(sp.x * 2, sp.z * 2);
fieldTextureXZ.data = (float*)malloc(sp.x * 2 * sp.z * 2 * nrChannels * sizeof(float));

//XZ texture layout per yee grid cell
//[   ][Ex]
//[Ez][Hy]

//This will probably be too slow to run at a reasonable pace, in that case we could switch to compute shaders
//for both the simulator and texture writes.
//Fill the texture:
for(int z = 0; z < sp.z; z++){ for(int x = 0; x < sp.x; x++){
	int zSlice = sp.x*4*4;
	int zHalfSlice = sp.x*2*4;
	int xJump = 8;
	int xHalfJump = 4;
	int index00 = fieldTextureXZ.data[zSlice * z + xJump * x];
	int index10 = fieldTextureXZ.data[zSlice * z + xJump * x + xHalfJump];
	int index01 = fieldTextureXZ.data[zSlice * z + xJump * x + zHalfSlice];
	int index11 = fieldTextureXZ.data[zSlice * z + xJump * x + zHalfSlice + xHalfJump];

	bool containsMaterial = !materialGrid.grid[sp.z * z + sp.x * x + sp.y * 0].empty;

	if(!containsMaterial){
		fieldTextureXZ.data[index00] = blue.x;
		fieldTextureXZ.data[index00++] = blue.y;
		fieldTextureXZ.data[index00++] = blue.z;
		fieldTextureXZ.data[index00++] = 1.0f;
	}else{
		fieldTextureXZ.data[index00] = 1.0f;
		fieldTextureXZ.data[index00++] = 1.0f;
		fieldTextureXZ.data[index00++] = 1.0f;
		fieldTextureXZ.data[index00++] = 1.0f;
	}

	float ExClamped = glm::clamp(yeeGrid(x, 0, z).Ex.current, 0, 100);
	float lerpVal = ExClamped / 100.f;
	float blue = 1 - lerpVal;
	float red = lerpVal;
	glm::vec3 color10 = glm::vec3(red, 0, blue);
	
	fieldTextureXZ.data[index10] = color10.x;
	fieldTextureXZ.data[index10++] = color10.y;
	fieldTextureXZ.data[index10++] = color10.z;
	fieldTextureXZ.data[index10++] = 1.0f;

	float EzClamped = glm::clamp(yeeGrid(x, 0, z).Ez.current, 0, 100);
	lerpVal = EzClamped / 100.f;
	blue = 1 - lerpVal;
	red = lerpVal;
	glm::vec3 color01 = glm::vec3(red, 0, blue);

	fieldTextureXZ.data[index01] = color01.x;
	fieldTextureXZ.data[index01++] = color01.y;
	fieldTextureXZ.data[index01++] = color01.z;
	fieldTextureXZ.data[index01++] = 1.0f;

	float HyClamped = glm::clamp(yeeGrid(x, 0, z).Hy.current, 0, 100);
	lerpVal = HyClamped / 100.f;
	blue = 1 - lerpVal;
	float green = lerpVal;
	glm::vec3 color11 = glm::vec3(0, green, blue);

	fieldTextureXZ.data[index11] = color11.x;
	fieldTextureXZ.data[index11++] = color11.y;
	fieldTextureXZ.data[index11++] = color11.z;
	fieldTextureXZ.data[index11++] = 1.0f;
}}

glBindTexture(GL_TEXTURE_2D, context.fieldTextureXZ.ID);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, sp.x, sp.z, 0, GL_RGBA, GL_FLOAT, context.fieldTextureXZ.data); //!!! did you mean sp.x * 2?
glBindTexture(GL_TEXTURE_2D, 0);

}
#endif
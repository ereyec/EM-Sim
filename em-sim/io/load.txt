//Loading a grid workspace
int xDim, yDim, zDim;

FILE* projectFile;
std::string filename;
projectFile = fopen(filename.c_str(), "r");
fscanf("%d %d %d ", &xDim, &yDim, &zDim);
while(!feof(projectFile)){
	float e, o, u;
	int empty;
	fscanf("%f %f %f %d", &e, &o, &u, &empty);
	materialCell mc = {e, o, u, empty};
	materialGrid.push_back(mc);
}

if(materialGrid.size() != xDim * yDim * zDim){
	std::cout << "Dimension mismatch between file content size and dimensions " << std::endl;
	return -1;
}
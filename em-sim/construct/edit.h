//SETTINGS: Brush / eraser
double mouseXCurrent = 0.0;
double mouseYCurrent = 0.0;
int leftbuttonStateCurrent = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
int leftbuttonStateLast;

if(leftbuttonStateCurrent == GLFW_PRESS && 1){
	glfwGetCursorPos(window, &mouseXCurrent, &mouseYCurrent);
	//suppose grid size is 200,200 and window size is 800,600
	float xPercentage = mouseXCurrent / 800.0;
	float yPercentage = mouseYCurrent / 600.0;
	int xIndex = glm::floor(glm::clamp(xPercentage * 200, 0, 199));
	int yIndex = glm::floor(glm::clamp(yPercentage * 200, 0, 199));

	//Brush
	materialGrid(xIndex, 0, yIndex).materialCell = {materialSelection::e, materialSelection::o, materialSelection::u, 0};
	
	//also update the Yee grid:	!!! indexing may be wrong!
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ex.invPermittivity = 1/materialSelection::e;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ex.conductivity = materialSelection::o;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ey.invPermittivity = 1/materialSelection::e;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ey.conductivity = materialSelection::o;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ez.invPermittivity = 1/materialSelection::e;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ez.conductivity = materialSelection::o;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hx.permeability = materialSelection::u;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hy.permeability = materialSelection::u;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hz.permeability = materialSelection::u;

	//Eraser:
	materialGrid(xIndex,0, yIndex).materialCell = {8.854e-12, 0, 12.56e-7, 1};

	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ex.invPermittivity = 1/8.854e-12;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ex.conductivity = 0;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ey.invPermittivity = 1/8.854e-12;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ey.conductivity = 0;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ez.invPermittivity = 1/8.854e-12;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Ez.conductivity = 0;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hx.permeability = 12.56e-7;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hy.permeability = 12.56e-7;
	yeeGrid.grid[sp.z * yIndex + sp.x * xIndex].Hz.permeability = 12.56e-7;
	
}

//Potential issue: click being activated when we wanted to click an imgui component
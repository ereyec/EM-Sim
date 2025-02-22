#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H

#include "../context.h"
#include "../common.h"

//Simple Damping Layer - function to be called in the spatial for loop
void applyDampingLayer(simulationState& ss, simulationParams& sp, int x, int y, int z){
//Right boundary
if(x == 199){

	float Ex = ss.yeeGrid.getCell(x,y,z).ex.last - (sp.dt/sp.dx)*(ss.yeeGrid.getCell(x,y,z).ex.current - ss.yeeGrid.getCell(x-1,y,z).ex.current);
	float Ey = ss.yeeGrid.getCell(x,y,z).ey.last - (sp.dt/sp.dx)*(ss.yeeGrid.getCell(x,y,z).ey.current - ss.yeeGrid.getCell(x-1,y,z).ey.current);
	float Ez = ss.yeeGrid.getCell(x,y,z).ez.last - (sp.dt/sp.dx)*(ss.yeeGrid.getCell(x,y,z).ez.current - ss.yeeGrid.getCell(x-1,y,z).ez.current);

	ss.yeeGrid.setCellEx(x,y,z, Ex);
	ss.yeeGrid.setCellEy(x,y,z, Ey);
	ss.yeeGrid.setCellEz(x,y,z, Ez);
	
	//float t = 1.f - (200.f - x) / 20.f;
	//float sigma = glm::mix(0, 6000, t);
	
	//ss.yeeGrid.setCellEx(x, y, z, ss.yeeGrid.getCell(x,y,z).ex.current * std::exp(-sigma * 0.0005f));
	//ss.yeeGrid.setCellEy(x, y, z, ss.yeeGrid.getCell(x,y,z).ey.current * std::exp(-sigma * 0.0005f));
	//ss.yeeGrid.setCellEz(x, y, z, ss.yeeGrid.getCell(x,y,z).ez.current * std::exp(-sigma * 0.0005f));
	//ss.yeeGrid.setCellHx(x, y, z, ss.yeeGrid.getCell(x,y,z).hx.current * std::exp(-sigma * 0.0005f));
	//ss.yeeGrid.setCellHy(x, y, z, ss.yeeGrid.getCell(x,y,z).hy.current * std::exp(-sigma * 0.0005f));
	//ss.yeeGrid.setCellHz(x, y, z, ss.yeeGrid.getCell(x,y,z).hz.current * std::exp(-sigma * 0.0005f));
}

}
#endif

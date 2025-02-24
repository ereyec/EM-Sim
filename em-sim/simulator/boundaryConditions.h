#ifndef BOUNDARYCONDITIONS_H
#define BOUNDARYCONDITIONS_H

#include "../context.h"
#include "../common.h"


//Engquist Majda Boundary Condition

void applyEngquistMajda(simulationState& ss, simulationParams& sp, int x, int y, int z){
	//Ex at the left boundary (x = 0)
	//Note: current means at the current time n, last means at time n - 1.

	float unp1ip1 = 1.5*ss.yeeGrid.getCell(x+1,y,z).ex.current - 0.5*ss.yeeGrid.getCell(x+1,y,z).ex.last; //u^n+1_i+1
	float unp1im1 = 1.5*ss.yeeGrid.getCell(x-1,y,z).ex.current - 0.5*ss.yeeGrid.getCell(x-1,y,z).ex.last; //u^n+1_i-1

	float d2udxdt = (unp1ip1 - unp1im1 - ss.yeeGrid.getCell(x+1,y,z).ex.last + ss.yeeGrid.getCell(x-1,y,z).ex.last)/(4*sp.dx*sp.dt);
	float d2udy2 = (ss.yeeGrid.getCell(x,y+1,z).ex.current - 2*ss.yeeGrid.getCell(x,y,z).ex.current + ss.yeeGrid.getCell(x,y-1,z).ex.current)/(sp.dy*sp.dy);
	float d2udz2 = (ss.yeeGrid.getCell(x,y,z+1).ex.current - 2*ss.yeeGrid.getCell(x,y,z).ex.current + ss.yeeGrid.getCell(x,y,z-1).ex.current)/(sp.dz*sp.dz);

	float Ex_updated = d2udxdt*sp.dt*sp.dt + d2udy2*sp.dt*sp.dt + d2udz2*sp.dt*sp.dt + 2*ss.yeeGrid.getCell(x,y,z).ex.current - ss.yeeGrid.getCell(x,y,z).ex.last;

	ss.yeeGrid.setCellEx(x, y, z, Ex_updated);
	
	
	//Ey at the left boundary (x = 0)
	//Note: current means at the current time n, last means at time n - 1.

	unp1ip1 = 1.5*ss.yeeGrid.getCell(x+1,y,z).ey.current - 0.5*ss.yeeGrid.getCell(x+1,y,z).ey.last; //u^n+1_i+1
	unp1im1 = 1.5*ss.yeeGrid.getCell(x-1,y,z).ey.current - 0.5*ss.yeeGrid.getCell(x-1,y,z).ey.last; //u^n+1_i-1

	d2udxdt = (unp1ip1 - unp1im1 - ss.yeeGrid.getCell(x+1,y,z).ey.last + ss.yeeGrid.getCell(x-1,y,z).ey.last)/(4*sp.dx*sp.dt);
	d2udy2 = (ss.yeeGrid.getCell(x,y+1,z).ey.current - 2*ss.yeeGrid.getCell(x,y,z).ey.current + ss.yeeGrid.getCell(x,y-1,z).ey.current)/(sp.dy*sp.dy);
	d2udz2 = (ss.yeeGrid.getCell(x,y,z+1).ey.current - 2*ss.yeeGrid.getCell(x,y,z).ey.current + ss.yeeGrid.getCell(x,y,z-1).ey.current)/(sp.dz*sp.dz);

	float Ey_updated = d2udxdt*sp.dt*sp.dt + d2udy2*sp.dt*sp.dt + d2udz2*sp.dt*sp.dt + 2*ss.yeeGrid.getCell(x,y,z).ey.current - ss.yeeGrid.getCell(x,y,z).ey.last;

	ss.yeeGrid.setCellEy(x, y, z, Ey_updated);


	//Ez at the left boundary (x = 0)
	//Note: current means at the current time n, last means at time n - 1.

	unp1ip1 = 1.5*ss.yeeGrid.getCell(x+1,y,z).ez.current - 0.5*ss.yeeGrid.getCell(x+1,y,z).ez.last; //u^n+1_i+1
	unp1im1 = 1.5*ss.yeeGrid.getCell(x-1,y,z).ez.current - 0.5*ss.yeeGrid.getCell(x-1,y,z).ez.last; //u^n+1_i-1

	d2udxdt = (unp1ip1 - unp1im1 - ss.yeeGrid.getCell(x+1,y,z).ez.last + ss.yeeGrid.getCell(x-1,y,z).ez.last)/(4*sp.dx*sp.dt);
	d2udy2 = (ss.yeeGrid.getCell(x,y+1,z).ez.current - 2*ss.yeeGrid.getCell(x,y,z).ez.current + ss.yeeGrid.getCell(x,y-1,z).ez.current)/(sp.dy*sp.dy);
	d2udz2 = (ss.yeeGrid.getCell(x,y,z+1).ez.current - 2*ss.yeeGrid.getCell(x,y,z).ez.current + ss.yeeGrid.getCell(x,y,z-1).ez.current)/(sp.dz*sp.dz);

	float Ez_updated = d2udxdt*sp.dt*sp.dt + d2udy2*sp.dt*sp.dt + d2udz2*sp.dt*sp.dt + 2*ss.yeeGrid.getCell(x,y,z).ez.current - ss.yeeGrid.getCell(x,y,z).ez.last;

	ss.yeeGrid.setCellEz(x, y, z, Ez_updated);
			
}

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

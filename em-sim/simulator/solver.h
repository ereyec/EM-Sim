#ifndef SOLVER_H
#define SOLVER_H

#include <cmath>

#include "../io/save.h"
#include "./boundaryConditions.h"

//FDTD
void updateEComponents(simulationParams& sp, simulationState& ss, int x, int y, int z){
	float dHx, dHy, dHz;

	//Ex
	dHz = ss.yeeGrid.getCell(x,y,z).hz.current - ss.yeeGrid.getCell(x,y-1,z).hz.current;
	dHy = ss.yeeGrid.getCell(x,y,z).hy.current - ss.yeeGrid.getCell(x,y,z-1).hy.current;
	float Ex = ss.yeeGrid.getCell(x,y,z).ex.last + ss.yeeGrid.getCell(x,y,z).ex.invPermittivity
*((sp.dt/sp.dy)*(dHz) - (sp.dt/sp.dz)*(dHy) -ss.yeeGrid.getCell(x,y,z).ex.conductivity *ss.yeeGrid.getCell(x,y,z).ex.last);
	ss.yeeGrid.setCellEx(x,y,z,Ex);

	//Ey
	dHx = ss.yeeGrid.getCell(x,y,z).hx.current - ss.yeeGrid.getCell(x,y,z-1).hx.current;
	dHz = ss.yeeGrid.getCell(x,y,z).hz.current - ss.yeeGrid.getCell(x-1,y,z).hz.current;	
	float Ey = ss.yeeGrid.getCell(x,y,z).ey.last + ss.yeeGrid.getCell(x,y,z).ey.invPermittivity
	*( (sp.dt/sp.dz)*(dHx) - (sp.dt/sp.dx)*(dHz) - ss.yeeGrid.getCell(x,y,z).ey.conductivity *ss.yeeGrid.getCell(x,y,z).ey.last);
	ss.yeeGrid.setCellEy(x,y,z,Ey);

	//Ez
	dHy = ss.yeeGrid.getCell(x,y,z).hy.current - ss.yeeGrid.getCell(x-1,y,z).hy.current;
	dHx = ss.yeeGrid.getCell(x,y,z).hx.current - ss.yeeGrid.getCell(x,y-1,z).hx.current;
	float Ez = ss.yeeGrid.getCell(x,y,z).ez.last + ss.yeeGrid.getCell(x,y,z).ez.invPermittivity
	*( (sp.dt/sp.dx)*(dHy) - (sp.dt/sp.dy)*(dHx) - ss.yeeGrid.getCell(x,y,z).ez.conductivity*ss.yeeGrid.getCell(x,y,z).ez.last);
	ss.yeeGrid.setCellEz(x,y,z,Ez);


	//Setting all lasts to current
	YeeTrihedralCell ytc = ss.yeeGrid.getCell(x, y, z);

	ss.yeeGrid.setCellExLast(x, y, z, ytc.ex.current);
	ss.yeeGrid.setCellEyLast(x, y, z, ytc.ey.current);
	ss.yeeGrid.setCellEzLast(x, y, z, ytc.ez.current);

}

void updateHComponents(simulationParams& sp, simulationState& ss, int x, int y, int z){
	//Hx
	float dEx, dEy, dEz;

	dEy = ss.yeeGrid.getCell(x,y,z+1).ey.current - ss.yeeGrid.getCell(x,y,z).ey.current;
	dEz = ss.yeeGrid.getCell(x,y+1,z).ez.current - ss.yeeGrid.getCell(x,y,z).ez.current;
	float Hx = ss.yeeGrid.getCell(x,y,z).hx.last + (1/ss.yeeGrid.getCell(x,y,z).hx.permeability)
	*( (sp.dt/sp.dz)*dEy - (sp.dt/sp.dy)*dEz );
	ss.yeeGrid.setCellHx(x,y,z,Hx);

	//Hy
	dEz = ss.yeeGrid.getCell(x+1,y,z).ez.current - ss.yeeGrid.getCell(x,y,z).ez.current;
	dEx = ss.yeeGrid.getCell(x,y,z+1).ex.current - ss.yeeGrid.getCell(x,y,z).ex.current;
	float Hy = ss.yeeGrid.getCell(x,y,z).hy.last + (1/ss.yeeGrid.getCell(x,y,z).hy.permeability)
	*( (sp.dt/sp.dx)*dEz - (sp.dt/sp.dz)*dEx);
	ss.yeeGrid.setCellHy(x,y,z,Hy);

	//Hz
	dEx = ss.yeeGrid.getCell(x,y+1,z).ex.current - ss.yeeGrid.getCell(x,y,z).ex.current;
	dEy = ss.yeeGrid.getCell(x+1,y,z).ey.current - ss.yeeGrid.getCell(x,y,z).ey.current;	
	float Hz = ss.yeeGrid.getCell(x,y,z).hz.last + (1/ss.yeeGrid.getCell(x,y,z).hz.permeability)
	*( (sp.dt/sp.dy)*dEx - (sp.dt/sp.dx)*dEy);
	ss.yeeGrid.setCellHz(x,y,z,Hz);
	
	//Setting all lasts to current
	YeeTrihedralCell ytc = ss.yeeGrid.getCell(x, y, z);

	ss.yeeGrid.setCellHxLast(x, y, z, ytc.hx.current);
	ss.yeeGrid.setCellHyLast(x, y, z, ytc.hy.current);
	ss.yeeGrid.setCellHzLast(x, y, z, ytc.hz.current);
}


void solveSingleIteration(simulationParams& sp, simulationState& ss){
//hard sourcing a wave
if(ss.step < 50){
float Emax = 2000.f;
float omega = 200.f;
float E = Emax*std::cos(omega * ss.time);
ss.yeeGrid.setCellEx(100, 0, 40, E);
//ss.yeeGrid.setCellEy(100, 0, 100, E);
//ss.yeeGrid.setCellEz(100, 0, 100, E);
}

float energy = 0.0f;

for(int z = 0; z < sp.z; z++){
for(int x = 0; x < sp.x; x++){
for(int y = 0; y < sp.y; y++){		

	//YeeTrihedralCell ytc = ss.yeeGrid.getCell(x,y,z);
	//energy += 0.5*ytc.ex.current*ytc.ex.current + 0.5*ytc.hx.current*ytc.hx.current;
	//energy += 0.5*ytc.ex.current*ytc.ey.current + 0.5*ytc.hx.current*ytc.hy.current;
	//energy += 0.5*ytc.ex.current*ytc.ez.current + 0.5*ytc.hx.current*ytc.hz.current;

	//Leapfrog mechanism:
	if(ss.step%2 == 0){
		updateEComponents(sp, ss, x, y, z);
		if (x == 199){
			applyEngquistMajda(ss, sp, x, y, z);
		}
	}
	else{
		updateHComponents(sp, ss, x, y, z);
	}		
	
	
}}}
ss.step++;
ss.time += sp.dt;

//std::cout << "total energy: " << energy << std::endl;

//write to file
/*if(ss.step > 2004 || ss.step == 5) 
{saveSimOutputEx(sp, ss);}*/
}

#endif

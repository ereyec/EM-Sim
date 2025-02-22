#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include <iostream>
#include <string>

//Save Ex
int saveSimOutputEx(simulationParams& sp, simulationState& ss){
	std::string filename = "Sim-Output-Ex-step" + std::to_string(ss.step) + ".csv";
	FILE* outputFile;
	outputFile = fopen(filename.c_str(), "w");
	if(outputFile == NULL){
		std::cout << "Could not write to file " << std::endl;
		return -1;	
	}
	for(int z = 0; z < sp.z; z++){ for(int x = 0; x < sp.x; x++){
		fprintf(outputFile, "%f, ", ss.yeeGrid.getCell(x,0,z).ex.current);
	}
		fprintf(outputFile, "%f\n", ss.yeeGrid.getCell(sp.x-1, 0, z).ex.current);
	}
	fclose(outputFile);
	std::cout << "File Ex has been written " << std::endl;
	return 0;
}


//Save Ey
int saveSimOutputEy(simulationParams& sp, simulationState& ss){
	std::string filename = "Sim-Output-Ey-step" + std::to_string(ss.step) + ".csv";
	FILE* outputFile;
	outputFile = fopen(filename.c_str(), "w");
	if(outputFile == NULL){
		return -1;
	}
	for(int z = 0; z < sp.z; z++){ for(int x = 0; x <= sp.x; x++){
		fprintf(outputFile, "%f, ", ss.yeeGrid.getCell(x, 0, z).ey.current);
	}
		fprintf(outputFile, "%f\n", ss.yeeGrid.getCell(sp.x-1, 0, z).ey.current);
	}
	fclose(outputFile);
	std::cout << "File Ey has been written " << std::endl;
	return 0;
}

//Save Ez
int saveSimOutputEz(simulationParams& sp, simulationState& ss){
	std::string filename = "Sim-Output-Ez-step" + std::to_string(ss.step) + ".csv";
	FILE* outputFile;
	outputFile = fopen(filename.c_str(), "w");
	if(outputFile == NULL){
		return -1;
	}
	for(int z = 0; z < sp.z; z++){ for(int x = 0; x <= sp.x; x++){
		fprintf(outputFile, "%f, ", ss.yeeGrid.getCell(x, 0, z).ez.current);
	}
		fprintf(outputFile, "%f\n", ss.yeeGrid.getCell(sp.x-1, 0, z).ez.current);
	}
	fclose(outputFile);
	std::cout << "File Ez has been written " << std::endl;
	return 0;
}

//Save Hy
int saveSimOutputHy(simulationParams& sp, simulationState& ss){
	std::string filename = "Sim-Output-Hy-step" + std::to_string(ss.step) + ".csv";
	FILE* outputFile;
	outputFile = fopen(filename.c_str(), "w");
	if(outputFile == NULL) return -1;
	
	for(int z = 0; z < sp.z; z++){ for(int x = 0; x <= sp.x; x++){
		fprintf(outputFile, "%f, ", ss.yeeGrid.getCell(x, 0, z).hy.current);
	}
		fprintf(outputFile, "%f\n", ss.yeeGrid.getCell(sp.x-1, 0, z).hy.current);
	}
	fclose(outputFile);
	std::cout << "File Hy has been written " << std::endl;
	return 0;

}

//Save a grid workspace
int saveGridWorkspace(simulationState& ss, simulationParams& sp){
	std::string filename; //will be set by the user
	FILE* outputFile;
	outputFile = fopen(filename.c_str(), "w");
	if(outputFile == NULL){
		return -1;
	}
	fprintf(outputFile, "%d %d %d ", sp.x, sp.y, sp.z);
	for(int i = 0; i < ss.materialGrid.grid.size(); i++){
		float e, o, u;
		int empty;
		e = ss.materialGrid.grid[i].permittivity;
		o = ss.materialGrid.grid[i].conductivity;
		u = ss.materialGrid.grid[i].permeability;
		empty = (int)ss.materialGrid.grid[i].empty; //be careful with the cast here
		fprintf(outputFile, "%f %f %f %d ", e, o, u, empty);
	}
	fclose(outputFile);
	return 0;

}

#endif

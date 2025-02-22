#ifndef COMMON_H
#define COMMON_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct simulationParams{
	//dimensions
	int x;
	int y;
	int z;

	float dx;
	float dy;
	float dz;
	float dt;
};

struct physicalConstants{
	inline static float e0 = 0.25f; //8.854e-12;
	inline static float u0 = 0.25f; //12.56e-7;
	inline static float o0 = 0;
	inline static float c = 299792458;
};

struct Ex{
	float current;
	float last;
	float invPermittivity;
	float conductivity;
};
struct Ey{
	float current;
	float last;
	float invPermittivity;
	float conductivity;
};
struct Ez{
	float current;
	float last;
	float invPermittivity;
	float conductivity;
};
struct Hx{
	float current;
	float last;
	float permeability;
};
struct Hy{
	float current;
	float last;
	float permeability;
};
struct Hz{
	float current;
	float last;
	float permeability;
};

struct YeeTrihedralCell{
	glm::ivec3 pivot;
	Ex ex;
	Ey ey;
	Ez ez;
	Hx hx;
	Hy hy;
	Hz hz;
};

//not sure how to apply PML yet so I'll just experiment with this:
void setBoundaryCell(YeeTrihedralCell& ytc){
	ytc.pivot = glm::ivec3(0,0,0);

	ytc.ex.current = 0;
	ytc.ex.last = 0;
	ytc.ex.invPermittivity = 1/physicalConstants::e0;
	ytc.ex.conductivity = physicalConstants::o0;

	ytc.ey.current = 0;
	ytc.ey.last = 0;
	ytc.ey.invPermittivity = 1/physicalConstants::e0;
	ytc.ey.conductivity = physicalConstants::o0;

	ytc.ez.current = 0;
	ytc.ez.last = 0;
	ytc.ez.invPermittivity = 1/physicalConstants::e0;
	ytc.ez.conductivity = physicalConstants::o0;

	ytc.hx.current = 0;
	ytc.hx.last = 0;
	ytc.hx.permeability = physicalConstants::u0;

	ytc.hy.current = 0;
	ytc.hy.last = 0;
	ytc.hy.permeability = physicalConstants::u0;

	ytc.hz.current = 0;
	ytc.hz.last = 0;
	ytc.hz.permeability = physicalConstants::u0;
}

class YeeGrid{
public:
	std::vector<YeeTrihedralCell> grid; //to be intitialized 
	int dimX, dimY, dimZ;

	YeeGrid(){}
	YeeGrid(simulationParams& sp){
		dimX = sp.x;
		dimY = sp.y;
		dimZ = sp.z;
		this->grid.resize(sp.x*sp.y*sp.z);

		//initialize all grid components:
		YeeTrihedralCell ytc;
		setBoundaryCell(ytc);
		for(int i = 0; i < this->grid.size(); i++) this->grid[i] = ytc;

		//conducting wire injection:
		/*for(int x=0; x<200; x++){
			grid[50*200 + x].ex.invPermittivity = 0.0f;
			grid[50*200 + x].ex.conductivity = 1000.f;
			grid[50*200 + x].ey.invPermittivity = 0.0f;
			grid[50*200 + x].ey.conductivity = 1000.f;
			grid[50*200 + x].ez.invPermittivity = 0.0f;
			grid[50*200 + x].ez.conductivity = 1000.f;
		}
		
		for(int x = 80; x < 120; x++){
			grid[105*200+x].ex.invPermittivity = 0.0f;
			grid[105*200+x].ex.conductivity = 1000.0f;
			grid[105*200+x].ey.invPermittivity = 0.0f;
			grid[105*200+x].ey.conductivity = 1000.0f;
			grid[105*200+x].ez.invPermittivity = 0.0f;
			grid[105*200+x].ez.conductivity = 1000.0f;
		}*/

		
	}
	
	void setCellEx(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ex.current = val;
	}
	void setCellEy(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ey.current = val;
	}
	void setCellEz(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ez.current = val;
	}
	void setCellHx(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hx.current = val;
	}
	void setCellHy(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hy.current = val;
	}
	void setCellHz(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hz.current = val;
	}

	void setCellExLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ex.last = val;
	}
	void setCellEyLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ey.last = val;
	}
	void setCellEzLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].ez.last = val;
	}
	void setCellHxLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hx.last = val;
	}
	void setCellHyLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hy.last = val;
	}
	void setCellHzLast(int x, int y, int z, float val){
		this->grid[this->dimX*z + this->dimY*x + y].hz.last = val;
	}

	YeeTrihedralCell getCell(int x, int y, int z){
		bool withinBounds = (x >= 0 && x < this->dimX && y >= 0 && y < this->dimY && z >= 0 && z < this->dimZ);
		if(withinBounds) return this->grid[this->dimX*z + this->dimY*x + y];
		else{
			if(x >= dimX){
				YeeTrihedralCell last_valid = this->getCell(dimX-1,y,z);
				return last_valid;
			}else{
				YeeTrihedralCell ytc;
				setBoundaryCell(ytc);
				return ytc;
			}
		}
	}

};

struct materialCell{
	float permittivity;
	float conductivity;
	float permeability;
	bool empty;
};

class MaterialGrid{
public:
	std::vector<materialCell> grid;		
	
};

struct materialSelection{
	inline static float e;
	inline static float o;
	inline static float u;
	inline static bool eraser;
};

class simulationState{
public:
	int step;
	float time;
	YeeGrid yeeGrid;
	MaterialGrid materialGrid;
	materialSelection materialselec;

	simulationState(simulationParams& sp){
		yeeGrid = YeeGrid(sp);
		step = 0;
		time = 0.0f;
	}
};

void pushV3T2(std::vector<float>& vertices, glm::vec3 vec, glm::vec2 tex){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
        vertices.push_back(tex.x);
        vertices.push_back(tex.y);
}

#endif

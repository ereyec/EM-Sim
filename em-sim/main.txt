#include <iostream>
#include <string>	

#include "common.h"
#include "context.h"
#include "application.h"

int main(int argc, char* argv[]){

	if(argc > 2){
		std::cout << "Usage: type \"help\" for more info " << std::endl;
	} else if(argc == 2){
		if(std::strcmp(argv[1], "help") == 0){
			std::cout << "For more info please visit: https://github.com/ereyec/EM-Sim" << std::endl;
		}
	}

	Application app;
	
	if(app.init(context) != -1){
		app.run(context);
	}
	app.cleanup(context);

	return 0;
}
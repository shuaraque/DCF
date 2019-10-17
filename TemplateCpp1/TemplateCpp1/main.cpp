#include <iostream>
#include <string>
#include "data.h"

using namespace std;

int main(int argc, char* argv[]) {


	if (argc != 4) {
		cout << "Check command arguments!" << endl;
			return 1;
	}
	data1 CSMA_CA_SIM;
	cout << "Starting simulation ... " << endl;
	CSMA_CA_SIM.readFile(argv[1], argv[2]);
	CSMA_CA_SIM.startSimulation();
	CSMA_CA_SIM.writeToFile(argv[3]);

	cout << "Simulation is done!" << endl;

	return 0;
	   	  
}
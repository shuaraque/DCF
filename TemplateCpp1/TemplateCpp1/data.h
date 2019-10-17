#include <iostream>
#include <fstream>
#include <string>
#include "channel.h"
#include "station.h"

using namespace std;



class data1  {

public:
	data1() {

	};
	int readFile(string inputFile1, string inputFile2);

	int startSimulation();
	int writeToFile(string outFile);

private:

	vector <station> Stations_with_arrivals;
	channel obj;



};
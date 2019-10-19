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
	int readFile(string inputFile1, string inputFile2, string outputFile);

	int startSimulation();
	int writeToFile(string outFile, vector <station> &StationX);

private:
	string outPutFile;
	vector <station> Stations_with_arrivals_Ta;
	vector <station> Stations_with_arrivals_Ta_VCS;
	vector <station> Stations_with_arrivals_Tb;
	vector <station> Stations_with_arrivals_Tb_VCS;
	channel obj;



};
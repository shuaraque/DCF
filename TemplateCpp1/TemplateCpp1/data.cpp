#include"data.h"


int data1::readFile(string inputFile1, string inputFile2, string outputFile) {
	this->outPutFile = outputFile;
	station A;
	station C;
	double time = 0.0;

	ifstream inFile1;
	inFile1.open(inputFile1);
	if (!inFile1.is_open()) {
		cout << "Cant open file1" << endl;
	}
	ifstream inFile2;
	inFile2.open(inputFile2);
	if (!inFile2.is_open()) {
		cout << "Cant open file2" << endl;
	}

	while (!inFile1.eof()) {
		inFile1 >> time;
		if (!inFile1.eof()) {
			A.SetArrivals(time);
		}

	}

	while (!inFile2.eof()) {
		inFile2 >> time;
		if (!inFile2.eof()) {
			C.SetArrivals(time);
		}

	}

	Stations_with_arrivals_Ta.push_back(A);
	Stations_with_arrivals_Ta.push_back(C);

	Stations_with_arrivals_Ta_VCS=Stations_with_arrivals_Ta;
	Stations_with_arrivals_Tb = Stations_with_arrivals_Ta;
	Stations_with_arrivals_Tb_VCS = Stations_with_arrivals_Ta;
	inFile1.close();
	inFile2.close();

	return 0;
}


int data1::startSimulation() {
	// a1
	//obj.transmit_Ta_CSMACA(Stations_with_arrivals_Ta);
	//this->writeToFile(outPutFile, Stations_with_arrivals_Ta);
	//a2
	//obj.transmit_Ta_CSMACA_VCS(Stations_with_arrivals_Ta_VCS);
	//this->writeToFile(outPutFile, Stations_with_arrivals_Ta_VCS);
	//b1
	//obj.transmit_Tb_CSMACA(Stations_with_arrivals_Tb);
	//this->writeToFile(outPutFile, Stations_with_arrivals_Tb);
	//b2
	obj.transmit_Tb_CSMACA_VCS(Stations_with_arrivals_Tb_VCS);
	this->writeToFile(outPutFile, Stations_with_arrivals_Tb_VCS);


	return 0;
}

int data1::writeToFile(string outFile, vector <station> &StationX) {
	ofstream outF;
	outF.open(outFile);
	if (!outF.is_open()) {
		cout << "Can't open file to write" << endl;
	}
	outF << "Station A successes= " << StationX[0].GetnumSuccesses() << endl;
	outF << "Station A collisions= " << StationX[0].GetnumCollisions()<< endl;
	outF << "A Throughput= " << ((double)StationX[0].GetnumSuccesses()*12000.0 )/ double(10) << endl;
	outF << endl;
	outF << "*****************************************************************" << endl;
	outF << endl;
	outF << "Station C successes= " << StationX[1].GetnumSuccesses() << endl;
	outF << "Station C collisions= " << StationX[1].GetnumCollisions() << endl;
	outF << "C Throughput= " << ((double)StationX[1].GetnumSuccesses()*12000.0) / double(10) << endl;

	outF.close();

	return 0;

}
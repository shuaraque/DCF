#include"data.h"


int data1::readFile(string inputFile1, string inputFile2) {
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

	Stations_with_arrivals.push_back(A);
	Stations_with_arrivals.push_back(C);
	inFile1.close();
	inFile2.close();

	return 0;
}


int data1::startSimulation() {

	obj.transmit(Stations_with_arrivals);

	return 0;
}

int data1::writeToFile(string outFile) {
	ofstream outF;
	outF.open(outFile);
	if (!outF.is_open()) {
		cout << "Can't open file to write" << endl;
	}
	outF << "Station A successes= " << Stations_with_arrivals[0].GetnumSuccesses() << endl;
	outF << "Station A collisions= " << Stations_with_arrivals[0].GetnumCollisions()<< endl;
	outF << "A Throughput= " << ((double)Stations_with_arrivals[0].GetnumSuccesses()*12000.0 )/ double(10) << endl;
	outF << endl;
	outF << "**********************************************************************************************" << endl;
	outF << endl;
	outF << "Station C successes= " << Stations_with_arrivals[1].GetnumSuccesses() << endl;
	outF << "Station C collisions= " << Stations_with_arrivals[1].GetnumCollisions() << endl;
	outF << "C Throughput= " << ((double)Stations_with_arrivals[1].GetnumSuccesses()*12000.0) / double(10) << endl;

	outF.close();

	return 0;

}
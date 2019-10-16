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
		A.SetArrivals(time);

	}

	while (!inFile2.eof()) {
		inFile2 >> time;
		C.SetArrivals(time);

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
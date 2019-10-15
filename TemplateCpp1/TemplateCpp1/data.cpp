#include"data.h"


int readFile(string inputFile1, string inputFile2) {
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

	inFile1.close();
	inFile2.close();

}
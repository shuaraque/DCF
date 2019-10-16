#include "channel.h"
#include "station.h"



int channel::transmitS(station& x, int i) {
	
	i += DIFS; // sence the channel for DIFS

	if (this->ch_status != Busy) {

		i += x.GetBackoffTime(); // Backoff time
	}

	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.success();
	this->collision = false;
	return i;
}
int channel::transmitC(station& x, int i) {

	//i += DIFS; // sence the channel for DIFS

	i += x.GetBackoffTime(); // Backoff time
	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.collision();
	this->collision = true;
	return i;
}

int channel::transmit(vector<station> &stations) {

	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;

	vector<double> arrival_times_A = A.GetArrivals();
	vector<double> arrival_times_C = C.GetArrivals();

	A.selectBackoffTime(CW_0, 0); // select a random backoff time between 0 and 3
	C.selectBackoffTime(CW_0, 0);

	int i = 1;
	int j = 0;
	while (i <= SIM_TIME) { // simulation time 

		if (i <= ceil(arrival_times_A[j])) {
			A_arrival = true;
		}
		if (i <= ceil(arrival_times_C[j])) {
			C_arrival = true;
		}

		if (A_arrival == true && C_arrival == false) { // A gets the channel

			i = this->transmitS(A, i); // function for successful transmision

		}
		if (C_arrival == true && A_arrival == false) {  // C gets the channel

			i = this->transmitS(C, i);
		}

		if (C_arrival == true && C_arrival == true) {   // A and C tries to grab the channel

			//i += DIFS; // both sence the channel for DIFS

			if (A.GetBackoffTime() - C.GetBackoffTime() > 0) { // A has larger backoff time, A freezes and C transmit
				A.SetBackoffTime(A.GetBackoffTime() - C.GetBackoffTime());// freeze A
				i = this->transmitS(C, i); // C transmits
			}
			else if (A.GetBackoffTime() - C.GetBackoffTime() < 0) { // C has larger backoff time
				C.SetBackoffTime(C.GetBackoffTime() - A.GetBackoffTime()); // freeze C
				i = this->transmitS(A, i); // A transmits
			}
			else if (A.GetBackoffTime() == C.GetBackoffTime()) {
				while (A.GetBackoffTime() == C.GetBackoffTime()) {
					this->transmitC(A, i); // collision No ACK received
					i = this->transmitC(C, i); // collision No ACK received
				//	A.selectBackoffTime()
				}
			}



		}
		A_arrival = false;
		C_arrival = false;
		i++;
		j++;

	}





	return 0;
}
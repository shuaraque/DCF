#include "channel.h"
#include "station.h"



int channel::transmitS(station& x, int i) {
	
	i += DIFS; // sence the channel for DIFS

	if (this->ch_status != Busy) {

		i += x.GetBackoffTime(); // Backoff time
	}

	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.success();
	this->collision = 0;
	return i;
}
int channel::transmitC(station& x, int i) {

	//i += DIFS; // sence the channel for DIFS

	i += x.GetBackoffTime(); // Backoff time
	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.collision();
	this->collision += 1;
	return i;
}

int channel::transmit(vector<station> &stations) {

	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;

	
	queue<double> arrival_times_A = A.GetArrivals();
	queue<double> arrival_times_C = C.GetArrivals();



	int i = 1;

	while (i <= SIM_TIME) { // simulation time 

		A.selectBackoffTime(CW_0, 0); // select a random backoff time between 0 and 3
		C.selectBackoffTime(CW_0, 0);

		if (i > ceil(arrival_times_A.front()) && i > ceil(arrival_times_C.front())) { // FIXME

			if (ceil(arrival_times_A.front()) - ceil(arrival_times_C.front()) > 0) { // update simulation timer
				i = arrival_times_A.front();
			}
			else {
				i = arrival_times_C.front();
			}
			
		}


		


		if (i <= ceil(arrival_times_A.front())) {
			A_arrival = true;
		}
		if (i <= ceil(arrival_times_C.front())) {
			//arrival_times_C.pop();
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
				arrival_times_C.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() - C.GetBackoffTime() < 0) { // C has larger backoff time
				C.SetBackoffTime(C.GetBackoffTime() - A.GetBackoffTime()); // freeze C
				i = this->transmitS(A, i); // A transmits
				arrival_times_A.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() == C.GetBackoffTime()) { // A and C have similar backoff times

				while (A.GetBackoffTime() == C.GetBackoffTime()) {
					this->transmitC(A, i); // collision No ACK received
					i = this->transmitC(C, i); // collision No ACK received
					A.selectBackoffTime(CW_0, this->collision);
					C.selectBackoffTime(CW_0, this->collision);
				}
				if (A.GetBackoffTime() != C.GetBackoffTime()) {

					if (A.GetBackoffTime() - C.GetBackoffTime() > 0) { // A has larger backoff time, A freezes and C transmit
						A.SetBackoffTime(A.GetBackoffTime() - C.GetBackoffTime());// freeze A
						i = this->transmitS(C, i); // C transmits
						arrival_times_C.pop(); // remove the first element
					}
					else if (A.GetBackoffTime() - C.GetBackoffTime() < 0) { // C has larger backoff time
						C.SetBackoffTime(C.GetBackoffTime() - A.GetBackoffTime()); // freeze C
						i = this->transmitS(A, i); // A transmits
						arrival_times_A.pop(); // remove the first element
					}

				}
			}



		}
		A_arrival = false;
		C_arrival = false;
		i++;

	}





	return 0;
}
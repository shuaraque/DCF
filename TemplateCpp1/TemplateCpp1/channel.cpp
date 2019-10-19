#include "channel.h"
#include "station.h"



int channel::transmitS(station& x, int i) {
	
	i += DIFS; // sence the channel for DIFS

		i += x.GetBackoffTime(); // Backoff time
	

	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.success();
	return i;
}

int channel::transmitS_VCS(station& x, int i) {

	i += DIFS; // sence the channel for DIFS

	if (this->ch_status != Busy) {

		i += x.GetBackoffTime(); // Backoff time
	}
	i += RTS+SIFS+CTS+SIFS; // adding the RTS and CTS times 
	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.success();
	return i;
}



int channel::transmitC(station& x, int i) {

	i += DIFS; // sence the channel for DIFS

	i += x.GetBackoffTime(); // Backoff time
	i += Data_Frame_Size + SIFS + ACK; // sending a frame and receiving ack
	x.collision();
	return i;
}

int channel::transmitC_VCS(station& x, int i) {

	i += DIFS; // sence the channel for DIFS

	i += x.GetBackoffTime(); // Backoff time
	i += RTS + SIFS + CTS + SIFS; // adding the RTS and CTS times 

	x.collision();
	return i;
}

int channel::transmit_Ta_CSMACA(vector<station> &stations) {
	int i = 1;
	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;

	
	queue<double> arrival_times_A = A.GetArrivals();
	queue<double> arrival_times_C = C.GetArrivals();

	if (ceil(arrival_times_A.front()) - ceil(arrival_times_C.front()) > 0) { // setting simulation timer
		i = ceil(arrival_times_C.front()); // if arrival time of C is less that arrival time of A
	}
	else {
		i = ceil(arrival_times_A.front()); // if arrival time of A is less that arrival time of C
	}

	A.selectBackoffTime(CW_0, 0); // select a random backoff time between 0 and 3
	C.selectBackoffTime(CW_0, 0);

	while (i <= SIM_TIME) { // simulation time 



		if (arrival_times_A.size() !=0 && i >= ceil(arrival_times_A.front())) {
			A_arrival = true; //  A has an arrival
			//C_arrival = true;
		}
		if (arrival_times_C.size() != 0 && i >= ceil(arrival_times_C.front())) {
			C_arrival = true;  // only has an arrival
		}

		if (A_arrival == false && C_arrival == false) {
			i++;
			continue;
		}


		if (A_arrival == true && C_arrival == false) { // A gets the channel

			i = this->transmitS(A, i); // function for successful transmision
			A.Resetcollision_CW();
			A.selectBackoffTime(CW_0, 0);
			arrival_times_A.pop(); // remove the first element
		}
		if (C_arrival == true && A_arrival == false) {  // C gets the channel

			i = this->transmitS(C, i);
			C.Resetcollision_CW();
			C.selectBackoffTime(CW_0, 0);
			arrival_times_C.pop(); // remove the first element
		}

		if (A_arrival == true && C_arrival == true) {   // A and C tries to grab the channel

			//i += DIFS; // both sence the channel for DIFS

			if (A.GetBackoffTime() - C.GetBackoffTime() > 0) { // A has larger backoff time, A freezes and C transmit
				A.SetBackoffTime(A.GetBackoffTime() - C.GetBackoffTime());// freeze A
				i = this->transmitS(C, i); // C transmits
				C.Resetcollision_CW();
				C.selectBackoffTime(CW_0, 0);
				arrival_times_C.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() - C.GetBackoffTime() < 0) { // C has larger backoff time
				C.SetBackoffTime(C.GetBackoffTime() - A.GetBackoffTime()); // freeze C
				i = this->transmitS(A, i); // A transmits
				A.Resetcollision_CW();
				A.selectBackoffTime(CW_0, 0);
				arrival_times_A.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() == C.GetBackoffTime()) { // A and C have similar backoff times

				while (A.GetBackoffTime() == C.GetBackoffTime()) {
					this->transmitC(A, i); // collision No ACK received
					i = this->transmitC(C, i); // collision No ACK received
					A.Setcollision_CW(); // number of collisions
					C.Setcollision_CW();
					A.selectBackoffTime(CW_0, A.Getcollision_CW());
					C.selectBackoffTime(CW_0, C.Getcollision_CW());
				}
	
			}



		}
		A_arrival = false;
		C_arrival = false;
		

	}




	stations[0] = A;
	stations[1] = C;
	return 0;
}


int channel::transmit_Ta_CSMACA_VCS(vector<station> &stations) {

	int i = 1;
	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;


	queue<double> arrival_times_A = A.GetArrivals();
	queue<double> arrival_times_C = C.GetArrivals();

	if (ceil(arrival_times_A.front()) - ceil(arrival_times_C.front()) > 0) { // setting simulation timer
		i = ceil(arrival_times_C.front()); // if arrival time of C is less that arrival time of A
	}
	else {
		i = ceil(arrival_times_A.front()); // if arrival time of A is less that arrival time of C
	}

	A.selectBackoffTime(CW_0, 0); // select a random backoff time between 0 and 3
	C.selectBackoffTime(CW_0, 0);

	while (i <= SIM_TIME) { // simulation time 



		if (arrival_times_A.size() != 0 && i >= ceil(arrival_times_A.front())) {
			A_arrival = true; //  A has an arrival
			//C_arrival = true;
		}
		if (arrival_times_C.size() != 0 && i >= ceil(arrival_times_C.front())) {
			C_arrival = true;  // only has an arrival
		}

		if (A_arrival == false && C_arrival == false) {
			i++;
			continue;
		}


		if (A_arrival == true && C_arrival == false) { // A gets the channel

			i = this->transmitS_VCS(A, i); // function for successful transmision
			A.Resetcollision_CW();
			A.selectBackoffTime(CW_0, 0);
			arrival_times_A.pop(); // remove the first element
		}
		if (C_arrival == true && A_arrival == false) {  // C gets the channel

			i = this->transmitS_VCS(C, i);
			C.Resetcollision_CW();
			C.selectBackoffTime(CW_0, 0);
			arrival_times_C.pop(); // remove the first element
		}

		if (A_arrival == true && C_arrival == true) {   // A and C tries to grab the channel

			//i += DIFS; // both sence the channel for DIFS

			if (A.GetBackoffTime() - C.GetBackoffTime() > 0) { // A has larger backoff time, A freezes and C transmit
				A.SetBackoffTime(A.GetBackoffTime() - C.GetBackoffTime());// freeze A
				i = this->transmitS_VCS(C, i); // C transmits
				C.Resetcollision_CW();
				C.selectBackoffTime(CW_0, 0);
				arrival_times_C.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() - C.GetBackoffTime() < 0) { // C has larger backoff time
				C.SetBackoffTime(C.GetBackoffTime() - A.GetBackoffTime()); // freeze C
				i = this->transmitS_VCS(A, i); // A transmits
				A.Resetcollision_CW();
				A.selectBackoffTime(CW_0, 0);
				arrival_times_A.pop(); // remove the first element
			}
			else if (A.GetBackoffTime() == C.GetBackoffTime()) { // A and C have similar backoff times

				while (A.GetBackoffTime() == C.GetBackoffTime()) {
					this->transmitC_VCS(A, i); // collision No ACK received
					i = this->transmitC_VCS(C, i); // collision No ACK received
					A.Setcollision_CW(); // number of collisions
					C.Setcollision_CW();
					A.selectBackoffTime(CW_0, A.Getcollision_CW());
					C.selectBackoffTime(CW_0, C.Getcollision_CW());
				}

			}



		}
		A_arrival = false;
		C_arrival = false;


	}




	stations[0] = A;
	stations[1] = C;
	return 0;






}


int channel::transmit_Tb_CSMACA(vector<station> &stations) { // FIXME
	int A_timer = 1;
	int C_timer = 1;
	int i = 1;
	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;


	queue<double> arrival_times_A = A.GetArrivals();
	queue<double> arrival_times_C = C.GetArrivals();

	
		C_timer = ceil(arrival_times_C.front()); // if arrival time of C is less that arrival time of A
	
		A_timer = ceil(arrival_times_A.front()); // if arrival time of A is less that arrival time of C


	A.selectBackoffTime(CW_0, 0); // select a random backoff time between 0 and 3
	C.selectBackoffTime(CW_0, 0);

	//if (A_timer < C_timer) {
	//	i = A_timer;
	//}
	//else
	//{
	//	i = C_timer;
	//}

	while (i <= SIM_TIME) { // simulation time 
		A_timer=924
			C_timer=1175

		if (A_timer < C_timer) {
			i = A_timer;
		}
		else
		{
			i = C_timer;
		}

		if (arrival_times_A.size() != 0 ) {
			A_arrival = true; //  A has an arrival
			//if (A_timer >= ceil(arrival_times_A.front())) {
			//	//
			//}
			//else {
			//	A_timer = ceil(arrival_times_A.front());
			//}
			//C_arrival = true;
		}
		if (arrival_times_C.size() != 0 ) {
			C_arrival = true;  // only has an arrival
			//if (C_timer >= ceil(arrival_times_C.front())) {
			//	//
			//}
			//else {
			//	C_timer = ceil(arrival_times_C.front());
			//}
		}

		if (A_arrival == false && C_arrival == false) {
			i++;
			continue;
		}




		if (A_arrival == true && C_arrival == false) { // A gets the channel

			//i = this->transmitS(A, i); // function for successful transmision
			A_timer += DIFS + A.GetBackoffTime();
			A.SetA_transmission(A_timer);
			A_timer += Data_Frame_Size + SIFS;
			A_timer += ACK;
			A.success();
			A.Resetcollision_CW();
			A.selectBackoffTime(CW_0, 0);
			arrival_times_A.pop(); // remove the first element
			//i = A_timer;
		}
		if (C_arrival == true && A_arrival == false) {  // C gets the channel
				C_timer += DIFS + C.GetBackoffTime();
				C.SetC_transmission(C_timer);
				C_timer += Data_Frame_Size + SIFS;
				C_timer += ACK;
				C.success();
				C.Resetcollision_CW();
				C.selectBackoffTime(CW_0, 0);
				arrival_times_C.pop(); // remove the first element
				//i = C_timer;
			}

		if (A_arrival == true && C_arrival == true) {   // A and C send packet as they arrive

			if (A_timer < C_timer) { // A sends first 

				A_timer += DIFS + A.GetBackoffTime();
				A.SetA_transmission(A_timer);
				A_timer += Data_Frame_Size + SIFS;
				B.SetB_transmission_To_A(A_timer); // this the time when B start sending Ack
				A_timer += ACK;



				// now C sends
				if (A_timer < C_timer) {
					A.success();
					A.Resetcollision_CW();
					A.selectBackoffTime(CW_0, 0);
					arrival_times_A.pop(); // remove the first element
				}
				else {
					C_timer += DIFS + C.GetBackoffTime();
					C.SetC_transmission(C_timer);
					C_timer += Data_Frame_Size + SIFS;
					B.SetB_transmission_To_C(C_timer);
					C_timer += ACK;

					if ((A.GetA_transmission() <= C.GetC_transmission() && A.GetA_transmission() + 100 > C.GetC_transmission() )
						|| (C.GetC_transmission() <= A.GetA_transmission() && C.GetC_transmission() + 100 > A.GetA_transmission())) {

						A.collision();
						C.collision();
						A.Setcollision_CW(); // number of collisions
						C.Setcollision_CW();
						A.selectBackoffTime(CW_0, A.Getcollision_CW());
						C.selectBackoffTime(CW_0, C.Getcollision_CW());
					}
					else if (B.GetB_transmission_To_A() <= C.GetC_transmission() && B.GetA_transmission()+2 > C.GetC_transmission())
					{
						C.collision();
						C.Setcollision_CW();
						C.selectBackoffTime(CW_0, C.Getcollision_CW());
					}
					else if (B.GetB_transmission_To_C() <= A.GetA_transmission() && B.GetB_transmission_To_C() + 2 > A.GetA_transmission())
					{
						A.collision();
						A.Setcollision_CW();
						A.selectBackoffTime(CW_0, A.Getcollision_CW());
					}
					else {
						A.success();
						A.Resetcollision_CW();
						A.selectBackoffTime(CW_0, 0);
						arrival_times_A.pop(); // remove the first element
						C_timer = C.GetC_transmission();
					}


				}

		

			}


			else if (A_timer > C_timer) { // C sends first

				C_timer += DIFS + C.GetBackoffTime();
				C.SetC_transmission(C_timer);
				C_timer += Data_Frame_Size + SIFS;
				B.SetB_transmission_To_C(C_timer); // this the time when B start sending Ack
				C_timer += ACK;



				// now C sends
				if (C_timer < A_timer) {
					C.success();
					C.Resetcollision_CW();
					C.selectBackoffTime(CW_0, 0);
					arrival_times_C.pop(); // remove the first element
				}
				else {
					A_timer += DIFS + A.GetBackoffTime();
					A.SetA_transmission(A_timer);
					A_timer += Data_Frame_Size + SIFS;
					B.SetB_transmission_To_A(A_timer);
					A_timer += ACK;

					if (C.GetC_transmission() <= A.GetA_transmission() && C.GetC_transmission() + 100 > A.GetA_transmission()) {

						A.collision();
						C.collision();
						A.Setcollision_CW(); // number of collisions
						C.Setcollision_CW();
						A.selectBackoffTime(CW_0, A.Getcollision_CW());
						C.selectBackoffTime(CW_0, C.Getcollision_CW());
					}
					else if (B.GetB_transmission_To_C() <= A.GetA_transmission() && B.GetB_transmission_To_C() + 2 > A.GetA_transmission())
					{
						A.collision();
						A.Setcollision_CW();
						A.selectBackoffTime(CW_0, A.Getcollision_CW());
					}


				}
			
}

			else {  // they both send at the same time 

				A_timer += DIFS + A.GetBackoffTime();
				A.SetA_transmission(A_timer);
				A_timer += Data_Frame_Size + SIFS;
				A_timer += ACK;

			

				C_timer += DIFS + C.GetBackoffTime();
				C.SetC_transmission(C_timer);
				C_timer += Data_Frame_Size + SIFS;
				C_timer += ACK;

		

				A.collision();
				C.collision();
				A.Setcollision_CW(); // number of collisions
				C.Setcollision_CW();
				A.selectBackoffTime(CW_0, A.Getcollision_CW());
				C.selectBackoffTime(CW_0, C.Getcollision_CW());

			}


		}
		A_arrival = false;
		C_arrival = false;


	}




	stations[0] = A;
	stations[1] = C;

	return 0;


}
#include "channel.h"
#include "station.h"


int channel::transmit(vector<station>stations) {

	station A = stations[0];
	station C = stations[1];
	bool A_arrival = false;
	bool C_arrival = false;

	vector<double> arrival_times_A = A.GetArrivals();
	vector<double> arrival_times_C = C.GetArrivals();


	A.SetBackoffTime(CW_0);
	C.SetBackoffTime(CW_0);
	int i = 1;
	int j = 0;
	while (i <= SIM_TIME) {

		if (i == ceil(arrival_times_A[0])) {
			A_arrival = true;
		}
		if (i == ceil(arrival_times_C[0])) {
			C_arrival = true;
		}

		if (A_arrival == true) {
			if ((i - ceil(arrival_times_A[0]) < DIFS)) {
				continue;
			}
			else {
					A.backoffCountDown();

			}
		}

		if (C_arrival == true) {
			if ((i - ceil(arrival_times_C[0]) < DIFS)) {
				continue;
			}
			else {
				C.backoffCountDown();

			}
		}

		if (A.GetBackoffTime() == 0) {
			// A start transmitting 
		}





		
			
			
		

		// first sense the channel for DIFS slots 

		
		
		
		
		
		
		
		
		
		

		
	
		
		if (C.GetBackoffTime() == 0) {
			// C start transmitting 
		}
		
		i++;
	}


	






	return 0;
}
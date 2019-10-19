#ifndef satation_h
#define satation_h

#include <vector>
#include <math.h> 
#include <queue>
using namespace std;

#define SIFS 1 // one slot
#define DIFS 4 // 4 slots
#define CW_0 4 // CW0 4 slots
#define CW_MAX 1024 // CW MAX 1024 slots
#define SIM_TIME 1000000 // simulation time 1M slots
#define Data_Frame_Size 100 // 100 slots
#define ACK 2 // 2 slots
#define RTS 2 // 2 slots
#define CTS 2 // 2 slots

class station {

public:
	station() {
		backoffTime = 0;
		numCollisions = 0;
		numSuccesses = 0;
		collision_CW = 0;
	}
	void selectBackoffTime(int CE_value, int numCollision); // initialize backoff with random value
	void SetBackoffTime(int time) { this->backoffTime = time; }
	int  GetBackoffTime() { return this->backoffTime; }
	void backoffCountDown() { this->backoffTime = this->backoffTime - 1; }
	void SetArrivals(double arrival) { this->arrivals.push(arrival); }
	queue <double> GetArrivals() { return this->arrivals; }
	void success() { this->numSuccesses++; }
	void collision() { this->numCollisions++; }
	int GetnumSuccesses() { return this->numSuccesses; }
	int GetnumCollisions() { return this->numCollisions; }

	void Setcollision_CW() { this->collision_CW += 1; }
	void Resetcollision_CW() { this->collision_CW = 0; }
	int Getcollision_CW() { return this->collision_CW; }



	void SetA_transmission(int num) { this->A_transmission = num; }
	int GetA_transmission() { return this->A_transmission; }

	void SetC_transmission(int num) { this->C_transmission = num; }
	int GetC_transmission() { return this->C_transmission; }

	void SetB_transmission(int num) { this->B_transmission = num; }
	int GetB_transmission() { return this->B_transmission; }
protected:
	int backoffTime; // backoff time
	queue <double> arrivals; // frames arrival times
	int numCollisions;// counter for collisions
	int numSuccesses;// counter for successes
	int collision_CW; 


	int A_transmission;
	int C_transmission;

	int B_transmission;
};

























#endif // satation_h

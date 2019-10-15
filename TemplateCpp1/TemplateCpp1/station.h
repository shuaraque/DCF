#ifndef satation_h
#define satation_h

#include <vector>
#include <math.h> 
using namespace std;

#define SIFS 1 // one slot
#define DIFS 4 // 4 slots
#define CW_0 4 // CW0 4 slots
#define CW_MAX 1024 // CW MAX 1024 slots
#define SIM_TIME 1000000 // simulation time 1M slots

class station {

public:
	station() {

	}
	void selectBackoffTime(int CE_value); // initialize backoff with random value
	void SetBackoffTime(int time) { this->backoffTime = time; }
	int  GetBackoffTime() { return this->backoffTime; }
	void backoffCountDown() { this->backoffTime = this->backoffTime - 1; }
	void SetArrivals(double arrival) { this->arrivals.push_back(arrival); }
	vector <double> GetArrivals() { return this->arrivals; }
	void success() { this->numSuccesses++; }
	void collision() { this->numCollisions++; }
	int GetnumSuccesses() { return this->numSuccesses; }
	int GetnumCollisions() { return this->numCollisions; }

protected:
	int backoffTime; // backoff time
	vector <double> arrivals; // frames arrival times
	int numCollisions;// counter for collisions
	int numSuccesses;// counter for successes

};

/*--------------------------------------------------------------------------------*/

//class station_A : public station {
//
//public:
//
//	
//
//
//private:
//
//
//};
///*--------------------------------------------------------------------------------*/
//
//class station_C : public station {
//
//public:
//
//
//
//
//private:
//
//
//};

























#endif // satation_h

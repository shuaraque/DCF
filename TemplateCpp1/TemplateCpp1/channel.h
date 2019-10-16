#ifndef channel_h
#define channel_h

#include "station.h"
#include <math.h> 
typedef enum status_ch{
	Idle, Busy
}status;

class channel {

public:
	channel(){
		this->ch_status = Idle;
	}
	void SetStatus(status x) { this->ch_status = x; }// set to Idle or Busy
	status GetStatus() { return this->ch_status; }// return the state
	int transmit(vector<station> &stations);
	int transmitS(station& x, int i);
	int transmitC(station& x, int i);

protected:
	status ch_status; // channel status busy or idle


};


#endif // !channel_h

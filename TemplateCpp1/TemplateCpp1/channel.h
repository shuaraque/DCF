#ifndef channel_h
#define channel_h

#include "station.h"
#include <math.h> 
typedef enum status_ch{
	Idle, Busy
}status;

class channel {

public:

	void SetStatus(status x) { this->ch_status = x; }// set to Idle or Busy
	status GetStatus() { return this->ch_status; }// return the state
	int transmit(vector<station>stations);

protected:
	status ch_status; // channel status busy or idle


};


#endif // !channel_h

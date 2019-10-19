#ifndef channel_h
#define channel_h

#include "station.h"
#include <math.h> 
#include <queue>
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
	int transmitS(station& x, int i);
	int transmitC(station& x, int i);

	int transmitS_VCS(station& x, int i);
	int transmitC_VCS(station& x, int i);


	int transmit_Ta_CSMACA(vector<station> &stations);
	int transmit_Ta_CSMACA_VCS(vector<station> &stations);

	int transmit_Tb_CSMACA(vector<station> &stations);
	int transmit_Tb_CSMACA_VCS(vector<station> &stations);

protected:
	status ch_status; // channel status busy or idle


	int RTC;
	int CTC;

	station B;

};


#endif // !channel_h

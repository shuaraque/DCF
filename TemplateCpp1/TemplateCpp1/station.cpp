#include "channel.h"
#include "station.h"
#include <random>

void station::selectBackoffTime(int CW_value) {
	// generating random number for backoff time between (0 and CW-1)
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_int_distribution<int> distribution(0, CW_value - 1);

	this->backoffTime = distribution(e2);


}
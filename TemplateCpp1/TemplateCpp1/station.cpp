#include "channel.h"
#include "station.h"
#include <random>

void station::selectBackoffTime(int CW_value, int numCollision) { // test
	// generating random number for backoff time between (0 and CW-1)
	int result = CW_value * pow(2, numCollision);
	if (result > CW_MAX) { result = CW_MAX; }
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_int_distribution<int> distribution(0, result - 1);

	this->backoffTime = distribution(e2);


}
#include "TrafficController.h"



TrafficController::TrafficController()
{
}


TrafficController::~TrafficController()
{
}

void TrafficController::makeSchedule(std::vector<std::vector<unsigned>> stationsGraph, std::vector<Train> trains)
{
	unsigned numTrains = sizeof(trains);
	for (size_t i = 0; i < numTrains; i++) {
		unsigned time = 0;
		unsigned pathLen = sizeof(trains[i].path);
		for (size_t p = 0; p < pathLen; p++) {

		}
	}
}

void TrafficController::findCollisions()
{
}

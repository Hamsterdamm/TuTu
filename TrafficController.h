#include <vector>
#include "Train.h"
#include "Railway.h"

#ifndef _TrafficController_H_
#define _TrafficController_H_

class TrafficController
{
private:
	std::vector<std::vector<long int>> schedule;
	unsigned numTrains;
	unsigned numStations;
public:
	TrafficController();
	~TrafficController();
	void makeSchedule(Railway& railway, std::vector<Train> trains);
	void findCollisions(Railway& railway);
};

#endif//_TrafficController_H_
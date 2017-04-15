#include <vector>
#include "Train.h"

#ifndef _TrafficController_H_
#define _TrafficController_H_

class TrafficController
{
private:
	std::vector<std::vector<unsigned>> schedule;
	unsigned numTrains;

public:
	TrafficController();
	~TrafficController();
	void makeSchedule(std::vector<std::vector<unsigned>> stationsGraph, std::vector<Train> trains);
	void findCollisions(std::vector<std::vector<unsigned>> stationsGraph);
};

#endif//_TrafficController_H_
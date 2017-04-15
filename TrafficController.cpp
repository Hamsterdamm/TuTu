#include "TrafficController.h"
#include <iostream>



TrafficController::TrafficController()
{
}


TrafficController::~TrafficController()
{
}

void TrafficController::makeSchedule(std::vector<std::vector<unsigned>> stationsGraph, std::vector<Train> trains)
{
	numTrains = sizeof(trains);
	for (size_t i = 0; i < numTrains; i++) {
		unsigned time = trains[i].starttime;
		unsigned pathLen = sizeof(trains[i].path);
		for (size_t p = 0; p < pathLen; p++) {
			schedule[i][trains[i].path[p]] = time + stationsGraph[trains[i].path[p]][trains[i].path[p] + 1]/ trains[i].velocity;
			time = schedule[i][trains[i].path[p]];
		}
	}
}

void TrafficController::findCollisions(std::vector<std::vector<unsigned>> stationsGraph)
{
	int k(0), l(0);
	while (stationsGraph[k][l] != 0) {
		for (int i = 0; i < numTrains; i++) {
			for (int j = 0; (j < numTrains) && (j != i); j++) {
				if (!((schedule[i][k]<schedule[j][k]&& schedule[i][l]<schedule[j][l])|| (schedule[i][k]>schedule[j][k] && schedule[i][l]>schedule[j][l]))) {
					std::cout<<"Столкновение"<<std::endl;
				}
			}
		}
	}
}

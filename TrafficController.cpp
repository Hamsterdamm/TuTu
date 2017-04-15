#include "TrafficController.h"
#include <iostream>



TrafficController::TrafficController()
{
}


TrafficController::~TrafficController()
{
}

void TrafficController::makeSchedule(Railway& railway, std::vector<Train> trains)
{
	numStations = railway.stationsGraph.size();
	numTrains = trains.size();
	for (size_t i = 0; i < numTrains; i++) {
		std::vector<long int> train(numStations, 0);
		schedule.push_back(train);
	}

	for (size_t i = 0; i < numTrains; i++) {
		unsigned time = trains[i].starttime;
		unsigned pathLen = trains[i].path.size();
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][trains[i].path[p]-1] = time + railway.stationsGraph[trains[i].path[p]-1][trains[i].path[p - 1]-1]/ trains[i].velocity;
			time = schedule[i][trains[i].path[p]-1];
		}
	}


}

void TrafficController::findCollisions(Railway& railway)
{
	int k(0), l(0);
	while (railway.stationsGraph[k][l] != 0) {
		for (size_t i = 0; i < numTrains; i++) {
			for (size_t j = 0; (j < numTrains) && (j != i); j++) {
				if (!((schedule[i][k]<schedule[j][k]&& schedule[i][l]<schedule[j][l])|| (schedule[i][k]>schedule[j][k] && schedule[i][l]>schedule[j][l]))) {
					std::cout<<"Столкновение"<<std::endl;
				}
			}
		}
		k++; l++;
	}
}

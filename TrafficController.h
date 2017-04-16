#include <vector>
#include "Train.h"
#include "Railway.h"

#ifndef _TrafficController_H_
#define _TrafficController_H_

class TrafficController
{
private:
	std::vector<std::vector<unsigned>> schedule;


public:
	unsigned numTrains;
	unsigned numStations;
	TrafficController();
	~TrafficController();

	void makeSchedule(Railway& railway, std::vector<Train> trains);//метод построения расписания поездов по станциям
	int findCollisions(Railway& railway, bool flag);//метод поиска столкновений по расписанию
	std::vector<std::vector<unsigned>> getSchedule() const;//метод получения расписания
};

#endif//_TrafficController_H_
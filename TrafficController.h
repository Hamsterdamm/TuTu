#include <vector>
#include "Train.h"

#ifndef _TrafficController_H_
#define _TrafficController_H_

typedef std::vector<std::vector<unsigned> > Railway;

class TrafficController
{
private:
	std::vector<std::vector<unsigned> > schedule;
	unsigned numTrains;
	unsigned numStations;

public:

	TrafficController();//конструктор
	~TrafficController();//деструктор

	int makeSchedule(Railway& railway, std::vector<Train> trains);//метод построения расписания поездов по станциям
	long findCollisions(Railway& railway, bool flag);//метод поиска столкновений по расписанию
	std::vector<std::vector<unsigned> > getSchedule() const;//метод получения расписания
};

#endif//_TrafficController_H_

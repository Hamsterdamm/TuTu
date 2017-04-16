#include <vector>
#include "Train.h"

#ifndef _TrafficController_H_
#define _TrafficController_H_

typedef std::vector<std::vector<unsigned>> RailwayType;

class TrafficController
{
private:
	std::vector<std::vector<unsigned>> schedule;

public:
	unsigned numTrains;
	unsigned numStations;

	TrafficController();
	~TrafficController();

	int makeSchedule(RailwayType& railway, std::vector<Train> trains);//����� ���������� ���������� ������� �� ��������
	long findCollisions(RailwayType& railway, bool flag);//����� ������ ������������ �� ����������
	std::vector<std::vector<unsigned>> getSchedule() const;//����� ��������� ����������
};

#endif//_TrafficController_H_
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

	void makeSchedule(Railway& railway, std::vector<Train> trains);//����� ���������� ���������� ������� �� ��������
	int findCollisions(Railway& railway, bool flag);//����� ������ ������������ �� ����������
	std::vector<std::vector<unsigned>> getSchedule() const;//����� ��������� ����������
};

#endif//_TrafficController_H_
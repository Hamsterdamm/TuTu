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

	TrafficController();//�����������
	~TrafficController();//����������

	int makeSchedule(Railway& railway, std::vector<Train> trains);//����� ���������� ���������� ������� �� ��������
	long findCollisions(Railway& railway, bool flag);//����� ������ ������������ �� ����������
	std::vector<std::vector<unsigned> > getSchedule() const;//����� ��������� ����������
};

#endif//_TrafficController_H_

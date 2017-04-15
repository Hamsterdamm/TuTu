#include "TrafficController.h"
#include <iostream>

TrafficController::TrafficController()
{
}

TrafficController::~TrafficController()
{
}

void TrafficController::makeSchedule(Railway& railway, std::vector<Train> trains)//����� ���������� ���������� ������� �� ��������
{
	numStations = railway.stationsGraph.size();//���������� ���������� �������
	numTrains = trains.size();//���������� ���������� �������
	for (size_t i = 0; i < numTrains; i++) {//�������������� ������� ���������� ������
		std::vector<long int> train(numStations, 0);
		schedule.push_back(train);
	}

	

	for (size_t i = 0; i < numTrains; i++) {
		std::vector<unsigned> path = trains[i].getPath();
		unsigned time = trains[i].getStarttime();//�������������� ���������� ������� �������� ����������� ������ � ��������� ������� (�� ������� = 0 ��� ����)
		unsigned pathLen = path.size();//���������� ����� ������� � �������� ������
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][path[p]-1] = 
				time + railway.stationsGraph[path[p]-1][path[p - 1]-1]/ trains[i].getVelocity();//� ���������� ������� ��� i-�� ������ 
																																			  //����� �������� �� p-� ������� �� ��� �������� 
																																			  //����� ����������� ����� (p-1)-� � p-� ���������, 
																																			  //�������� �� �������� (�� ������� = 1 ��� ����) 
																																			  //+ ����� ������� � ���������� �������
			time = schedule[i][path[p]-1];//���������� ����� �������� ��� ������� ��������� �������
		}
	}


}

void TrafficController::findCollisions(Railway& railway)//����� ������ ������������ �� ����������
{
	int k(0), l(0);
	while (railway.stationsGraph[k][l] != 0) {
		for (size_t i = 0; i < numTrains; i++) {
			for (size_t j = 0; (j < numTrains) && (j != i); j++) {
				if (!((schedule[i][k]<schedule[j][k]&& schedule[i][l]<schedule[j][l])|| (schedule[i][k]>schedule[j][k] && schedule[i][l]>schedule[j][l]))) {
					std::cout<<"������������"<<std::endl;
				}
			}
		}
		k++; l++;
	}
}

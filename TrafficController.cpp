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
		//unsigned time = trains[i].getStarttime();//�������������� ���������� ������� �������� ����������� ������ � ��������� ������� (�� ������� = 0 ��� ����)
		unsigned pathLen = path.size();//���������� ����� ������� � �������� ������

		schedule[i][path[0] - 1] = trains[i].getStarttime();
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][path[p]-1] = 
				schedule[i][path[p-1] - 1] + railway.stationsGraph[path[p]-1][path[p - 1]-1]/ trains[i].getVelocity();//� ���������� ������� ��� i-�� ������ 
																																			  //����� �������� �� p-� ������� �� ��� �������� 
																																			  //����� ����������� ����� (p-1)-� � p-� ���������, 
																																			  //�������� �� �������� (�� ������� = 1 ��� ����) 
																																			  //+ ����� ������� � ���������� �������
			//time = schedule[i][path[p]-1];//���������� ����� �������� ��� ������� ��������� �������
		}
	}


}

void TrafficController::findCollisions(Railway& railway)//����� ������ ������������ �� ����������
{

	unsigned collisionsCount = 0;
	for (size_t k = 0; k < numStations;k++) {
		for (size_t l = k+1; l < numStations; l++) {
			if ((railway.stationsGraph[k][l] != 0)) {
				for (size_t i = 0; i < numTrains; i++) {
					for (size_t j = i+1; j < numTrains; j++) {
						if ((schedule[i][k] != 0) && (schedule[j][k] != 0) && (schedule[i][l] != 0) && (schedule[j][l] != 0)) {//���� ����� �������� ������ � ����� �� ������� ������� �� �������
							
							if ((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l])) || ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l])) ||
								((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l]))) ||
								(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||
								((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l])))) {
								
								std::cout << "������������" << std::endl;
								collisionsCount++;

							}
							
							//if (((((static_cast<long>(schedule[i][k])) - schedule[j][k]) < 0) && (((static_cast<long>(schedule[i][l])) - schedule[j][l]) < 0)) || ((((static_cast<long>(schedule[i][k])) - schedule[j][k]) > 0) && (((static_cast<long>(schedule[i][l])) - schedule[j][l]) > 0))) {
							//	//���� ������ �������� � ����� �����������

							//	if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//		std::cout << "������������" << std::endl;
							//		collisionsCount++;
							//	}
							//}
							//else {
							//	//���� ������ �������� � ��������������� �����������

							//	if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//		std::cout << "������������" << std::endl;
							//		collisionsCount++;

							//		((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l]))|| ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l]))||
							//			((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l])))||
							//			(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||
							//			((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l]))));

							//		if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//			std::cout << "������������" << std::endl;
							//			collisionsCount++;
							//}
						}
					}
				}
			}
		}

	}
	std::cout << "����� ������������:" << collisionsCount << std::endl;
}

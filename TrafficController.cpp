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
	numStations = railway.getNumStations();//���������� ���������� �������
	numTrains = trains.size();//���������� ���������� �������
	for (size_t i = 0; i < numTrains; i++) {//�������������� ������� ���������� ������
		std::vector<unsigned> train(numStations, 0);
		schedule.push_back(train);
	}

	

	for (size_t i = 0; i < numTrains; i++) {
		std::vector<unsigned> path = trains[i].getPath();
		unsigned pathLen = path.size();//���������� ����� ������� � �������� ������

		schedule[i][path[0] - 1] = trains[i].getStarttime(); //������ ����� ����������� ������ �� ������ ������� ��������
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][path[p]-1] =														//� ���������� ������� ��� i-�� ������ 
				schedule[i][path[p-1] - 1] +												//����� �������� �� p-� ������� �� ��� �������� 
				railway.getStationsGraph()[path[p]-1][path[p - 1]-1]/ trains[i].getVelocity();					//����� ����������� ����� (p-1)-� � p-� ���������, 
																							//�������� �� �������� (�� ������� = 1 ��� ����) 
																							//+ ����� ������� � ���������� �������
		}
	}


}

int TrafficController::findCollisions(Railway& railway, bool flag)//����� ������ ������������ �� ����������
{

	unsigned collisionsCount = 0;
	for (size_t k = 0; k < numStations;k++) {//������ �� ��������
		for (size_t l = k+1; l < numStations; l++) {//�.�. ���� ����� k � l ��������� = ���� ����� l � k ���������, 
													//�� ������� ��������� - ������������ � �������� ������ �� �������� �������
			if ((railway.getStationsGraph()[k][l] != 0)) {//��������� ������ ������������ ���� (�.�. ���������� ����� ��������� �� ����� 0)
				for (size_t i = 0; i < numTrains; i++) {//������ �� �������
					for (size_t j = i+1; j < numTrains; j++) {//���� ����� i ������������ � ������� j, �� ����� � ��������. 
															  //�.�. ��� ���� ������������ � �������� ��������� ������������ j � i �� ���������
						if ((schedule[i][k] != 0) && (schedule[j][k] != 0) && (schedule[i][l] != 0) && (schedule[j][l] != 0)) {//���� ����� �������� ������ � ����� �� ������� ������� �� �������
							
							if ((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l])) || ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l])) ||//���� ����� �������� ������ ������ �� ������� k ��� ������� l
								((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l]))) ||//�������� � �������� ������� ����� �������� ������� ������ �� ������� k �
								(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||//��������� �� ������� l, �� ���������� ������������
								((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l]))))  
																																														   
																																														   
							{

								if (!flag) {
									std::cout << "���� ������������" << std::endl;
									return -1;
								}
								std::cout << "������������" << std::endl;
								collisionsCount++;

							}
						}
					}
				}
			}
		}

	}
	if (collisionsCount){
		std::cout << "����� ������������:" << collisionsCount << std::endl;
	}

	return 0;
}

std::vector<std::vector<unsigned>> TrafficController::getSchedule() const
{
	return schedule;
}

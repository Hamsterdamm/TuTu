#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Railway.h"
#include "Train.h"


void getTrainsSchedules(std::vector<Train>& trains, const char* filename);//������� ���������� �� ����� ���������� � �������
void getStationsGraph(Railway& railway, const char* filename);//������� ���������� �� ����� ������������ �/� ����

int main() {

	setlocale(LC_ALL, "RUS");//��������� ������� ���������

	std::vector<Train> trains;//������ �������
	getTrainsSchedules(trains, "schedule.txt");//��������� �� ����� ���������� � �������

	Railway RZD;//�/� ����
	getStationsGraph(RZD, "graph.txt");//��������� �� ����� ������������ � / � ����

	system("pause");
	return 0;
}

void getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����
		std::cout << "���� �� ������!" << std::endl;
		system("pause");
		//return -1;
	}
	else
	{
		std::getline(file, line);//����� ������ � �����
		while (std::getline(file, line)) {//���� ������� ������ � �����
			Train train;//������ ������ �����

			std::replace(line.begin(), line.end(), '-', ' ');//�������� "-" �� ������� �� ������� ������ � ���������
			std::istringstream iss(line);//���������� ������ �� ������-������ � ��������� �����

			iss >> train.name;//������ ������� ������ - �������� ������

			unsigned station;//������� � �������� ������
			while (iss >> station) {
				train.path.push_back(station);//��������� ������ �������� ������
			}

			trains.push_back(train);//��������� ����� � ������ �������
		}

		file.close();//��������� ����
	}


}

void getStationsGraph(Railway & railway, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����
		std::cout << "���� �� ������!" << std::endl;
		system("pause");
		//return -1;
	}
	else
	{
		std::getline(file, line);//����� ������ � �����
		while (std::getline(file, line)) {//���� ������� ������ � �����
			std::vector<unsigned> graphLine;//������ ������� ��������� �����
			std::istringstream iss(line);//���������� ������ �� ������-������ � ��������� �����

			iss.ignore(1024, ' ');//���������� ������ ������

			unsigned distance;//���������� ����� ���������
			while (iss >> distance) {
				graphLine.push_back(distance);//��������� ������ ������� ��������� ����� ������� � ����������� ����� ���������
			}

			railway.stationsGraph.push_back(graphLine);//��������� ������ � ������� ���������
		}

		file.close();//��������� ����
	}


}

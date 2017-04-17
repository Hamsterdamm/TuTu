#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <locale>

#include "Train.h"
#include "TrafficController.h"


int getTrainsSchedules(std::vector<Train>& trains, const char* filename);//������� ���������� �� ����� ���������� � �������
int getStationsGraph(Railway &stationsGraph, const char* filename);//������� ���������� �� ����� ������������ �/� ����
void question(bool &flag);//������ ������� �� ������������: ������� ��� �� �������

char* trainsFileName = "input/schedule_2.txt";
char* graphFileName = "input/graph_2.txt";

int main() {

	setlocale(LC_ALL, "RUS");//��������� ������� ���������

	std::vector<Train> trains;//������ �������
	if (getTrainsSchedules(trains, trainsFileName) == -1) {	//��������� �� ����� ���������� � �������
		std::cout << "���� �� ������!" << std::endl;		//���� ���� �� ������ - ���������� -1 ��������� ���������
		std::cout << "��� ������ ������� enter.";
		std::cin.get();
		return -1;
	}

	Railway RZD;//�/� ����
	if (getStationsGraph(RZD, graphFileName) == -1) {			//��������� �� ����� ������������ ����
		std::cout << "���� �� ������!" << std::endl;		//���� ���� �� ������ - ���������� -1 ��������� ���������
		std::cout << "��� ������ ������� enter.";
		std::cin.get();
		return -1;
	}

	TrafficController controller;//���������

	bool flag(false);//����: ������� ������������ - true, �� ������� - false
	question(flag);//������ ������� �� ������������: ������� ��� �� �������

	if (controller.makeSchedule(RZD, trains) != 0) {//��������� ����������
		std::cout << "���������� ��������� ���������� �������!" << std::endl;
		std::cout << "��� ��������� ��������� ����������� ��������������� ���� ����� ���������." << std::endl;
		std::cout << "��� ������ ������� enter.";
		std::cin.get();
		return -1;
	}


	switch (controller.findCollisions(RZD, flag)) {//�������� �� ������������
		case 0:{
			std::cout << "������������ �� ����������." << std::endl;
			break;
		}
		case -1:{
			std::cout << "���������� ������������!" << std::endl;
			break;
		}
		default:{
			std::cout << "���������� ������������. ����� ������������: " << controller.findCollisions(RZD, flag) << std::endl;
		}
	}

	std::cout << "��� ������ ������� enter.";
	std::cin.get();
	return 0;
}

int getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����. ���� ���� �� ������ - ���������� -1 � ������� �� �������
		return -1;
	}

	std::getline(file, line);//����� ������ ������ � �����
	while (std::getline(file, line)) {//���� ������� ������ � �����
		std::string name;//�������� ������
		std::vector<unsigned> path;//������� ������

		std::replace(line.begin(), line.end(), '-', ' ');//�������� "-" �� ������� �� ������� ������ � ���������
		std::istringstream iss(line);//���������� ������ �� ������-������ � ��������� �����

		iss >> name;//������ ������� ������ - �������� ������

		unsigned station;//������� � �������� ������
		while (iss >> station) {
			path.push_back(station);//��������� ������ �������� ������
		}

		Train train(name, path);//������� ������ ������ ����� � ��������� ��������� � ���������
		trains.push_back(train);//��������� ����� � ������ �������
	}

	file.close();//��������� ����

	return 0;
}

int getStationsGraph(Railway &stationsGraph, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����. ���� ���� �� ������ - ���������� -1 � ������� �� �������
		return -1;
	}

	std::getline(file, line);//����� ������ ������ � �����
	while (std::getline(file, line)) {//���� ������� ������ � �����
		std::vector<unsigned> graphLine;//������ ������� ��������� �����
		std::istringstream iss(line);//���������� ������ �� ������-������ � ��������� �����

		iss.ignore(1024, ' ');//���������� ������ ������� (�������� �������)

		unsigned distance;//���������� ����� ���������
		while (iss >> distance) {
			graphLine.push_back(distance);//��������� ������ ������� ��������� ����� ������� � ����������� ����� ���������
		}

		stationsGraph.push_back(graphLine);//��������� ������ � ������� ���������
	}


	file.close();//��������� ����

	return 0;
}

void question(bool &flag)//������ ������� �� ������������: ������� ��� �� �������
{
	std::cout << "���������� ��� ������������? y/n" << std::endl;
	char ans;
	std::cin >> ans;
	if (ans == 'y')
		flag = true;
	else if (ans == 'n')
		flag = false;
	else {
		std::cout << "������������ ����! ��������� �������!" << std::endl;
		question(flag = false);
	}
}

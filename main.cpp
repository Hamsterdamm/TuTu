#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>

#include "Railway.h"
#include "Train.h"
#include "TrafficController.h"

typedef std::vector<std::vector<unsigned>> RailwayType;

int getTrainsSchedules(std::vector<Train>& trains, const char* filename);//������� ���������� �� ����� ���������� � �������
int getStationsGraph(std::vector<std::vector<unsigned>> &stationsGraph, const char* filename);//������� ���������� �� ����� ������������ �/� ����

int main() {

	setlocale(LC_ALL, "RUS");//��������� ������� ���������

	std::vector<Train> trains;//������ �������
	getTrainsSchedules(trains, "schedule.txt");//��������� �� ����� ���������� � �������

	RailwayType stationsGraph;
	getStationsGraph(stationsGraph, "graph.txt");//��������� �� ����� ������������ � / � ����
	Railway RZD(stationsGraph);//�/� ����

	TrafficController controller;
	std::cout << "���������� ��� ������������? y/n" << std::endl;
	char ans;
	bool flag(false);
	std::cin >> ans;
	if (ans == 'y')
		flag = true;

	controller.makeSchedule(RZD, trains);//��������� ����������

	switch (controller.findCollisions(RZD, flag)) {//�������� �� ������������
	case 0:{
		std::cout << "������������ �� ����������." << std::endl; 
		break; 
	}
	case 1:{
		std::cout << "���������� ������������!" << std::endl;
		break; 
	}
	default:{		
		std::cout << "���������� ������������. ����� ������������: " << controller.findCollisions(RZD, flag) << std::endl; 
	}

	}

	_getch();
	return 0;
}

int getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����. ���� ���� �� ������ - ���������� -1 � ������� �� �������
		std::cout << "���� �� ������!" << std::endl;
		system("pause");
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

int getStationsGraph(std::vector<std::vector<unsigned>> &stationsGraph, const char * filename)
{
	std::string line;//�����-������
	std::ifstream file(filename, std::ios_base::in);//������� �������� �����

	if (!file.is_open()) { //�������� ������� �����. ���� ���� �� ������ - ���������� -1 � ������� �� �������
		std::cout << "���� �� ������!" << std::endl;
		system("pause");
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

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Railway.h"
#include "Train.h"


void getTrainsSchedules(std::vector<Train>& trains, const char* filename);

int main() {

	setlocale(LC_ALL, "RUS");//поддержка русской кодировки

	std::vector<Train> trains;
	getTrainsSchedules(trains, "schedule.txt");

	system("pause");
	return 0;
}

void getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;
	std::ifstream input(filename, std::ios_base::in);//входной файловый поток

	if (!input.is_open()) {
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		//return -1;
	}
	else
	{
		std::getline(input, line);
		while (std::getline(input, line)) {
			Train train;

			std::replace(line.begin(), line.end(), '-', ' ');
			std::istringstream iss(line);

			iss >> train.name;

			unsigned point;
			while (iss >> point) {
				train.path.push_back(point);
			}
			trains.push_back(train);

		}

		input.close();
	}


}

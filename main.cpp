#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Railway.h"
#include "Train.h"
#include "TrafficController.h"


void getTrainsSchedules(std::vector<Train>& trains, const char* filename);//функция считывания из файла информации о поездах
void getStationsGraph(Railway& railway, const char* filename);//функция считывания из файла конфигурации ж/д сети

int main() {

	setlocale(LC_ALL, "RUS");//поддержка русской кодировки

	std::vector<Train> trains;//вектор поездов
	getTrainsSchedules(trains, "schedule.txt");//считываем из файла информации о поездах

	Railway RZD;//ж/д сеть
	getStationsGraph(RZD, "graph.txt");//считываем из файла конфигурацию ж / д сети

	TrafficController controller;
	std::cout << "Подсчитать все столкновения?" << std::endl;
	char ans;
	bool flag(false);
	std::cin >> ans;
	if (ans == 'y')
		flag = true;

	controller.makeSchedule(RZD, trains);//заполняем расписание
	controller.findCollisions(RZD, flag);//ищем столкновения

	system("pause");
	return 0;
}

void getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		//return -1;
	}
	else
	{
		std::getline(file, line);//вывод строки в буфер
		while (std::getline(file, line)) {//пока выводим строки в буфер
			std::string name;//название поезда
			std::vector<unsigned> path;//маршрут поезда

			std::replace(line.begin(), line.end(), '-', ' ');//заменяем "-" на пробелы во входных данных о маршрутах
			std::istringstream iss(line);//направляем данные из буфера-строки в строковый поток

			iss >> name;//первый элемент строки - название поезда

			unsigned station;//станция в маршруте поезда
			
			while (iss >> station) {
				path.push_back(station);//заполняем вектор маршрута поезда
			}

			Train train(name, path);//объект класса Поезд инициализируется значениями названия и маршрута
			trains.push_back(train);//добавляем поезд в вектор поездов
		}

		file.close();//закрываем файл
	}


}

void getStationsGraph(Railway & railway, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		//return -1;
	}
	else
	{
		std::getline(file, line);//вывод строки в буфер
		while (std::getline(file, line)) {//пока выводим строки в буфер
			std::vector<unsigned> graphLine;//строка матрицы смежности графа
			std::istringstream iss(line);//направляем данные из буфера-строки в строковый поток

			iss.ignore(1024, ' ');//пропускаем первую строку

			unsigned distance;//расстояние между станциями
			while (iss >> distance) {
				graphLine.push_back(distance);//заполняем строку матрицы смежности графа данными о расстояниях между станциями
			}

			railway.stationsGraph.push_back(graphLine);//добавляем строку к матрице смежности
		}


		file.close();//закрываем файл
	}


}

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Railway.h"
#include "Train.h"
#include "TrafficController.h"


int getTrainsSchedules(std::vector<Train>& trains, const char* filename);//функция считывания из файла информации о поездах
int getStationsGraph(std::vector<std::vector<unsigned>> &stationsGraph, const char* filename);//функция считывания из файла конфигурации ж/д сети

int main() {

	setlocale(LC_ALL, "RUS");//поддержка русской кодировки

	std::vector<Train> trains;//вектор поездов
	getTrainsSchedules(trains, "schedule.txt");//считываем из файла информации о поездах

	std::vector<std::vector<unsigned>> stationsGraph;
	getStationsGraph(stationsGraph, "graph.txt");//считываем из файла конфигурацию ж / д сети
	Railway RZD(stationsGraph);//ж/д сеть

	TrafficController controller;
	std::cout << "Подсчитать все столкновения? y/n" << std::endl;
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

int getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла. если файл не найден - возвращаем -1 и выходим из функции
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		return -1;
	}

	std::getline(file, line);//вывод первой строки в буфер
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

		Train train(name, path);//создаем объект класса Поезд с принятыми названием и маршрутом
		trains.push_back(train);//добавляем поезд в вектор поездов
	}

	file.close();//закрываем файл

	return 0;
}

int getStationsGraph(std::vector<std::vector<unsigned>> &stationsGraph, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла. если файл не найден - возвращаем -1 и выходим из функции
		std::cout << "Файл не найден!" << std::endl;
		system("pause");
		return -1;
	}

	std::getline(file, line);//вывод первой строки в буфер
	while (std::getline(file, line)) {//пока выводим строки в буфер
		std::vector<unsigned> graphLine;//строка матрицы смежности графа
		std::istringstream iss(line);//направляем данные из буфера-строки в строковый поток

		iss.ignore(1024, ' ');//пропускаем первый столбец (названия станций)

		unsigned distance;//расстояние между станциями
		while (iss >> distance) {
			graphLine.push_back(distance);//заполняем строку матрицы смежности графа данными о расстояниях между станциями
		}

		stationsGraph.push_back(graphLine);//добавляем строку к матрице смежности
	}


	file.close();//закрываем файл

	return 0;
}

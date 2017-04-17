#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <locale>

#include "Train.h"
#include "TrafficController.h"


int getTrainsSchedules(std::vector<Train>& trains, const char* filename);//функция считывания из файла информации о поездах
int getStationsGraph(Railway &stationsGraph, const char* filename);//функция считывания из файла конфигурации ж/д сети
void question(bool &flag);//запрос решения от пользователя: считать или не считать

char* trainsFileName = "input/schedule_2.txt";
char* graphFileName = "input/graph_2.txt";

int main() {

	setlocale(LC_ALL, "RUS");//поддержка русской кодировки

	std::vector<Train> trains;//вектор поездов
	if (getTrainsSchedules(trains, trainsFileName) == -1) {	//считываем из файла информации о поездах
		std::cout << "Файл не найден!" << std::endl;		//если файл не найден - возвращаем -1 завершаем программу
		std::cout << "Для выхода нажмите enter.";
		std::cin.get();
		return -1;
	}

	Railway RZD;//ж/д сеть
	if (getStationsGraph(RZD, graphFileName) == -1) {			//считываем из файла конфигурацию сети
		std::cout << "Файл не найден!" << std::endl;		//если файл не найден - возвращаем -1 завершаем программу
		std::cout << "Для выхода нажмите enter.";
		std::cin.get();
		return -1;
	}

	TrafficController controller;//диспетчер

	bool flag(false);//флаг: считать столкновения - true, не считать - false
	question(flag);//запрос решения от пользователя: считать или не считать

	if (controller.makeSchedule(RZD, trains) != 0) {//заполняем расписание
		std::cout << "Невозможно составить расписание поездов!" << std::endl;
		std::cout << "Для некоторых маршрутов отсутствуют железнодорожные пути между станциями." << std::endl;
		std::cout << "Для выхода нажмите enter.";
		std::cin.get();
		return -1;
	}


	switch (controller.findCollisions(RZD, flag)) {//проверка на столкновения
		case 0:{
			std::cout << "Столкновения не произойдут." << std::endl;
			break;
		}
		case -1:{
			std::cout << "Произойдут столкновения!" << std::endl;
			break;
		}
		default:{
			std::cout << "Произойдут столкновения. Число столкновений: " << controller.findCollisions(RZD, flag) << std::endl;
		}
	}

	std::cout << "Для выхода нажмите enter.";
	std::cin.get();
	return 0;
}

int getTrainsSchedules(std::vector<Train>& trains, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла. если файл не найден - возвращаем -1 и выходим из функции
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

int getStationsGraph(Railway &stationsGraph, const char * filename)
{
	std::string line;//буфер-строка
	std::ifstream file(filename, std::ios_base::in);//входной файловый поток

	if (!file.is_open()) { //проверка наличия файла. если файл не найден - возвращаем -1 и выходим из функции
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

void question(bool &flag)//запрос решения от пользователя: считать или не считать
{
	std::cout << "Подсчитать все столкновения? y/n" << std::endl;
	char ans;
	std::cin >> ans;
	if (ans == 'y')
		flag = true;
	else if (ans == 'n')
		flag = false;
	else {
		std::cout << "Некорректный ввод! Повторите попытку!" << std::endl;
		question(flag = false);
	}
}

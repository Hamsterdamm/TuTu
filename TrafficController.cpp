#include "TrafficController.h"
#include <iostream>



TrafficController::TrafficController()
{
}


TrafficController::~TrafficController()
{
}

void TrafficController::makeSchedule(Railway& railway, std::vector<Train> trains)//метод построения расписания поездов по станциям
{
	numStations = railway.stationsGraph.size();//определяем количество станций
	numTrains = trains.size();//определяем количество поездов
	for (size_t i = 0; i < numTrains; i++) {//инициализируем матрицу расписания нулями
		std::vector<long int> train(numStations, 0);
		schedule.push_back(train);
	}

	for (size_t i = 0; i < numTrains; i++) {
		unsigned time = trains[i].starttime;//инициализируем переменную времени временем отправления поезда с начальной станции (по условию = 0 для всех)
		unsigned pathLen = trains[i].path.size();//определяем число станций в маршруте поезда
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][trains[i].path[p]-1] = 
				time + railway.stationsGraph[trains[i].path[p]-1][trains[i].path[p - 1]-1]/ trains[i].velocity;//в расписании поездов для i-го поезда 
																																			  //время прибытия на p-ю станцию из его маршрута 
																																			  //равно расстоянияю между (p-1)-й и p-й станциями, 
																																			  //деленное на скорость (по условию = 1 для всех) 
																																			  //+ время отбытия с предыдущей станции
			time = schedule[i][trains[i].path[p]-1];//запоминаем время прибытия для расчета следующей станции
		}
	}


}

void TrafficController::findCollisions(Railway& railway)//метод поиска столкновений по расписанию
{
	int k(0), l(0);
	while (railway.stationsGraph[k][l] != 0) {
		for (size_t i = 0; i < numTrains; i++) {
			for (size_t j = 0; (j < numTrains) && (j != i); j++) {
				if (!((schedule[i][k]<schedule[j][k]&& schedule[i][l]<schedule[j][l])|| (schedule[i][k]>schedule[j][k] && schedule[i][l]>schedule[j][l]))) {
					std::cout<<"Столкновение"<<std::endl;
				}
			}
		}
		k++; l++;
	}
}

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
		std::vector<unsigned> path = trains[i].getPath();
		//unsigned time = trains[i].getStarttime();//инициализируем переменную времени временем отправления поезда с начальной станции (по условию = 0 для всех)
		unsigned pathLen = path.size();//определяем число станций в маршруте поезда

		schedule[i][path[0] - 1] = trains[i].getStarttime();
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][path[p]-1] = 
				schedule[i][path[p-1] - 1] + railway.stationsGraph[path[p]-1][path[p - 1]-1]/ trains[i].getVelocity();//в расписании поездов для i-го поезда 
																																			  //время прибытия на p-ю станцию из его маршрута 
																																			  //равно расстоянияю между (p-1)-й и p-й станциями, 
																																			  //деленное на скорость (по условию = 1 для всех) 
																																			  //+ время отбытия с предыдущей станции
			//time = schedule[i][path[p]-1];//запоминаем время прибытия для расчета следующей станции
		}
	}


}

void TrafficController::findCollisions(Railway& railway)//метод поиска столкновений по расписанию
{

	unsigned collisionsCount = 0;
	for (size_t k = 0; k < numStations;k++) {
		for (size_t l = k+1; l < numStations; l++) {
			if ((railway.stationsGraph[k][l] != 0)) {
				for (size_t i = 0; i < numTrains; i++) {
					for (size_t j = i+1; j < numTrains; j++) {
						if ((schedule[i][k] != 0) && (schedule[j][k] != 0) && (schedule[i][l] != 0) && (schedule[j][l] != 0)) {//если время прибытия поезда в любую из станций участка не нулевое
							
							if ((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l])) || ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l])) ||
								((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l]))) ||
								(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||
								((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l])))) {
								
								std::cout << "Столкновение" << std::endl;
								collisionsCount++;

							}
							
							//if (((((static_cast<long>(schedule[i][k])) - schedule[j][k]) < 0) && (((static_cast<long>(schedule[i][l])) - schedule[j][l]) < 0)) || ((((static_cast<long>(schedule[i][k])) - schedule[j][k]) > 0) && (((static_cast<long>(schedule[i][l])) - schedule[j][l]) > 0))) {
							//	//если поезда движутся в одном направлении

							//	if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//		std::cout << "Столкновение" << std::endl;
							//		collisionsCount++;
							//	}
							//}
							//else {
							//	//если поезда движутся в противоположном направлении

							//	if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//		std::cout << "Столкновение" << std::endl;
							//		collisionsCount++;

							//		((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l]))|| ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l]))||
							//			((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l])))||
							//			(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||
							//			((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l]))));

							//		if ((!(((schedule[i][k] < schedule[j][k]) && (schedule[i][l] < schedule[j][l])) || ((schedule[i][k] > schedule[j][k]) && (schedule[i][l] > schedule[j][l]))))) {
							//			std::cout << "Столкновение" << std::endl;
							//			collisionsCount++;
							//}
						}
					}
				}
			}
		}

	}
	std::cout << "Число столкновений:" << collisionsCount << std::endl;
}

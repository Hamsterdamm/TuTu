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
	numStations = railway.getNumStations();//определяем количество станций
	numTrains = trains.size();//определяем количество поездов
	for (size_t i = 0; i < numTrains; i++) {//инициализируем матрицу расписания нулями
		std::vector<unsigned> train(numStations, 0);
		schedule.push_back(train);
	}

	

	for (size_t i = 0; i < numTrains; i++) {
		std::vector<unsigned> path = trains[i].getPath();
		unsigned pathLen = path.size();//определяем число станций в маршруте поезда

		schedule[i][path[0] - 1] = trains[i].getStarttime(); //задаем время отправления поезда от первой станции маршрута
		for (size_t p = 1; p < pathLen; p++) {
			schedule[i][path[p]-1] =														//в расписании поездов для i-го поезда 
				schedule[i][path[p-1] - 1] +												//время прибытия на p-ю станцию из его маршрута 
				railway.getStationsGraph()[path[p]-1][path[p - 1]-1]/ trains[i].getVelocity();					//равно расстоянияю между (p-1)-й и p-й станциями, 
																							//деленное на скорость (по условию = 1 для всех) 
																							//+ время отбытия с предыдущей станции
		}
	}


}

int TrafficController::findCollisions(Railway& railway, bool flag)//метод поиска столкновений по расписанию
{

	unsigned collisionsCount = 0;
	for (size_t k = 0; k < numStations;k++) {//проход по станциям
		for (size_t l = k+1; l < numStations; l++) {//т.к. путь между k и l станциями = пути между l и k станциями, 
													//то матрица смежности - симметричная и проходим только по половине матрицы
			if ((railway.getStationsGraph()[k][l] != 0)) {//проверяем только существующие пути (т.е. расстояние между станциями не равно 0)
				for (size_t i = 0; i < numTrains; i++) {//проход по поездам
					for (size_t j = i+1; j < numTrains; j++) {//если поезд i сталкивается с поездом j, то верно и обратное. 
															  //т.о. это одно столкновение и повторно проверять столкновение j и i не требуется
						if ((schedule[i][k] != 0) && (schedule[j][k] != 0) && (schedule[i][l] != 0) && (schedule[j][l] != 0)) {//если время прибытия поезда в любую из станций участка не нулевое
							
							if ((((schedule[i][k] >= schedule[j][k]) && (schedule[i][k] <= schedule[j][l])) || ((schedule[i][k] <= schedule[j][k]) && (schedule[i][k] >= schedule[j][l])) ||//если время прибытия одного поезда на станцию k или станцию l
								((schedule[i][l] >= schedule[j][k]) && (schedule[i][l] <= schedule[j][l])) || ((schedule[i][l] <= schedule[j][k]) && (schedule[i][l] >= schedule[j][l]))) ||//попадает в интервал времени между отбытием другого поезда со станции k и
								(((schedule[j][k] >= schedule[i][k]) && (schedule[j][k] <= schedule[i][l])) || ((schedule[j][k] <= schedule[i][k]) && (schedule[j][k] >= schedule[i][l])) ||//прибытием на станцию l, то произойдет столкновение
								((schedule[j][l] >= schedule[i][k]) && (schedule[j][l] <= schedule[i][l])) || ((schedule[j][l] <= schedule[i][k]) && (schedule[j][l] >= schedule[i][l]))))  
																																														   
																																														   
							{

								if (!flag) {
									std::cout << "Есть столкновения" << std::endl;
									return -1;
								}
								std::cout << "Столкновение" << std::endl;
								collisionsCount++;

							}
						}
					}
				}
			}
		}

	}
	if (collisionsCount){
		std::cout << "Число столкновений:" << collisionsCount << std::endl;
	}

	return 0;
}

std::vector<std::vector<unsigned>> TrafficController::getSchedule() const
{
	return schedule;
}

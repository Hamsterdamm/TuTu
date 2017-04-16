#include <vector>
#include <string>

#ifndef _TRAIN_H_
#define _TRAIN_H_

class Train {

private:
	int starttime;//время отправления поезда с начальной станции
	int velocity;//скорость поезда
	std::string name;//название поезда
	std::vector<unsigned> path;	//маршрут поезда

public:

	Train();//конструктор класса, время отправления и скорость по умолчанию = 1
	Train(std::string name, std::vector<unsigned> path);//конструктор класса поезд с входными данными об названии и маршруте
	~Train();//деструктор

	std::string getName() const;//метод получения названия поезда
	std::vector<unsigned> getPath() const;//метод получения маршрута поезда
	int getStarttime() const;//метод получения времени отправления поезда
	int getVelocity() const;//метод получения скорости поезда

};

#endif //_TRAIN_H_
#include "Train.h"

Train::Train():starttime(1),velocity(1)//конструктор класса, время отправления и скорость по умолчанию = 1
{
}

Train::Train(std::string _name, std::vector<unsigned> _path) : starttime(1), velocity(1), name(_name), path(_path)//конструктор класса поезд с входными данными об названии и маршруте
{
}

Train::~Train()//деструктор
{
}

std::string Train::getName() const//метод получения названия поезда
{
	return name;
}

std::vector<unsigned> Train::getPath() const//метод получения маршрута поезда
{
	return path;
}

int Train::getStarttime() const//метод получения времени отправления поезда
{
	return starttime;
}

int Train::getVelocity() const//метод получения скорости поезда
{
	return velocity;
}

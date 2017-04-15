#include "Train.h"

Train::Train():starttime(0),velocity(1)
{
}

Train::Train(std::string _name, std::vector<unsigned> _path) : starttime(0), velocity(1), name(_name), path(_path)
{
}

Train::~Train()
{
}

void Train::setName()
{

}

std::string Train::getName() const
{
	return name;
}

std::vector<unsigned> Train::getPath() const
{
	return path;
}

int Train::getStarttime() const
{
	return starttime;
}

int Train::getVelocity() const
{
	return velocity;
}

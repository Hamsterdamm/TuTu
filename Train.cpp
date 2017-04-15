#include "Train.h"

Train::Train():starttime(0),velocity(1)
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

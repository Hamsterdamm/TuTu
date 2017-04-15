#include "Train.h"

Train::Train():starttime(0),velocity(1)
{
}

Train::~Train()
{
}

char * Train::getName() const
{
	return name;
}

char * Train::getPath() const
{
	return nullptr;
}

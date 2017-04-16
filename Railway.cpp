#include "Railway.h"

Railway::Railway()
{
}

Railway::Railway(std::vector<std::vector<unsigned>> _stationsGraph):stationsGraph(_stationsGraph), numStations(_stationsGraph.size())
{
}

Railway::~Railway()
{
}

unsigned Railway::getNumStations() const
{
	return numStations;
}

std::vector<std::vector<unsigned>> Railway::getStationsGraph() const
{
	return stationsGraph;
}

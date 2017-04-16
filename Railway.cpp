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

//int Railway::getDistance(int from, int to) const
//{
//	return 0;
//}
//
std::vector<std::vector<unsigned>> Railway::getStationsGraph() const
{
	return stationsGraph;
}

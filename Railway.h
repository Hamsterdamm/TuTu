#include <vector>

#ifndef _RAILWAY_H_
#define _RAILWAY_H_

typedef std::vector<std::vector<unsigned>> RailwayType;

class Railway {
private:

	unsigned numStations;
	std::vector<std::vector<unsigned>> stationsGraph;

public:

	Railway();//конструктор
	Railway(std::vector<std::vector<unsigned>> _stationsGraph);//конструктор
	~Railway();//деструктор


	unsigned getNumStations() const;
	std::vector<std::vector<unsigned>> getStationsGraph() const;
};

#endif //_RAILWAY_H_
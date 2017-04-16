#include <vector>

#ifndef _RAILWAY_H_
#define _RAILWAY_H_

class Railway {
private:

	unsigned numStations;
	std::vector<std::vector<unsigned>> stationsGraph;

public:

	Railway();//�����������
	Railway(std::vector<std::vector<unsigned>> _stationsGraph);//�����������
	~Railway();//����������


	unsigned getNumStations() const;
	//int getDistance(int from,int to) const;
	std::vector<std::vector<unsigned>> getStationsGraph() const;
};

#endif //_RAILWAY_H_
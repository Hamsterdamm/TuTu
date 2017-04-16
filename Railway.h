#include <vector>

#ifndef _RAILWAY_H_
#define _RAILWAY_H_

class Railway {
public:


	std::vector<std::vector<unsigned>> stationsGraph;

	Railway();//конструктор
	~Railway();//деструктор



	//int getDistance(int from,int to) const;
	//std::vector<std::vector<unsigned>> getGraph() const;
};

#endif //_RAILWAY_H_
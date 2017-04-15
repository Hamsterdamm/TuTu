#include <vector>

#ifndef _RAILWAY_H_
#define _RAILWAY_H_

class Railway {
private:
	

public:
	std::vector<std::vector<unsigned>> stationsGraph;
	Railway();
	~Railway();

	int getDistance(int from,int to) const;
};

#endif //_RAILWAY_H_
#include <vector>

#ifndef _RAILWAY_H_
#define _RAILWAY_H_

class Railway {
private:
	std::vector<std::vector<unsigned>> stationsGraph;

public:

	Railway();
	~Railway();

	int getDistance(int from,int to) const;
};

#endif //_RAILWAY_H_
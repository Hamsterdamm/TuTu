#ifndef _RAILWAY_H_
#define _RAILWAY_H_

class Railway {
private:
	int** stationsGraph;

public:

	Railway();
	~Railway();

	int getDistance(int from,int to) const;
};

#endif //_RAILWAY_H_
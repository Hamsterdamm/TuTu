#include <vector>
#include <string>

#ifndef _TRAIN_H_
#define _TRAIN_H_

class Train {

private:
	int starttime;
	int velocity;
	std::string name;
	std::vector<unsigned> path;	

public:

	Train();
	Train(std::string name, std::vector<unsigned> path);
	~Train();
	void setName();
	std::string getName() const;
	std::vector<unsigned> getPath() const;
	int getStarttime() const;
	int getVelocity() const;

};

#endif //_TRAIN_H_
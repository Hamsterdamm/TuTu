#include <vector>
#include <string>

#ifndef _TRAIN_H_
#define _TRAIN_H_

class Train {

private:

	int starttime;
	int velocity;

public:
	std::string name;
	std::vector<unsigned> path;

	Train();
	~Train();
	void setName() const;
	std::string getName() const;
	std::vector<unsigned> getPath() const;

};

#endif //_TRAIN_H_
#ifndef _TRAIN_H_
#define _TRAIN_H_

class Train {

private:
	char* name;
	int starttime;
	int velocity;

public:

	Train();
	~Train();
	char* getName() const;
	char* getPath() const;

};

#endif //_TRAIN_H_
#ifndef _TrafficController_H_
#define _TrafficController_H_

class TrafficController
{
private:
	int** schedule;

public:
	TrafficController();
	~TrafficController();
	void makeSchedule();
	void findCollisions();
};

#endif//_TrafficController_H_
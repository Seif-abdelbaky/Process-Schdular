#pragma once
#include "Processor.h"
#include"LinkedQueue.h"
#include "PriorityQueue.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class RR : public Processor
{
private :
	int TimeSlice;
	int RTF;
public:

	RR(int x, int y, int T);
	void set_time(int x);
	int get_time() const;
	int ScheduleALGO(Process*& done, int TS);
	void setBusy(bool b);
	bool isBusy();
	void  setTimeLeftInQueue(int t);

	void printRDY();
	int countRDY();
	bool SigKill(Process*& Killed, int idKilled, bool& hasChildren);
	bool fork(int T, Process*& forkPtr);
	~RR();
};


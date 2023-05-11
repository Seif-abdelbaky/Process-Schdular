#pragma once
#include "Processor.h"
#include "PriorityQueue.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class SJF : public Processor
{
public:
	SJF(int T);

	int ScheduleALGO(Process*& done, int TS);

	void setBusy(bool b);
	bool isBusy();
	void  setTimeLeftInQueue(int t);

	void printRDY();
	int countRDY();
	bool SigKill(Process*& Killed, int idKilled, bool& hasChildren);
	bool fork(int T, Process*& forkPtr);
	~SJF();
};


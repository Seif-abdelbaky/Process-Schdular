#pragma once
#include<iostream>

#include"LinkedQueue.h"
#include"Processor.h"
#include <cstdlib>
class FCFS :public Processor
{
private: 
	int MaxW;
public:
	FCFS(int x, int T);
	int virtual ScheduleALGO(Process*& done, int TS);
	void setBusy(bool b);
	bool isBusy();
	void  setTimeLeftInQueue(int t);
	void printRDY();
	int countRDY();
	bool SigKill(Process*& Killed, int idKilled, bool& hasChildren);
	bool fork(int T, Process*& forkPtr, int TotalProcess);
	~FCFS();
};


#pragma once
#include"QueueADT.h"
#include"process.h"
class Processor
{
protected:
	int TimeLeftInQueue;
	Process* runPtr;
	QueueADT<Process*>* readyQ;
	bool busy;
	int TotalBusy = 0;
	int CoolingT;
	bool overHeated = false;
	int waiting = 0;
public:
	void overHeat(Process*& temp);
	bool isHeated();
	int virtual ScheduleALGO(Process* & done, int TS) = 0;
	void virtual setBusy(bool b) = 0;
	bool virtual isBusy() = 0;
	void virtual setTimeLeftInQueue(int t) = 0;
	bool virtual SigKill(Process*& Killed, int idKilled,bool & hasChildren) = 0;
	bool virtual fork(int T,Process*&forkPtr, int TotalProcess) = 0;
	int virtual getter_total();
	int virtual getTimeLeftInQueue();
	bool virtual AddtoQ(Process* x);
	void virtual printRDY() = 0;
	int virtual countRDY() = 0;
	Process* getRun();
	Process* gimme_something(bool noNeed);
	bool EmptyReady();
	int TimeLeftRunPtr();
	int TimeLeftReady();
	int getTotalBusy();
};


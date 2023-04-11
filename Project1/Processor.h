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
public:
	void virtual ScheduleAlgo()=0;
	bool virtual Run(Process* & done) = 0;
	void virtual setBusy(bool b) = 0;
	bool virtual isBusy() = 0;
	void virtual setTimeLeftInQueue(int t) = 0;
	int virtual getTimeLeftInQueue() = 0;
	virtual QueueADT<Process*>*  getReadyQ() = 0;
	bool virtual AddtoQ(Process* x)
	{
		bool flag = readyQ->enqueue(x);
		if (flag)
			TimeLeftInQueue += x->getCPUTime();
		return(flag);
	}
};


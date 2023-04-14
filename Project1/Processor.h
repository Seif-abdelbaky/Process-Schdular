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
	int virtual Run(Process* & done, int TS) = 0;
	void virtual setBusy(bool b) = 0;
	bool virtual isBusy() = 0;
	void virtual setTimeLeftInQueue(int t) = 0;
	int virtual getTimeLeftInQueue() 
	{
		int count = 0;
		if (runPtr)
			count += runPtr->getTimeLeft();
		LinkedQueue<Process*> temp;
		if (readyQ->isEmpty())
		{
			//cout << endl;
			return count;
		}
		Process* x;
		readyQ->dequeue(x);
		temp.enqueue(x);
		count += x->getTimeLeft();
		while (!readyQ->isEmpty())
		{
			Process* x;
			readyQ->dequeue(x);
			temp.enqueue(x);
			count += x->getTimeLeft();
		}
		while (!temp.isEmpty())
		{
			Process* x;
			temp.dequeue(x);
			readyQ->enqueue(x);
		}
		return count;
	}
	virtual QueueADT<Process*>*  getReadyQ() = 0;
	bool virtual AddtoQ(Process* x)
	{
		bool flag = readyQ->enqueue(x);
		if (flag)
			TimeLeftInQueue += x->getCPUTime();
		return(flag);
	}
	void virtual printRDY() = 0;
	int virtual countRDY() = 0;
	Process* getRun() { return runPtr; }
};


#pragma once
#include "Processor.h"
#include "PriorityQueue.h"
#include <iostream>
using namespace std;
class SJF : public Processor
{
public:
	SJF()
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new PriorityQueue<Process*>;
		runPtr = nullptr;
	}
	void ScheduleAlgo()
	{
		cout << "Hello world";
	}
	bool Run(Process* & done,int TS)
	{
		if (!busy && !readyQ->isEmpty())
		{
			readyQ->dequeue(runPtr);
			busy = true;
			runPtr->setResponseTime(TS);
			runPtr->setWaitingTime(runPtr->getResponseTime() - runPtr->getArrivalTime());
			
		}
		if (runPtr)
		{
			if (busy)
			{
				if (runPtr->getTimeLeft() > 0)
				{
					runPtr->setTimeLeft(runPtr->getTimeLeft() - 1);

				}
				else
				{
					busy = false;
					done = runPtr;
					runPtr->setTerminationTime(TS);
					runPtr = nullptr;
					return true;
				}
			}
		}
		return false;
	}

	void setBusy(bool b)
	{
		busy = b;

	}
	bool isBusy()
	{
		return busy;
	}
	void  setTimeLeftInQueue(int t)
	{
		TimeLeftInQueue = t;
	}
	int  getTimeLeftInQueue()
	{
		return TimeLeftInQueue;
	}
	QueueADT<Process*>* getReadyQ()
	{
		return readyQ;
	}
	~SJF()
	{
		delete readyQ;
	}
};


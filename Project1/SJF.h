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
	int Run(Process* & done,int TS)
	{
		if (!busy && !readyQ->isEmpty())
		{
			readyQ->dequeue(runPtr);
			busy = true;
		}
		if (runPtr)
		{
			if (TS < runPtr->getArrivalTime())
				return 0;
			runPtr->setResponseTime(TS);
			runPtr->setWaitingTime(runPtr->getResponseTime() - runPtr->getArrivalTime());
			if (busy)
			{
				if (runPtr->getnIO() == nullptr)
				{
					runPtr->getIO();

				}
				if (runPtr->getnIO() != nullptr && !runPtr->getnIO()->isDone())
				{
					if (runPtr->getnIO()->getArrival() == runPtr->getCPUTime() - runPtr->getTimeLeft())
					{
						busy = false;
						done = runPtr;
						runPtr = nullptr;
						return 2;
					}
				}
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
					return 1;
				}
			}
		}
		return 0;
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


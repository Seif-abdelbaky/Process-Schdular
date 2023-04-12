#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"Processor.h"

class FCFS :public Processor
{
public:
	FCFS()
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new LinkedQueue<Process*>;
		runPtr = nullptr;
	}
	void ScheduleAlgo()
	{
		cout << "Hello world";
	}
	bool virtual Run(Process* & done,int TS) {
		if (!busy && !readyQ->isEmpty())
		{
			readyQ->dequeue(runPtr);
			busy = true;
		}
		if (runPtr)
		{
			if (TS < runPtr->getArrivalTime())
				return false;
			runPtr->setResponseTime(TS);
			runPtr->setWaitingTime(runPtr->getResponseTime() - runPtr->getArrivalTime());
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
	~FCFS()
	{
		delete readyQ;
	}
};


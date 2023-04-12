#pragma once
#include "Processor.h"
#include "PriorityQueue.h"
#include <iostream>
using namespace std;
class RR : public Processor
{
private :
	int TimeSlice;
public:

	RR(int x = 0)
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new PriorityQueue<Process*>;
		runPtr = nullptr;
		TimeSlice = x;
	}
	void set_time(int x)
	{
		TimeSlice = x;
	}
	int get_time() const
	{
		return TimeSlice;
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
				return false;
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
					if (runPtr->getTimeLeft() > 0 && TimeSlice != 0 && (TS - runPtr->getResponseTime()) % TimeSlice == 0 )
					{
						Process* temp = runPtr;
						readyQ->enqueue(temp);
						runPtr = nullptr;

					}
					return false;

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
	~RR()
	{
		delete readyQ;
	}
};


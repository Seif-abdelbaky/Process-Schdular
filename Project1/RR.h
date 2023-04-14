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
			runPtr->setResponseTime(TS);
			runPtr->setWaitingTime(runPtr->getResponseTime() - runPtr->getArrivalTime());
			
		}
		if (runPtr)
		{
			if (TS < runPtr->getArrivalTime())
				return 0;
			
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
				runPtr->setTimeLeft(runPtr->getTimeLeft() - 1);
				if (runPtr->getTimeLeft() > 0)
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
					if (runPtr->getTimeLeft() > 0 && TimeSlice != 0 && (TS - runPtr->getResponseTime()) % TimeSlice == 0 && TS != runPtr->getResponseTime() )
					{
						Process* temp = runPtr;
						readyQ->enqueue(temp);
						runPtr = nullptr;
						busy = false;
					}
					

				}
				else
				{
					busy = false;
					done = runPtr;
					runPtr->setTerminationTime(TS);
					runPtr = nullptr;
					return 1;
				}
				return 0;
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

	QueueADT<Process*>* getReadyQ()
	{
		return readyQ;
	}
	void printRDY()
	{
		cout << "[RR  ]: ";
		cout << countRDY() << " RDY:";
		LinkedQueue<Process*> temp;
		if (readyQ->isEmpty())
		{
			cout << endl;
			return;
		}
		Process* x;
		readyQ->dequeue(x);
		temp.enqueue(x);
		cout << x;
		while (!readyQ->isEmpty())
		{
			Process* x;
			readyQ->dequeue(x);
			temp.enqueue(x);
			cout << ", " << x;

		}
		while (!temp.isEmpty())
		{
			Process* x;
			temp.dequeue(x);
			readyQ->enqueue(x);
		}
		cout << endl;
	}
	int countRDY()
	{
		int count = 0;
		LinkedQueue<Process*> temp;
		if (readyQ->isEmpty())
		{
			//cout << endl;
			return 0;
		}
		Process* x;
		readyQ->dequeue(x);
		temp.enqueue(x);
		count++;
		while (!readyQ->isEmpty())
		{
			Process* x;
			readyQ->dequeue(x);
			temp.enqueue(x);
			count++;
		}
		while (!temp.isEmpty())
		{
			Process* x;
			temp.dequeue(x);
			readyQ->enqueue(x);
		}
		return count;
	}
	~RR()
	{
		delete readyQ;
	}
};


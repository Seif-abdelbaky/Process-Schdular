#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"Processor.h"
#include <cstdlib>
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
	int virtual Run(Process* & done,int TS) {
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
				return false;
			
			if (busy)
			{
				////////////////////////// PHASE 1
				srand(time(0));
				int probability = rand() % 100 + 1;
				if (probability <= 15 && probability >= 1)
				{
					//// blk
					busy = false;
					done = runPtr;
					runPtr = nullptr;
					return 2;
				}
				else if (probability <= 30 && probability >= 20)
				{
					/////RDY
					Process* temp = runPtr;
					readyQ->enqueue(temp);
					runPtr = nullptr;
					busy = false;
					return 0;
				}
				else if (probability <= 60 && probability >= 50)
				{
					//// trm
					busy = false;
					done = runPtr;
					runPtr->setTerminationTime(TS);
					runPtr = nullptr;
					return 1;
				}
				else
				{
					/// continue
					return 0;
				}
				/////////////////////PHASE 2
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

	QueueADT<Process*>* getReadyQ()
	{
		return readyQ;
	}
	void printRDY()
	{
		cout << "[FCFS]: ";
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
	~FCFS()
	{
		delete readyQ;
	}
};


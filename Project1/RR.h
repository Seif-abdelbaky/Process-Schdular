#pragma once
#include "Processor.h"
#include"LinkedQueue.h"
#include "PriorityQueue.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class RR : public Processor
{
private :
	int TimeSlice;
	int RTF;
public:

	RR(int x, int y)
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new LinkedQueue<Process*>;
		runPtr = nullptr;
		TimeSlice = x;
		RTF = y;
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
			runPtr->setWaitingTime(TS - runPtr->getArrivalTime() + runPtr->getTimeLeft() - runPtr->getCPUTime());
			
		}
		if (runPtr)
		{
			if (TS < runPtr->getArrivalTime())
				return 0;
			
			if (busy)
			{
				////////////////////////// PHASE 1
				/*srand(time(0) % 10);*/
				/*int probability = rand() % 100 + 1;
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
				}*/
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
						return 2;		////// goes to block
					}
				}
				if (runPtr->getTimeLeft() < RTF)
				{
					busy = false;
					done = runPtr;
					runPtr = nullptr;
					return 5; ///// goes to shortest SJF Q
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
					if (runPtr->getTimeLeft() > 0 && TimeSlice != 0 && (TS + 1 - runPtr->getResponseTime()) % TimeSlice == 0 )
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
	bool SigKill(Process* &Killed, int idKilled, bool& hasChildren)
	{
		return false;
	}
	bool fork(int T)
	{
		return false;
	}
	~RR()
	{
		delete readyQ;
	}
};


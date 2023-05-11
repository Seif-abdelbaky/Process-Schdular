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
	void overHeat(Process* & temp)
	{
		overHeated = true;
		waiting = 0;
		if (busy)
		{
			busy = false;
			temp = runPtr;
			runPtr = nullptr;
		}
	}
	bool isHeated()
	{
		return overHeated;
	}
	void virtual ScheduleAlgo()=0;
	int virtual Run(Process* & done, int TS) = 0;
	void virtual setBusy(bool b) = 0;
	bool virtual isBusy() = 0;
	void virtual setTimeLeftInQueue(int t) = 0;
	bool virtual SigKill(Process*& Killed, int idKilled,bool & hasChildren) = 0;
	bool virtual fork(int T,Process*&forkPtr) = 0;
	int virtual getter_total()
	{
		int x = 0;
		if (runPtr)
			x = runPtr->getTimeLeft();
		return TimeLeftInQueue + x;
	}
	int virtual getTimeLeftInQueue() 
	{
		return getter_total();
		///// brute force
		/*int count = 0;
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
		return count; */
	}
	virtual QueueADT<Process*>*  getReadyQ() = 0;
	bool virtual AddtoQ(Process* x)
	{
		bool flag = readyQ->enqueue(x);
		if (flag)
			TimeLeftInQueue += x->getTimeLeft();
		return(flag);
	}
	void virtual printRDY() = 0;
	int virtual countRDY() = 0;
	Process* getRun() { return runPtr; }
	Process* gimme_something(bool noNeed) // no need = no need to check for a nonchild since it is either in SJF/ RR or to a FCFS
	{
		Process* ptr = nullptr;
		if (!readyQ->isEmpty())
		{
			if (noNeed)
			{
				readyQ->dequeue(ptr);
				TimeLeftInQueue -= ptr->getTimeLeft();
			}
			else
			{
				LinkedQueue<Process*> temp;
				Process* x;
				while (!readyQ->isEmpty())
				{
					readyQ->dequeue(x);
					if (!x->isChild() && ptr == nullptr)
					{
						ptr = x;
						TimeLeftInQueue -= ptr->getTimeLeft();
					}
					else
						temp.enqueue(x);

				}
				while (!temp.isEmpty())
				{
					temp.dequeue(x);
					readyQ->enqueue(x);
				}
			}
		}
		return ptr;
	}
	bool EmptyReady()
	{
		return readyQ->isEmpty();
	}
	int TimeLeftRunPtr()
	{
		if (runPtr)
			return runPtr->getTimeLeft();
		else
			return 0;
	}
	int TimeLeftReady()
	{
		return getTimeLeftInQueue() - TimeLeftRunPtr();
	}
	int getTotalBusy() {
		return TotalBusy;
	}
};


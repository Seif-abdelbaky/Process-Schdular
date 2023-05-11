#include "SJF.h"

SJF::SJF(int T)
{
	TimeLeftInQueue = 0;
	busy = false;
	readyQ = new PriorityQueue<Process*>;
	runPtr = nullptr;
	CoolingT = T;
}


int SJF::ScheduleALGO(Process*& done, int TS)
{
	if (overHeated)
	{
		waiting++;
		if (waiting >= CoolingT)
		{
			//cout << "COOOOOOLED" << endl;
			overHeated = false;
			waiting = 0;
		}
		return 0;
	}
	if (!busy && !readyQ->isEmpty())
	{
		readyQ->dequeue(runPtr);
		busy = true;
		runPtr->setResponseTime(TS - runPtr->getArrivalTime());
		runPtr->setWaitingTime(TS - runPtr->getArrivalTime() + runPtr->getTimeLeft() - runPtr->getCPUTime());
		TimeLeftInQueue -= runPtr->getTimeLeft();
	}
	if (runPtr)
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
			TotalBusy++;
			runPtr->setTimeLeft(runPtr->getTimeLeft() - 1);
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
				return 0;
			}
			else
			{
				busy = false;
				done = runPtr;
				runPtr->setTerminationTime(TS + 1);
				runPtr = nullptr;
				return 1;
			}
		}
	}
	return 0;
}

void SJF::setBusy(bool b)
{
	busy = b;

}

bool SJF::isBusy()
{
	return busy;
}

void SJF::setTimeLeftInQueue(int t)
{
	TimeLeftInQueue = t;
}



void SJF::printRDY()
{
	cout << "[SJF ]: ";
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

int SJF::countRDY()
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

bool SJF::SigKill(Process*& Killed, int idKilled, bool& hasChildren)
{
	return false;
}

bool SJF::fork(int T, Process*& forkPtr)
{
	return false;
}

SJF::~SJF()
{
	delete readyQ;
}

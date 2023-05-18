#include "RR.h"

 RR::RR(int x, int y, int T)
{
	TimeLeftInQueue = 0;
	busy = false;
	readyQ = new LinkedQueue<Process*>;
	runPtr = nullptr;
	TimeSlice = x;
	RTF = y;
	CoolingT = T;
}

void RR::set_time(int x)
{
	TimeSlice = x;
}

int RR::get_time() const
{
	return TimeSlice;
}

int RR::ScheduleALGO(Process*& done, int TS)
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
		runPtr->setResponseProcessor(TS);
		runPtr->setWaitingTime(TS - runPtr->getArrivalTime() + runPtr->getTimeLeft() - runPtr->getCPUTime());
		TimeLeftInQueue -= runPtr->getTimeLeft();
		if (runPtr->getTimeLeft() < RTF)
		{
			busy = false;
			done = runPtr;
			runPtr = nullptr;
			return 5; ///// goes to shortest SJF Q
		}

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

			TotalBusy++;
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
				if (runPtr->getTimeLeft() > 0 && TimeSlice != 0 && (TS + 1 - runPtr->getresponseProcessor()) % TimeSlice == 0)
				{
					Process* temp = runPtr;
					readyQ->enqueue(temp);
					TimeLeftInQueue += temp->getTimeLeft();
					runPtr = nullptr;
					busy = false;
				}


			}
			else  // Ya rab mnwslsh hena
			{
				busy = false;
				done = runPtr;
				runPtr->setTerminationTime(TS + 1);
				runPtr = nullptr;
				return 1;
			}
			return 0;
		}
	}
	return 0;
}

void RR::setBusy(bool b)
{
	busy = b;
}

bool RR::isBusy()
{
	return busy;
}

void RR::setTimeLeftInQueue(int t)
{
	TimeLeftInQueue = t;
}

void RR::printRDY()
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

 int RR::countRDY()
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

  bool RR::SigKill(Process*& Killed, int idKilled, bool& hasChildren)
 {
	 return false;
 }

   bool RR::fork(int T, Process*& forkPtr, int TotalProcess)
  {
	  return false;
  }

    RR::~RR()
   {
	   delete readyQ;
   }

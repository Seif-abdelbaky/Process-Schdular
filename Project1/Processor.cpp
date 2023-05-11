#include "Processor.h"

 void Processor::overHeat(Process*& temp)
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

  bool Processor::isHeated()
 {
	 return overHeated;
 }

   int Processor::getter_total()
  {
	  int x = 0;
	  if (runPtr)
		  x = runPtr->getTimeLeft();
	  return TimeLeftInQueue + x;
  }

    int Processor::getTimeLeftInQueue()
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
	   return count;*/
   }

	 bool Processor::AddtoQ(Process* x)
	{
		bool flag = readyQ->enqueue(x);
		if (flag)
			TimeLeftInQueue += x->getTimeLeft();
		return(flag);
	}

	  Process* Processor::getRun() { return runPtr; }

	 Process* Processor::gimme_something(bool noNeed) // no need = no need to check for a nonchild since it is either in SJF/ RR or to a FCFS
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

	  bool Processor::EmptyReady()
	 {
		 return readyQ->isEmpty();
	 }

	   int Processor::TimeLeftRunPtr()
	  {
		  if (runPtr)
			  return runPtr->getTimeLeft();
		  else
			  return 0;
	  }

	    int Processor::TimeLeftReady()
	   {
		   return getTimeLeftInQueue() - TimeLeftRunPtr();
	   }

		 int Processor::getTotalBusy() {
			return TotalBusy;
		}

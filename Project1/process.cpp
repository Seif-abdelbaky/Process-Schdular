#include "process.h"

 Process::Process(int at, int pid, int ct, int IOn) {
	setArrivalTime(at);
	setPid(pid);
	setCPUTime(ct);
	setNumIOS(IOn);
	setTimeLeft(ct);
	TimeDone = 0;
	ResponseT = -1;
	nextIO = nullptr;
	child = nullptr;
	secondChild = nullptr;
	ischild = false;
	IO_D = 0;
	to_block = 0;
}

  int Process::get_to_block()
 {
	 return to_block;
 }

   void Process::set_blk(int x)
  {
	  to_block = x;
  }

    int Process::get_io_d()
   {
	   return IO_D;
   }

	 void Process::set_io_d(int x)
	{
		IO_D = x;
	}

	  void Process::set_child(bool x)
	 {
		 ischild = x;
	 }

	   bool Process::isChild()
	  {
		  return ischild;
	  }

	    IO* Process::getnIO()
	   {
		   return nextIO;
	   }

		 void Process::setnIO(IO* a)
		{
			nextIO = a;
		}

		  void Process::setPid(int pid)
		 {
			 Pid = pid;
		 }

		   void Process::setArrivalTime(int AT)
		  {
			  ArrivalT = AT;
		  }

		    void Process::setResponseTime(int RT)
		   {
			   if (ResponseT == -1)
				   ResponseT = RT;
			   return;
		   }

			 void Process::setCPUTime(int CT)
			{
				cpuT = CT;
			}

			  void Process::setTerminationTime(int TT)
			 {
				 TerminationT = TT;
			 }

			   void Process::setTurnAroundTime(int TRT)
			  {
				  TurnaroundDuration = TRT;
			  }

			    void Process::setWaitingTime(int WT)
			   {
				   WaitingT = WT;
			   }

void Process::setNumIOS(int IOS)
{
	IO_n = IOS;
}

void Process::setTimeLeft(int TL)
{
	timeLeft = TL;
}

void Process::setDoneTime(int DT) {
	TimeDone = DT;
}

int Process::getDoneTime() {
	return TimeDone;
}

int Process::getPid()
{
	return Pid;
}

int Process::getArrivalTime()
{
	return ArrivalT;
}

int Process::getResponseTime()
{
	if (ResponseT == -1)
		return 0;
	return ResponseT;
}

int Process::getCPUTime()
{
	return cpuT;
}

int Process::getTerminationTime()
{
	return TerminationT;
}

int Process::getTurnRoundTime()
{
	return TerminationT - ArrivalT;
}

int Process::get_WaitingTime()
{
	return WaitingT;
}

int Process::calcWaitingTime()
{
	return TerminationT - ArrivalT - cpuT + timeLeft;
}

int Process::getNumIOS()
{
	return IO_n;
}

int Process::getTimeLeft()
{
	return timeLeft;
}

void Process::addIO(const IO& io)
{
	IOs.enqueue(io);
}

void Process::getIO()
{
	IO ret;
	if (IOs.isEmpty())
		return;
	IOs.dequeue(ret);
	if (ret.isDone())
		return;
	IO back = ret;
	nextIO = new IO(ret);

	back.setDone(true);
	IOs.enqueue(back);
	return;

}

void Process::PrintAll() {
	cout << "Arival: " << ArrivalT << ", PID: " << Pid << ", CPU Time: " << cpuT << ", IOs: " << IO_n << endl;
}

void Process::ForkProcess(Process*& temp, int T)
{
	if (!child || !secondChild)
	{
		if (!child)
		{
			child = new Process();
			child->setTimeLeft(this->getTimeLeft());
			child->setCPUTime(this->getTimeLeft());
			child->setPid(this->getPid() + 100000);
			child->setArrivalTime(T);
			temp = child;
			child->set_child(true);
		}
		else
		{
			secondChild = new Process();
			secondChild->setTimeLeft(this->getTimeLeft());
			secondChild->setCPUTime(this->getTimeLeft());
			secondChild->setPid(this->getPid() + 1000000);
			secondChild->setArrivalTime(T);
			temp = secondChild;
			secondChild->set_child(true);
		}
	}
	else
		temp = nullptr;
}

  bool Process::isParent()
 {
	 return !(child == nullptr) || !(secondChild == nullptr);
 }

   Process*& Process::getChild()
  {
	  return child;
  }

    Process*& Process::getSecondChild()
   {
	   return secondChild;
   }

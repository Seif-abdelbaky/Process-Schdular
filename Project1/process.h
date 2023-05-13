#pragma once
#include "LinkedQueue.h"
#include "IO.h"
#include<iostream>
using namespace std;
class Process
{
	int Pid;
	int ArrivalT;
	int ResponseT;
	int cpuT;
	int TimeDone;
	int TerminationT;
	int TurnaroundDuration;
	int WaitingT;
	int IO_n;
	int timeLeft;
	Process* child;
	Process* secondChild;
	LinkedQueue <IO> IOs;
	IO* nextIO;
	bool ischild;
	int IO_D;
	int to_block;
public:
	Process(int at = 0, int pid = 0, int ct = 0, int IOn = 0);
	int get_to_block();
	void set_blk(int x);
	int get_io_d();
	void set_io_d(int x);
	void set_child(bool x);
	bool isChild();
	IO* getnIO();
	void setnIO(IO* a);
	bool operator > (Process B)
	{
		return timeLeft > B.timeLeft;
	}
	void setPid(int pid);
	void setArrivalTime(int AT);
	void setResponseTime(int RT);
	void setCPUTime(int CT);
	void setTerminationTime(int TT);
	void setTurnAroundTime(int TRT);
	void setWaitingTime(int WT);
	void setNumIOS(int IOS);
	void setTimeLeft(int TL);
	void setDoneTime(int DT);
	int getDoneTime();
	int getPid();
	int getArrivalTime();
	int getResponseTime();
	int getCPUTime();
	int getTerminationTime();
	int getTurnRoundTime();
	int get_WaitingTime();
	int calcWaitingTime();
	int getNumIOS();
	int getTimeLeft();
	void addIO(const IO& io);
	void getIO();
	void PrintAll();
	friend ostream& operator << (ostream& out, Process* ptr)
	{
		
		out << ptr->getPid();
		return out;
		
	}
	void ForkProcess(Process*& temp, int T, int TotalProcess);
	bool isParent();
	Process*& getChild();
	Process*& getSecondChild();
};



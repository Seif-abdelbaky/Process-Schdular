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
	LinkedQueue <IO> IOs;
	IO* nextIO;
	bool ischild;
public:
	Process(int at=0, int pid=0, int ct=0, int IOn=0) {
		setArrivalTime(at);
		setPid(pid);
		setCPUTime(ct);
		setNumIOS(IOn);
		setTimeLeft(ct);
		TimeDone = 0;
		
		nextIO = nullptr;
		child = nullptr;
		ischild = false;
	}
	void set_child(bool x)
	{
		ischild = x;
	}
	bool isChild()
	{
		return ischild;
	}
	IO* getnIO()
	{
		return nextIO;
	}
	void setnIO(IO* a)
	{
		nextIO = a;
	}
	bool operator > (Process B)
	{
		return timeLeft > B.timeLeft;
	}
	void setPid(int pid)
	{
		Pid = pid;
	}
	void setArrivalTime(int AT)
	{
		ArrivalT = AT;
	}
	void setResponseTime(int RT)
	{
		ResponseT = RT;
	}
	void setCPUTime(int CT)
	{
		cpuT = CT;
	}
	void setTerminationTime(int TT)
	{
		TerminationT = TT;
	}
	void setTurnAroundTime(int TRT)
	{
		TurnaroundDuration = TRT;
	}
	void setWaitingTime(int WT)
	{
		WaitingT = WT;
	}
	void setNumIOS(int IOS)
	{
		IO_n = IOS;
	}
	void setTimeLeft(int TL)
	{
		timeLeft = TL;
	}
	void setDoneTime(int DT) {
		TimeDone = DT;
	}
	int getDoneTime() {
		return TimeDone;
	}
	int getPid()
	{
		return Pid;
	}
	int getArrivalTime()
	{
		return ArrivalT;
	}
	int getResponseTime()
	{
		return ResponseT;
	}
	int getCPUTime()
	{
		return cpuT;
	}
	int getTerminationTime()
	{
		return TerminationT;
	}
	int getTurnRoundTime()
	{
		return TurnaroundDuration;
	}
	int getWaitingTime()
	{
		return WaitingT;
	}
	int getNumIOS()
	{
		return IO_n;
	}
	int getTimeLeft()
	{
		return timeLeft;
	}
	void addIO(const IO& io)
	{
		IOs.enqueue(io);
	}
	void getIO()
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
	void PrintAll() {
		cout << "Arival: " << ArrivalT << ", PID: " << Pid << ", CPU Time: " << cpuT << ", IOs: " << IO_n<<endl;
	}
	friend ostream& operator << (ostream& out, Process* ptr)
	{
		
		out << ptr->getPid();
		return out;
		
	}
	void ForkProcess(Process*& temp, int T)
	{
		if (!child)
		{
			child = new Process();
			child->setTimeLeft(this->getTimeLeft() );
			
			child->setPid(this->getPid() + 1000000);
			child->setArrivalTime(T);
			temp = child;
			child->set_child(true);
		}
		else
			temp = nullptr;
	}
	bool isParent()
	{
		return !(child==nullptr);
	}
	Process*& getChild()
	{
		return child;
	}
};



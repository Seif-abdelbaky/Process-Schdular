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
	bool Run(Process* & pro)
	{
		cout << "Hello RR" << endl;
		return false;
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
	int  getTimeLeftInQueue()
	{
		return TimeLeftInQueue;
	}
	QueueADT<Process*>* getReadyQ()
	{
		return readyQ;
	}
	~RR()
	{
		delete readyQ;
	}
};


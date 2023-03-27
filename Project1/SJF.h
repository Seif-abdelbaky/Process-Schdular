#pragma once
#include "Processor.h"
#include "PriorityQueue.h"
#include <iostream>
using namespace std;
class SJF : public Processor
{
	SJF()
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new PriorityQueue<Process>;
		runPtr = nullptr;
	}
	void ScheduleAlgo()
	{
		cout << "Hello world";
	}
	void Run()
	{
		cout << "Hello world";
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
	QueueADT<Process>* getReadyQ()
	{
		return readyQ;
	}
	~SJF()
	{
		delete readyQ;
	}
};


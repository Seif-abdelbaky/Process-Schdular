#pragma once
#include<iostream>
#include"LinkedQueue.h"
#include"Processor.h"

class FCFS :public Processor
{
public:
	FCFS()
	{
		TimeLeftInQueue = 0;
		busy = false;
		readyQ = new LinkedQueue<Process*>;
		runPtr = nullptr;
	}
	void ScheduleAlgo()
	{
		cout << "Hello world";
	}
	bool virtual Run(Process* & done) {
		/*if (!busy) {
			if (!readyQ->isEmpty()) {
				readyQ->peek(*runPtr);
			}
		}
		if (busy) {
			TimeLeftInQueue--;
			int doneTime = runPtr->getDoneTime();
			runPtr->setDoneTime(++doneTime);
			int cpuTime = runPtr->getCPUTime();
			if (doneTime == cpuTime) {
				busy = false;
				runPtr = nullptr;
				readyQ->dequeue(done);
				return true;
			}
		}*/
		cout << "Hello FCFS" << endl;
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
	~FCFS()
	{
		delete readyQ;
	}
};


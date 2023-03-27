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
		readyQ = new LinkedQueue<Process>;
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
	~FCFS()
	{
		delete readyQ;
	}
};


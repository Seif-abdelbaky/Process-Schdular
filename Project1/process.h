#pragma once
#include "LinkedQueue.h"
#include "IO.h"
class Process
{
	int Pid;
	int ArrivalT;
	int ResponseT;
	int cpuT;
	int TerminationT;
	int TurnaroundDuration;
	int WaitingT;
	int IO_n;
	int timeLeft;
	LinkedQueue <IO> IOs;
public:
	Process(int at, int pid, int ct, int IOn) {
		ArrivalT = at;
		Pid = pid;
		cpuT = ct;
		IO_n = IOn;
	}
};


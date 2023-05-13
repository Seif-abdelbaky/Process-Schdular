#pragma once
#include"QueueADT.h"
#include"LinkedQueue.h"
#include"IO.h"
#include"process.h"
#include"Processor.h"
#include"FCFS.h"
#include"SJF.h"
#include"RR.h"
#include<fstream>
#include<iostream>
#include "UI.h"
#include <cstdlib>
#include <time.h>
#include"SignKill.h"
using namespace std;
class Scheduler
{
	private:
		int NF;
		int NS;
		int NR;
		int RRtime;
		int RTF;
		int MaxW;
		int STL;
		int fork;
		int TotalProcess;
		int mode;
		int processRTF = 0;
		int processMaxW = 0;
		int processStolen = 0;
		int processForked = 0;
		int processKilled = 0;
		int TotalTime = 0;
		int CoolingTime = 0;
		LinkedQueue<Process*> ProcessNew;
		LinkedQueue<Process*> ProcessTer;
		LinkedQueue<Process*> ProcessBlk;
		LinkedQueue<SignKill> ProcessKill;
		Processor* processors[1000];
		int processorsCount = 0;
		int TotalProcessors;
		int currentProcessor = 0;
		UI tool;
	public:
		void killchildren(Process* subroot, int T);
		void set_mode(int x);
		int get_min(int start, int end);
		int get_max(int start, int end);
		int get_min_ready(int start, int end);
		int get_max_ready(int start, int end);
		void runBLK(int timestep);
		void LoadFile();
		void sigkill(int i);
		void SaveFile();
		void overheat(int j);
		void steal();
		void simulate();
		bool updateInterface(int i);
		~Scheduler();
};


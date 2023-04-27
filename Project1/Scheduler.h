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
#include<map>
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
		LinkedQueue<Process*> ProcessNew;
		LinkedQueue<Process*> ProcessTer;
		LinkedQueue<Process*> ProcessBlk;
		LinkedQueue<SignKill> ProcessKill;
		Processor* processors[1000];
		int processorsCount = 0;
		int TotalProcessors;
		int currentProcessor = 0;
		UI tool;
		map<int, int> processLocation;
	public:
		void set_mode(int x)
		{
			if (x != 1 && x != 2)
				x = 3;
			mode = x;
			system("CLS");
		}
		int get_min(int start, int end)
		{
			int index = start;
			int min = processors[start]->getTimeLeftInQueue();
			for (int j = start + 1; j < end; j++)
			{
				int temp = processors[j]->getTimeLeftInQueue();
				if (temp < min)
				{
					min = temp;
					index = j;
				}
			}
			return index;
		}
		int get_max(int start, int end)
		{
			int index = start;
			int max = processors[start]->getTimeLeftInQueue();
			for (int j = start + 1; j < end; j++)
			{
				int temp = processors[j]->getTimeLeftInQueue();
				if (temp > max)
				{
					max = temp;
					index = j;
				}
			}
			return index;
		}
		int get_min_ready(int start, int end)
		{
			int index = start;
			int min = processors[start]->TimeLeftReady();
			for (int j = start + 1; j < end; j++)
			{
				int temp = processors[j]->TimeLeftReady();
				if (temp < min)
				{
					min = temp;
					index = j;
				}
			}
			return index;
		}
		int get_max_ready(int start, int end)
		{
			int index = start;
			int max = processors[start]->TimeLeftReady();
			for (int j = start + 1; j < end; j++)
			{
				int temp = processors[j]->TimeLeftReady();
				if (temp > max)
				{
					max = temp;
					index = j;
				}
			}
			return index;
		}
		void runBLK()
		{
			if (!ProcessBlk.isEmpty())
			{
				Process* ptr;
				ProcessBlk.peek(ptr);
				/////////// phase 1:
				/*srand(time(0) % 10);*/
				//int prob = rand() % 100 + 1;
				//if (prob < 10)
				//{
				//	ProcessBlk.dequeue(ptr);
				//	///////////// throws the ptr to the queue with least time
				//	int index = 0;
				//	int min = processors[0]->getTimeLeftInQueue();
				//	for (int j = 1; j < processorsCount; j++)
				//	{
				//		int temp = processors[j]->getTimeLeftInQueue();
				//		if (temp < min)
				//		{
				//			min = temp;
				//			index = j;
				//		}
				//	}
				//	processors[index]->AddtoQ(ptr);
				//	processLocation[ptr->getPid()] = index;

				//	return;
				//}
				//else
				//{
				//	return;
				//}

				///////////phase 2
				int left = ptr->getnIO()->getTimeLeft();
				ptr->getnIO()->setTimeLeft(left - 1);
				if (left == 0)
				{
					//cout << "IO DONE";
					IO* ptrIO = ptr->getnIO();
					ptr->setnIO(nullptr);
					delete ptrIO;
					ProcessBlk.dequeue(ptr);
					///////////// throws the ptr to the queue with least time
					int index = get_min(0, processorsCount);
					processors[index]->AddtoQ(ptr);
					processLocation[ptr->getPid()] = index;

				}
			}
		}
		void LoadFile() {
			string filename = "Input.txt";
			ifstream inputFile(filename);
			inputFile >> NF >> NS >> NR;
			TotalProcessors = NF + NS + NR;
			inputFile >> RRtime;
			inputFile >> RTF >> MaxW >> STL >> fork;
			inputFile >> TotalProcess;
			//cout << NF << " " << NS << " " << NR<<endl;
			for (int i = 0; i < NF; i++) {
				processors[processorsCount++] = new FCFS(MaxW);
			}
			for (int i = 0; i < NS; i++) {
				processors[processorsCount++] = new SJF();
			}
			for (int i = 0; i < NR; i++) {
				processors[processorsCount++] = new RR(RRtime, RTF);
			}
			//cout << RRtime << endl;
			//cout << RTF << " " << MaxW << " " << STL << " " << fork << endl;
			//cout << TotalProcess << endl;
			for (int i = 0; i < TotalProcess; i++) {
				int AT, PID, CT, N;
				inputFile >> AT >> PID >> CT >> N;
				
				Process* process=new Process(AT, PID, CT, N);
				//process->PrintAll();
				for (int i = 0; i < N; i++) {
					char c;
					inputFile >> c;
					int r, d;
					inputFile >> r;
					inputFile >> c;
					inputFile >> d;
					inputFile >> c;
					if (i < N - 1) {
						inputFile >> c; // c=','
					}
					IO io(r, d);
					process->addIO(io);
					//cout << r << " " << d << endl;
				}
				ProcessNew.enqueue(process);
			}
			int PID, time;
			
			while (inputFile >> PID) {
				inputFile >> time;
				SignKill kill;
				kill.ID = PID;
				kill.Time = time;
				ProcessKill.enqueue(kill);
				PID = 0;
			}
		}

		void SaveFile() {
			string filename = "Input.txt";
			ofstream outputFile(filename,ios::app); // Open file for output

			string data = "Hello, world!";
			outputFile << data << endl; // Write data to file

			outputFile.close();
		}
		void steal()
		{
			bool NoNeed = false;
			int min = get_min_ready(0, processorsCount);
			int max = get_max_ready(0, processorsCount);
			if (min < NF && max < NF)
				NoNeed = true;
			if (max >= NF)
				NoNeed = true;
			if (processors[max]->TimeLeftReady() == 0)
				return;
			float percentage = float(processors[max]->TimeLeftReady() - processors[min]->TimeLeftReady()) / float(processors[max]->TimeLeftReady());
			while (percentage > 0.4)
			{
				Process* ptr = processors[max]->gimme_something(NoNeed);
				if (ptr == nullptr)
					break;
				processors[min]->AddtoQ(ptr);
				cout << "SOMETHING WAS STOLEN\n";
				if (processors[max]->EmptyReady())
					break;
				percentage = float(processors[max]->TimeLeftReady() - processors[min]->TimeLeftReady()) / float(processors[max]->TimeLeftReady());
			}
		}
		void simulate() {
			if (mode == 3)
				tool.generate_silent();
			int Assassin = 1 + rand() % TotalProcess;
			for (int i = 1; ; i++) {
				if (i % STL == 0)
					steal();
				//cout << i <<": " ;
				Process* cur;
				bool isNotEmpty= ProcessNew.peek(cur);
				while (isNotEmpty && cur->getArrivalTime() == i) {
					int index = get_min(0, TotalProcessors);
					bool flag = processors[index]->AddtoQ(cur);
					/*while (!flag) {
						flag = processors[currentProcessor++]->AddtoQ(cur);
					}*/
					processLocation[cur->getPid()] = index;
					/*if (currentProcessor == TotalProcessors) {
						currentProcessor = 0;
					}*/
					
					ProcessNew.dequeue(cur);
					isNotEmpty = ProcessNew.peek(cur);
				}

				for (int j = 0; j < TotalProcessors; j++) {
					Process* pro;
					if (processors[j])
					{
						//cout << processors[j]->getTimeLeftInQueue() << " ";

						if (!ProcessKill.isEmpty()) {
							SignKill kill;
							ProcessKill.peek(kill);
							if (kill.Time < i) {
								ProcessKill.dequeue(kill);
								cout << "passed: " << kill.ID << endl;
							}
							if (kill.Time == i) {
								bool hasChildren = false;
								bool Killed = processors[j]->SigKill(pro, kill.ID, hasChildren);
								if (Killed)
								{
									cout << "KILLED: " << kill.ID << endl;
									ProcessTer.enqueue(pro);
									ProcessKill.dequeue(kill);
								}
								if (pro)
								{
									bool HasChildren = pro->isParent();
									bool cont = true;
									while (pro && HasChildren && cont)
									{
										cont = false;
										for (int z = 0; z < NF; z++)
										{
											Process* temp = pro;
											processors[z]->SigKill(temp, temp->getChild()->getPid(), HasChildren);
											if (temp)
											{
												ProcessTer.enqueue(temp);
												cont = true;
												pro = temp;
												break;
											}
										}
									}
								}
							}
						}
						int fork_probability = 1+rand()%100;
						if (fork_probability <= fork && processors[j]->fork(i))
							TotalProcess++;
						int done = processors[j]->Run(pro, i);
						if (done == 5)	/// Migration to SJF;
						{
							do {
								int index = get_min(NF, NF + NS);
								processors[index]->AddtoQ(pro);
								done = processors[j]->Run(pro, i);
								cout << "MIGRATION TO SJF\n";
							} while (done == 5);
						}
						if (done == 4)	/// Migration to RR;
						{
							do {
								int index = get_min(NF + NS, processorsCount);
								processors[index]->AddtoQ(pro);
								done = processors[j]->Run(pro, i);
								cout << "MIGRATION TO RR\n";
							} while (done == 5);
						}
						if (done == 1) {
							ProcessTer.enqueue(pro);
							bool HasChildren = pro->isParent();
							bool cont = true;
							while (pro && HasChildren && cont)
							{
								cont = false;
								for (int z = 0; z < NF; z++)
								{
									Process* temp = pro;
									processors[z]->SigKill(temp, temp->getChild()->getPid(), HasChildren);
									if (temp)
									{
										ProcessTer.enqueue(temp);
										cont = true;
										pro = temp;
										break;
									}
								}
							}
						}
						else if (done == 2)
						{

							ProcessBlk.enqueue(pro);
						}
						

					}
				}
				runBLK();
				if (updateInterface(i))
					break;
			}

		}
		bool updateInterface(int i)
		{
			if (mode != 3)
			{
				tool.generate(i);
				tool.printProcessors(processors, processorsCount);
				tool.generateBLK(ProcessBlk);
				tool.printRunning(processors, processorsCount);
				tool.generateTRM(ProcessTer);

				if (count(ProcessTer) == TotalProcess)
				{
					cout << "Simulation ends, Output File Created" << endl;
					return true;
				}
				tool.next(mode);
			}
			if (count(ProcessTer) == TotalProcess)
			{
				cout << "Simulation ends, Output File Created" << endl;
				return true;
			}
			return false;
		}
};


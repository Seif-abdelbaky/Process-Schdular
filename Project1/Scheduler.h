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
		LinkedQueue<Process*> ProcessNew;
		LinkedQueue<Process*> ProcessTer;
		LinkedQueue<Process*> ProcessBlk;
		Processor* processors[1000];
		int processorsCount = 0;
		int TotalProcessors;
		int currentProcessor = 0;
		UI tool;
	public:

		void runBLK()
		{
			if (!ProcessBlk.isEmpty())
			{
				Process* ptr;
				ProcessBlk.peek(ptr);
				/////////// phase 1:
				/*srand(time(0) % 10);*/
				int prob = rand() % 100 + 1;
				if (prob < 10)
				{
					ProcessBlk.dequeue(ptr);
					///////////// throws the ptr to the queue with least time
					int index = 0;
					int min = processors[0]->getTimeLeftInQueue();
					for (int j = 1; j < processorsCount; j++)
					{
						int temp = processors[j]->getTimeLeftInQueue();
						if (temp < min)
						{
							min = temp;
							index = j;
						}
					}
					processors[index]->AddtoQ(ptr);
					return;
				}
				else
				{
					return;
				}

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
					int index = 0;
					int min = processors[0]->getTimeLeftInQueue();
					for (int j = 1; j < processorsCount; j++)
					{
						int temp = processors[j]->getTimeLeftInQueue();
						if (temp < min)
						{
							min = temp;
							index = j;
						}
					}
					processors[index]->AddtoQ(ptr);
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
				processors[processorsCount++] = new FCFS();
			}
			for (int i = 0; i < NS; i++) {
				processors[processorsCount++] = new SJF();
			}
			for (int i = 0; i < NR; i++) {
				processors[processorsCount++] = new RR(RRtime);
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
		}

		void SaveFile() {
			string filename = "Input.txt";
			ofstream outputFile(filename,ios::app); // Open file for output

			string data = "Hello, world!";
			outputFile << data << endl; // Write data to file

			outputFile.close();
		}

		void simulate() {
			int Assassin = 1+rand()%TotalProcess;
			for (int i = 1; ; i++) {
				//cout << i <<": " ;
				Process* cur;
				bool isNotEmpty= ProcessNew.peek(cur);
				while (isNotEmpty && cur->getArrivalTime() == i) {

					bool flag = processors[currentProcessor++]->AddtoQ(cur);
					while (!flag) {
						flag = processors[currentProcessor++]->AddtoQ(cur);
					}
					if (currentProcessor == TotalProcessors) {
						currentProcessor = 0;
					}
					
					ProcessNew.dequeue(cur);
					isNotEmpty = ProcessNew.peek(cur);
				}

				for (int j = 0; j < TotalProcessors; j++) {
					Process* pro;
					if (processors[j])
					{
						//cout << processors[j]->getTimeLeftInQueue() << " ";
						bool Killed = processors[j]->SigKill(pro, Assassin);
						if (Killed)
						{
							ProcessTer.enqueue(pro);
						}
						int done = processors[j]->Run(pro, i);
						if (done == 1) {
							ProcessTer.enqueue(pro);
						}
						else if (done == 2)
						{

							ProcessBlk.enqueue(pro);
						}

					}
				}
				runBLK();
				tool.generate(i);
				tool.printProcessors(processors, processorsCount);
				tool.generateBLK(ProcessBlk);
				tool.printRunning(processors, processorsCount);
				tool.generateTRM(ProcessTer);

				if (count(ProcessTer) == TotalProcess)
				{
					cout << "THE END! "<< endl;
					break;
				}
				//tool.next();
			}

		}
};


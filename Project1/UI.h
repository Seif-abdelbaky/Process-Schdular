#pragma once
#include <iostream>
using namespace std;
#include"QueueADT.h"
#include"LinkedQueue.h"
#include "process.h"
#include "Processor.h"
#include <Windows.h>
#include <cstdlib>
class UI
{
private: 
	int timestep;
public:
	UI(int x = 0)
	{
		timestep = x;
	}
	void generate_silent()
	{
		cout << "Silent Mode..........., Simulation Starts ..." << endl;
	}
	void generate(int x)
	{
		cout << "Current Timestep:" << x << endl;
		
	}
	template <class T>
	void generateBLK(LinkedQueue <T> & queue)
	{
		cout << "-------------- BLK processes --------------" << endl;
		string str;
		cout << queue.count() << " BLK: ";
		queue.print();
	}
	template <class T>
	void generateRDY(int x, string str, LinkedQueue <T>*& queue)
	{
		cout << "processor" << x << "[" << str << "]:" << endl;

		cout << " RDY: " << queue.count();
		queue.print();
	}
	template <class T>
	void generateTRM(LinkedQueue <T>& queue)
	{
		cout << "-------------- TRM processes --------------" << endl;
		string str;
		cout << queue.count() << " TRM: ";
		queue.print();

	}
	void next(int mode)
	{
		if (mode == 1)
		{
			cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!\n";
			cin.clear(); //this will clear any values remain in cin from prior run
			cin.ignore(1000000000, '\n');
			//cin.get();
			//system("PAUSE"); 
		}
		else
		{
			Sleep(1000);
		}
		system("CLS"); //this will clear the screen of any text from prior run


		
	 // this ends your main function.
		return;
	}
	void printProcessors(Processor** arr, int count)
	{
		cout << "-------------- RDY processes --------------" << endl;
		
		for (int i = 0;i < count; i++)
		{
			if (!arr[i]->isHeated())
			{
				cout << "processor " << i + 1 << " ";
				arr[i]->printRDY();
				cout << "USING GETTER:" << arr[i]->getter_total() << "    ";
				cout << "USing Brute Force: " << arr[i]->getTimeLeftInQueue() << endl;
			}
		}
	}
	void printRunning(Processor** arr, int count)
	{
		cout << "-------------- RUN processes --------------" << endl;
		int z = 0;
		for (int i = 0;i < count; i++)
		{
			if (arr[i]->isBusy())
				z++;
		}
		cout << z << " RUN:";
		int printed = 0;
		for (int i = 0; i < count; i++)
		{
			if (arr[i]->isBusy() && arr[i]->getRun())
			{
				
				cout << arr[i]->getRun();
				cout << "(P" << i + 1 << ")";
				if (printed + 1 != z)
				{
					cout << ", ";
				}
				printed++;
			}
		}
		cout << endl;
	}

};


#pragma once
#include <iostream>
using namespace std;
#include"QueueADT.h"
#include"LinkedQueue.h"
#include "process.h"
#include "Processor.h"
class UI
{
private: 
	int timestep;
public:
	UI(int x = 0)
	{
		timestep = x;
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
		cout << count(queue) << " BLK: ";
		print(queue);
	}
	template <class T>
	void generateRDY(int x, string str, LinkedQueue <T>*& queue)
	{
		cout << "processor" << x << "[" << str << "]:" << endl;

		cout << " RDY: " << count(queue);
		print(queue);
	}
	template <class T>
	void generateTRM(LinkedQueue <T>& queue)
	{
		cout << "-------------- TRM processes --------------" << endl;
		string str;
		cout << count(queue) << " TRM: ";
		print(queue);

	}
	void next()
	{
		cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!";
		char x;
		cin >> x;
		return;
	}
	void printProcessors(Processor** arr, int count)
	{
		cout << "-------------- RDY processes --------------" << endl;
		
		for (int i = 0;i < count; i++)
		{
			cout << "processor " << i + 1 << " ";
			arr[i]->printRDY();
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


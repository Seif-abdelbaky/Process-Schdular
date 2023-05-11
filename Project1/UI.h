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
	UI(int x = 0);
	void generate_silent();
	void generate(int x);
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
	void next(int mode);
	void printProcessors(Processor** arr, int count);
	void printRunning(Processor** arr, int count);

};


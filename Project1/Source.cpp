#include<iostream>
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include"FCFS.h"

#include"Scheduler.h"
using namespace std;

int main() {
	srand(time(0));
	cout << "Please Choose A Mode\n";
	cout << "Enter 1 for Interactive Mode\n";
	cout << "Enter 2 for Step by Step Mode\n";
	cout << "Enter 3 for Silent Mode\n";
	int mode;
	cin >> mode;
	cin.ignore();
	Scheduler scheduler;
	scheduler.set_mode(mode);
	scheduler.LoadFile();
	scheduler.simulate();
	scheduler.SaveFile();
}
#include<iostream>
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include"FCFS.h"

#include"Scheduler.h"
using namespace std;

int main() {
	srand(time(0));	//// seed for phase 1 random generation
	Scheduler scheduler;
	scheduler.LoadFile();

	scheduler.simulate();
}
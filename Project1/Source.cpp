#include<iostream>
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include"FCFS.h"

#include"Scheduler.h"
using namespace std;

int main() {
	Scheduler scheduler;
	scheduler.LoadFile();

	scheduler.simulate();
}
#include<iostream>
#include "LinkedQueue.h"
#include "PriorityQueue.h"
#include"FCFS.h"
using namespace std;

int main() {
	FCFS x;
	x.getReadyQ();
	QueueADT <int>* ptr;
	ptr = new PriorityQueue<int>;
	PriorityQueue<int> test;
	int arr[10] = { 1, 7, 9, -1, 0, 2, 3, 4, 5, 5 };
	for (int i = 0; i < 10; i++)
	{
		
		ptr->enqueue(arr[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		int x;
		ptr->dequeue(x);
		cout << x << ' ';
	}
}
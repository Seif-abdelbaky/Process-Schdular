#pragma once
class IO
{
	int arrival;
	int duration;
	int timeleft;
	bool done;
public:
	IO();
	IO(int r, int d);
	int getTimeLeft();
	void setTimeLeft(int x);
	void setArrival(int r);
	void setDuration(int d);
	void setDone(bool d);
	int getArrival();
	int getDuration();
	bool isDone();
};


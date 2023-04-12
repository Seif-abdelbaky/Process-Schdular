#pragma once
class IO
{
	int arrival;
	int duration;
	int timeleft;
	bool done;
public:
	IO() {
		arrival = 0;
		duration = 0;
		done = false;
	}
	IO(int r, int d) :arrival(r), duration(d) {
		done = 0;
		timeleft = duration;
	}
	int getTimeLeft()
	{
		return timeleft;
	}
	void setTimeLeft(int x)
	{
		timeleft = x;
	}
	void setArrival(int r) {
		if (r > 0) {
			arrival = r;
		}
	}
	void setDuration(int d) {
		if (d > 0) {
			duration = d;
		}
	}
	void setDone(bool d) {
		done = d;
	}
	int getArrival() {
		return arrival;
	}
	int getDuration() {
		return duration;
	}
	bool isDone() {
		return done;
	}
};


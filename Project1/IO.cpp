#include "IO.h"

 IO::IO() {
	arrival = 0;
	duration = 0;
	done = false;
}

  IO::IO(int r, int d) :arrival(r), duration(d) {
	 done = 0;
	 timeleft = duration;
 }

   int IO::getTimeLeft()
  {
	  return timeleft;
  }

    void IO::setTimeLeft(int x)
   {
	   timeleft = x;
   }

	 void IO::setArrival(int r) {
		if (r > 0) {
			arrival = r;
		}
	}

	  void IO::setDuration(int d) {
		 if (d > 0) {
			 duration = d;
		 }
	 }

	   void IO::setDone(bool d) {
		  done = d;
	  }

	    int IO::getArrival() {
		   return arrival;
	   }

		 int IO::getDuration() {
			return duration;
		}

		  bool IO::isDone() {
			 return done;
		 }

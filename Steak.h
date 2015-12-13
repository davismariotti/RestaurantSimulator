#ifndef STEAK_h
#define STEAK_h

#include "Dish.h"
#include "Simulator.h"
#include "Random.h"

extern Random _random;

class Steak : public Dish {
private:
	int time_until_ready = 20;
	int time_to_eat_min = 15;
	int time_to_eat_max = 25;
public:

	Steak(int clock) : Dish(clock) {}

	bool isReady(int clock) {
		return (clock - start) > time_until_ready;
	}

	int timeToEat(void) {
		return time_to_eat_min + _random.next_int(time_to_eat_max - time_to_eat_min);
	}
};

#endif
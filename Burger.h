#ifndef BURGER_h
#define BURGER_h

#include "Dish.h"
#include "Simulator.h"
#include "Random.h"

extern Random _random;

class Burger : public Dish {
private:
	int time_until_ready = 10;
	int time_to_eat_min = 8;
	int time_to_eat_max = 15;
public:

	Burger(int clock) : Dish(clock) {}

	bool isReady(int clock) {
		return (clock - start) > time_until_ready;
	}

	int timeToEat(void) {
		return time_to_eat_min + _random.next_int(time_to_eat_max - time_to_eat_min);
	}
};

#endif
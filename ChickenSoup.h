#ifndef CHICKENSOUP_h
#define CHICKENSOUP_h

#include "Dish.h"
#include "Simulator.h"
#include "Random.h"

extern Random _random;

class ChickenSoup : public Dish {
private:
	int time_until_ready = 10;
	int time_to_eat_min = 20;
	int time_to_eat_max = 30;
public:
	bool isReady(int clock) {
		return (clock - start) > time_until_ready;
	}

	int timeToEat() {
        return time_to_eat_min + _random.next_int(time_to_eat_max - time_to_eat_min);
	}
};

#endif


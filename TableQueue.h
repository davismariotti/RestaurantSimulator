#ifndef TableQueue_h
#define TableQueue_h

#include <queue>
#include "Customer.h"
#include "EntranceQueue.h"
#include "EatingQueue.h"
#include "ChickenSoup.h"
#include "Spaghetti.h"
#include "Burger.h"
#include "Steak.h"
#include "ChickenStrips.h"
#include "CaesarSalad.h"
#include "Taco.h"
#include "MozzorellaStix.h"
#include "OnionRings.h"
#include "IceCream.h"
#include "Pie.h"
#include "Cheesecake.h"
#include "Random.h"

extern Random _random;

class TableQueue {
private:
	EntranceQueue *entrance_queue;
	EatingQueue *eating_queue;

	std::priority_queue<Customer *, std::deque<Customer *>, CompareCustomer> the_queue;
	int total_wait;
	int num_served;


public:
	TableQueue() : total_wait(0), num_served(0) {}

	void init(EntranceQueue *entrance_queue, EatingQueue *eating_queue) {
		this->entrance_queue = entrance_queue;
		this->eating_queue = eating_queue;
	}

	void update(int clock) {
		if (!the_queue.empty()) {
			Customer *customer = the_queue.top();
			if (customer->ready(clock)) {
				// If the customer is ready to be served their food
				the_queue.pop();
				eating_queue->add(customer);
				num_served++;
				total_wait += clock - customer->getArrivalTime();
				customer->incrementTotalTime(clock - customer->getArrivalTime());
				customer->setArrivalTime(clock);
			}
		}
		if ((the_queue.size() + eating_queue->size()) < eating_queue->max_size) { // If there is room in the restaurant
			if (!entrance_queue->the_queue.empty()) { // If there are people waiting to be seated
				Customer *customer = entrance_queue->the_queue.front();
				entrance_queue->the_queue.pop();
				entrance_queue->num_served++;
				entrance_queue->total_wait += clock - customer->getArrivalTime();
				assignDishToCustomer(customer, clock);
				customer->setTimeInQueue(eating_queue->getFirstDishTime(customer));
				customer->setArrivalTime(clock);
				the_queue.push(customer);

			}
		}
	}

	Dish * rand_Dish(int clock, int choice) {
		if (choice == 0)
		{
			int rand = _random.next_int(3); // Must be the number of different foods
			switch (rand) {
			case 0:
				return new MozzorellaStix(clock);
				break;
			case 1:
				return new CaesarSalad(clock);
				break;
			case 2:
				return new OnionRings(clock);
				break;
			default:
				return new CaesarSalad(clock);
			}
		}


		if (choice == 1) {
			int rand = _random.next_int(5); // Must be the number of different foods
			switch (rand) {
			case 0:
				return new Burger(clock);
				break;
			case 1:
				return new ChickenSoup(clock);
				break;
			case 2:
				return new ChickenStrips(clock);
				break;
			case 3:
				return new Steak(clock);
				break;
			case 4:
				return new Taco(clock);
				break;
			default:
				return new Spaghetti(clock);
			}
		}


		if (choice == 3) {
			int rand = _random.next_int(3); // Must be the number of different foods
			switch (rand) {
			case 0:
				return new Pie(clock);
				break;
			case 1:
				return new IceCream(clock);
				break;
			case 2:
				return new Cheesecake(clock);
				break;
			default:
				return new IceCream(clock);
			}
		}
	}

    
    void assignDishToCustomer(Customer *customer, int clock) {
        SelectionData *data = new SelectionData(rand_Dish(clock,0), rand_Dish(clock,1), rand_Dish(clock,2));
        eating_queue->addDishPair(customer, data);
    }
    
    int getTotalWait() {
        return total_wait;
    }
    
    int getNumServed() {
        return num_served;
    }
};

#endif

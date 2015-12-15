#ifndef EatingQueue_h
#define EatingQueue_h

#include <queue>
#include <map>
#include "SelectionData.h"
#include "Customer.h"

class EatingQueue {
private:
    std::priority_queue<Customer *, std::deque<Customer *>, CompareCustomer> the_queue;
    std::map<Customer *, SelectionData *> dishes;
    int total_wait;
    int num_served;
    
public:
    EatingQueue() : total_wait(0), num_served(0) {}
    
    int max_size;
    
    void setMaxSize(int m) {
        max_size = m;
    }
    
    void addDishPair(Customer *customer, SelectionData *data) {
        dishes.insert(std::pair<Customer *, SelectionData *>(customer, data));
    }
    
    void add(Customer *customer) {
        the_queue.push(customer);
        customer->setTimeInQueue(dishes[customer]->getAppetizer()->timeToEat());
    }
    
    void remove(Customer *customer, int clock) {
        num_served++;
        std::cout << "total_wait-d += " << clock << " - " << customer->getArrivalTime() << " = " << clock - customer->getArrivalTime() << std:: endl;
        total_wait += clock - customer->getArrivalTime();
        dishes.erase(customer);
        the_queue.pop();
        delete customer;
    }
    
    void update(int clock) {
        if (!the_queue.empty()) {
            // Pulls top customer, but does not remove from queue
            Customer *customer = the_queue.top();
            if (customer->ready(clock)) {
                // Customer is ready to move on to the next stage of their meal
                SelectionData *data = dishes[customer];
                switch (customer->getCurrentCourse()) {
                    case 0:
                        std::cout << "total_wait-a += " << clock << " - " << customer->getArrivalTime() << " = " << clock - customer->getArrivalTime() << std:: endl;
                        total_wait += clock - customer->getArrivalTime();
                        customer->setTimeInQueue(data->getEntree()->timeToEat());
                        customer->setCurrentCourse(1);
                        customer->setArrivalTime(clock);
                        break;
                    case 1:
                        std::cout << "total_wait-e += " << clock << " - " << customer->getArrivalTime() << " = " << clock - customer->getArrivalTime() << std:: endl;
                        total_wait += clock - customer->getArrivalTime();
                        customer->setTimeInQueue(data->getDessert()->timeToEat());
                        customer->setCurrentCourse(2);
                        customer->setArrivalTime(clock);
                    case 2:
                        remove(customer, clock);
                }
            }
        }
    }
    
    int getTotalWait() {
        return total_wait;
    }
    
    int getNumServed() {
        return num_served;
    }
};

#endif

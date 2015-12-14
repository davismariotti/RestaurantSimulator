#ifndef EatingQueue_h
#define EatingQueue_h

#include <queue>
#include <map>
#include "SelectionData.h"
#include "Customer.h"

class EatingQueue {
private:
    std::priority_queue<Customer *> the_queue;
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
    
    void remove(Customer *customer) {
        dishes.erase(customer);
        delete customer;
        num_served++;
    }
    
    void update(int clock) {
        if (!the_queue.empty()) {
            //Pulls top customer, but does not remove from queue
            Customer *customer = the_queue.top();
            if (customer->ready(clock)) {
                SelectionData *data = dishes[customer];
                switch (customer->getCurrentCourse()) {
                    case 0:
                        customer->setTimeInQueue(data->getEntree()->timeToEat());
                        break;
                    case 1:
                        customer->setTimeInQueue(data->getDessert()->timeToEat());
                    case 2:
                        remove(customer);
                }
            }
        }
    }
};

#endif

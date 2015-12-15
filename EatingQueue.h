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
    
    int total_customer_wait;
    
public:
    EatingQueue() : total_wait(0), num_served(0), total_customer_wait(0) {}
    
    int max_size;
    
    void setMaxSize(int m) {
        max_size = m;
    }
    
    size_t size() {
        return the_queue.size();
    }
    
    void addDishPair(Customer *customer, SelectionData *data) {
        dishes.insert(std::pair<Customer *, SelectionData *>(customer, data));
    }
    
    int getFirstDishTime(Customer *customer) {
        return dishes[customer]->getAppetizer()->timeToEat();
    }
    
    void add(Customer *customer) {
        the_queue.push(customer);
        customer->setTimeInQueue(dishes[customer]->getAppetizer()->timeToEat());
    }
    
    void remove(Customer *customer, int clock) {
        num_served++;
        total_wait += clock - customer->getArrivalTime();
        customer->incrementTotalTime(clock - customer->getArrivalTime());
        total_customer_wait += customer->getTotalTime();
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
                the_queue.pop();
                switch (customer->getCurrentCourse()) {
                    case 0:
                        total_wait += clock - customer->getArrivalTime();
                        customer->incrementTotalTime(clock - customer->getArrivalTime());
                        customer->setTimeInQueue(data->getEntree()->timeToEat());
                        customer->setCurrentCourse(1);
                        customer->setArrivalTime(clock);
                        the_queue.push(customer);
                        break;
                    case 1:
                        total_wait += clock - customer->getArrivalTime();
                        customer->incrementTotalTime(clock - customer->getArrivalTime());
                        customer->setTimeInQueue(data->getDessert()->timeToEat());
                        customer->setCurrentCourse(2);
                        customer->setArrivalTime(clock);
                        the_queue.push(customer);
                        break;
                    case 2:
                        remove(customer, clock);
                        break;
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
    
    int getCustomerTotalWait() {
        return total_customer_wait;
    }
};

#endif

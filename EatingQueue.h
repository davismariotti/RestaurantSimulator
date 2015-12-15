#ifndef EatingQueue_h
#define EatingQueue_h

#include <queue>
#include <map>
#include "SelectionData.h"
#include "Customer.h"

class EatingQueue {
private:
    std::priority_queue<Customer *, std::deque<Customer *>, CompareCustomer> the_queue0;
    std::priority_queue<Customer *, std::deque<Customer *>, CompareCustomer> the_queue1;
    std::priority_queue<Customer *, std::deque<Customer *>, CompareCustomer> the_queue2;
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
        return the_queue1.size() + the_queue0.size() + the_queue2.size();
    }
    
    void addDishPair(Customer *customer, SelectionData *data) {
        dishes.insert(std::pair<Customer *, SelectionData *>(customer, data));
    }
    
    int getFirstDishTime(Customer *customer) {
        return dishes[customer]->getAppetizer()->timeToEat();
    }
    
    void add(Customer *customer) {
		customer->setTimeInQueue(dishes[customer]->getAppetizer()->timeToEat());
        the_queue0.push(customer);
    }
    
    void remove(Customer *customer, int clock) {
        num_served++;
        total_wait += clock - customer->getArrivalTime();
        customer->incrementTotalTime(clock - customer->getArrivalTime());
        total_customer_wait += customer->getTotalTime();
        dishes.erase(customer);
        delete customer;
    }
    
    void update(int clock) {
        if (!the_queue0.empty()) {
            // Pulls top customer, but does not remove from queue
            Customer *customer = the_queue0.top();
            if (customer->ready(clock)) {
                the_queue0.pop();
                // Customer is ready to move on to the next stage of their meal
                SelectionData *data = dishes[customer];
                total_wait += clock - customer->getArrivalTime();
                customer->incrementTotalTime(clock - customer->getArrivalTime());
                customer->setTimeInQueue(data->getEntree()->timeToEat());
                customer->setCurrentCourse(1);
                customer->setArrivalTime(clock);
                the_queue1.push(customer);
            }
        }
        if (!the_queue1.empty()) {
            // Pulls top customer, but does not remove from queue
            Customer *customer = the_queue1.top();
            if (customer->ready(clock)) {
                the_queue1.pop();
                // Customer is ready to move on to the next stage of their meal
                SelectionData *data = dishes[customer];
                total_wait += clock - customer->getArrivalTime();
                customer->incrementTotalTime(clock - customer->getArrivalTime());
                customer->setTimeInQueue(data->getEntree()->timeToEat());
                customer->setCurrentCourse(2);
                customer->setArrivalTime(clock);
                the_queue2.push(customer);
            }
        }
        if (!the_queue2.empty()) {
            // Pulls top customer, but does not remove from queue
            Customer *customer = the_queue2.top();
            if (customer->ready(clock)) {
                the_queue2.pop();
                // Customer is ready to move on to the next stage of their meal
                remove(customer, clock);
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

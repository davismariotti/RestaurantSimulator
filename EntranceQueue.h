#ifndef EntranceQueue_h
#define EntranceQueue_h

#include <queue>
#include <string>
#include "Customer.h"
#include "Random.h"

extern Random _random;

class EntranceQueue {
private:
    double arrival_rate;
    std::queue<Customer *> the_queue;
    int total_wait;
    int num_served;
public:
    EntranceQueue() : total_wait(0), num_served(0) {}
    
    void set_arrival_rate(double arrival_rate) {
        this->arrival_rate = arrival_rate;
    }
    
    int get_total_wait() {
        return total_wait;
    }
    
    int get_num_served() {
        return num_served;
    }
    
    long size() {
        return the_queue.size();
    }
    
    void update(int clock) {
        if (_random.next_double() < arrival_rate) {
            the_queue.push(new Customer(clock));
        }
    }
    
    int getTotalWait() {
        return total_wait;
    }
    
    int getNumServed() {
        return num_served;
    }
    
    friend class TableQueue;
};

#endif /* EntranceQueue_h */

#ifndef EatingQueue_h
#define EatingQueue_h

#include <queue>
#include <map>
#include "Dish.h"

class EatingQueue {
private:
    std::priority_queue<Customer *> the_queue;
    std::map<Customer *, Dish *> dishes;
    int total_wait;
    int num_served;
    
public:
    EatingQueue() : total_wait(0), num_served(0) {}
    
    int max_size;
    
    void setMaxSize(int m) {
        max_size = m;
    }
    
    void remove(Customer *customer) {
        
    }
    
    void update(int clock) {
        
    }
};

#endif

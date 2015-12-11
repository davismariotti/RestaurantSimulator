#ifndef EatingQueue_h
#define EatingQueue_h

#include <queue>

class EatingQueue {
private:
    std::priority_queue<Customer *> the_queue;
    int total_wait;
    int num_served;
    
public:
    EatingQueue() : total_wait(0), num_served(0) {}
    
    int max_size;
    
    void remove(Customer *customer) {
        
    }
    
    void update(int clock) {
        
    }
};

#endif

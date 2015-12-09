#ifndef EatingQueue_h
#define EatingQueue_h

class EatingQueue {
private:
    TableQueue *entrance_queue;
    
    std::priority_queue<Customer *> the_queue;
    int total_wait;
    int num_served;
    int max_size;
    
public:
    EatingQueue() : total_wait(0), num_served(0) {}
        
};

#endif

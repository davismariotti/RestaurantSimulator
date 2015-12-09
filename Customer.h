#ifndef Customer_h
#define Customer_h

class Customer {
public:
    Customer(int clock) : arrival_time(clock) {}
    
    int time_in_queue;
    int arrival_time;
    
    void setTimeInQueue(int t) {
        time_in_queue = t;
    }
    
    int getTimeInQueue() {
        return time_in_queue;
    }
    
};

struct CompareByTime {
    bool operator()(Customer const & c1, Customer const & c2) {
        return c1.time_in_queue < c2.time_in_queue;
    }
};


#endif

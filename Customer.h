#ifndef Customer_h
#define Customer_h

class Customer {
private:
    int time_in_queue;
    int arrival_time;
    int current_course; // Can be 0, 1, or 2 (appetizer, entree, dessert)
    
public:
    Customer(int clock) : arrival_time(clock), time_in_queue(0), current_course(0) {}
    
    void setTimeInQueue(int t) {
        time_in_queue = t;
    }
    
    int getTimeInQueue() {
        return time_in_queue;
    }
    
    int getArrivalTime() {
        return arrival_time;
    }
    
    bool ready(int clock) {
        return arrival_time + time_in_queue < clock;
    }
    
    bool operator<(Customer const & c2) {
        return time_in_queue < c2.time_in_queue;
    }
    
};


#endif

#ifndef Customer_h
#define Customer_h

class Customer {
private:
    int time_in_queue;
    int arrival_time;
    int current_course; // Can be 0, 1, or 2 (appetizer, entree, dessert)
    int total_time;
    int clock_time_ready;
    
public:
    Customer(int clock) : arrival_time(clock), time_in_queue(0), current_course(0), total_time(0), clock_time_ready(0) {}
    
    void setTimeInQueue(int t) {
        time_in_queue = t;
    }
    
    void setArrivalTime(int t) {
        arrival_time = t;
        clock_time_ready = arrival_time + time_in_queue;
    }
    
    int getTimeInQueue() const {
        return time_in_queue;
    }
    
    int getArrivalTime() const {
        return arrival_time;
    }
    
    int getClockTimeReady() const {
        return clock_time_ready;
    }
    
    int getTotalTime() {
        return total_time;
    }
    
    void incrementTotalTime(int t) {
        total_time += t;
    }
    
    int getCurrentCourse() {
        return current_course;
    }
    
    void setCurrentCourse(int c) {
        current_course = c;
    }
    
    void nextCourse() {
        current_course++;
    }
    
    bool ready(int clock) {
        return arrival_time + time_in_queue <= clock;
    }
    
};

struct CompareCustomer {
public:
    bool operator()(Customer const *c1, Customer const *c2) const {
        return c1->getClockTimeReady() > c2->getClockTimeReady();
    }
};


#endif

#ifndef Dish_h
#define Dish_h

class Dish {
protected:
    int start;
public:
    Dish (int clock) {
        this->start = clock;
    }
    
    virtual bool isReady() = 0;
    
    virtual int timeToEat() = 0;
};


#endif

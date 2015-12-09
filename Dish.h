#ifndef Dish_h
#define Dish_h

class Dish() {
private:
    int start;
public:
    Dish (clock) {
        this->start = clock;
    }
    
    bool isReady() = 0;
    
    int timeToEat() = 0;
}


#endif

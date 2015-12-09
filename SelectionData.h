#ifndef SelectionData_h
#define SelectionData_h

#include "Dish.h"

class SelectionData {
private:
    Dish appetizer;
    Dish entree;
    Dish dessert;
public:
    SelectionData(Dish a, Dish e, Dish d) : appetizer(a), entree(e), dessert(d) {}
    
    Dish getAppetizer() {
        return appetizer;
    }
    
    Dish getEntree() {
        return entree;
    }
    
    Dish getDessert() {
        return dessert;
    }
};
#endif

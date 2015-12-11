#ifndef Simulator_h
#define Simulator_h

#include "Random.h"
#include "EntranceQueue.h"
#include "TableQueue.h"
#include "EatingQueue.h"

Random _random;

class Simulator {
private:
    int total_time;
    int clock;
    
    EntranceQueue *entrance_queue;
    TableQueue *table_queue;
    EatingQueue *eating_queue;
    
    
    int read_int(const std::string &prompt, int low, int high) {
        if (low >= high) // invalid range
            throw std::invalid_argument("invalid range specified");
        
        std::cin.exceptions(std::ios_base::failbit);
        int num = 0;
        while (true) {
            try {
                while (true) {
                    std::cout << prompt;
                    std::cin >> num;
                    if (num >= low && num <= high) { // within the specified range
                        std::cout << std::endl;
                        return num;
                    }
                }
            }
            catch (std::ios_base::failure) {
                std::cout << "Bad numeric string -- try again\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }
        }
    }
public:
    
    Simulator() {
        entrance_queue = new EntranceQueue();
        table_queue = new TableQueue();
        eating_queue = new EatingQueue();
    }

    void init() {
        std::cout << "Welcome to the Restaurant Simulator" << std::endl;
        total_time = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
        total_time *= 60;
        
        int table_count = read_int("How many tables will the restaurant have: ", 1, INT_MAX);
        table_queue->setMaxSize(table_count);
    }
    
    
    void run() {
        for(clock = 0; clock < total_time; ++clock) {
            entrance_queue->update(clock);
            table_queue->update(clock);
            eating_queue->update(clock);
        }
    }
};

#endif

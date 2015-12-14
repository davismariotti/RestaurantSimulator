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
        table_queue->init(entrance_queue, eating_queue);
    }

    void init() {
        std::cout << "Welcome to the Restaurant Simulator" << std::endl;
        total_time = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
        total_time *= 60;
        
        int table_count = read_int("How many tables will the restaurant have: ", 1, INT_MAX);
        eating_queue->setMaxSize(table_count);
        
        int rate = read_int("How many people will come each hour: ", 1, INT_MAX);
        double a_rate = rate / 60.0;
        entrance_queue->set_arrival_rate(a_rate);
    }
    
    
    void run() {
        for(clock = 0; clock < total_time; ++clock) {
            entrance_queue->update(clock);
            table_queue->update(clock);
            eating_queue->update(clock);
        }
        
        std::cout << "EntranceQueue - Total Wait: " << entrance_queue->getTotalWait() << std::endl;
        std::cout << "EntranceQueue - Number Served: " << entrance_queue->getNumServed() << std::endl;
        std::cout << "EntranceQueue - Average Wait: " << entrance_queue->getTotalWait() / entrance_queue->getNumServed() << std::endl;
        std::cout << "TableQueue - Total Wait: " << table_queue->getTotalWait() << std::endl;
        std::cout << "TableQueue - Number Served: " << table_queue->getNumServed() << std::endl;
        std::cout << "TableQueue - Average Wait: " << table_queue->getTotalWait() / table_queue->getNumServed() << std::endl;
        std::cout << "EatingQueue - Total Wait: " << eating_queue->getTotalWait() << std::endl;
        std::cout << "EatingQueue - Number Served: " << eating_queue->getNumServed() << std::endl;
        std::cout << "EatingQueue - Average Wait: " << eating_queue->getTotalWait() / eating_queue->getNumServed() << std::endl;
    }
};

#endif

#include <stdio.h>
#include <iostream>
#include "Simulator.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Simulator sim;
    sim.init();
    sim.run();
}
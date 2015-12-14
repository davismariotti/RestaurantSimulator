#include <stdio.h>
#include <iostream>
#include "Simulator.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Simulator sim = Simulator();
    sim.init();
    sim.run();
}
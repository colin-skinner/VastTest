#include <iostream>

#include "Simulation.h"
// #include "Truck.h"
// #include "Station.h"

using namespace std;

int main(int argc, char* argv[]) {

    Simulation sim;

    // If trucks and stations are specified
    if (argc == 3) {
        printf("\n----- Initialization -----\n");

        int trucks;
        int stations;

        try { trucks = stoi(argv[1]); }
        catch (const std::invalid_argument) {
            printf("Trucks must be an integer");
            return -1;
        }

        try { stations = stoi(argv[2]); }
        catch (const std::invalid_argument) {
            printf("Stations must be an integer");
            return -1;
        }

        sim.add_trucks(abs(trucks));
        sim.add_stations(abs(stations));

        // 72 Hours
        printf("\n----- Simulation -----\n");
        sim.simulate(72 * 60, false);
        // sim.simulate(70, 10000);

        printf("\n----- Statistics -----\n");
        auto stats = sim.calc_statistics();
    }

    
    else {
        printf("\n----- No trucks and stations specified. Defaulting to 500 and 5. -----\n");
        printf("\n----- Initialization -----\n");
        sim.add_trucks(500);
        sim.add_stations(5);

        // 72 Hours
        printf("\n----- Simulation -----\n");
        sim.simulate(72 * 60, false);
        // sim.simulate(70, 10000);

        printf("\n----- Statistics -----\n");
        auto stats = sim.calc_statistics();
    }


    
    return 0;
}
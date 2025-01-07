#include <iostream>
#include <assert.h>
#include "../Simulation.h"

using namespace std;

void assert_that(bool statement, const char* message) {
    if (!statement) throw std::runtime_error{message};
}

// Runs with 
// - random mining OFF (6 minutes)
// - 142 minutes (2 cycles of mining and unloading)
void test_single_truck() {
    Simulation sim;

    int trucks = 1;
    int stations = 1;

    sim.add_trucks(trucks, false);
    sim.add_stations(stations);

    // 72 Hours
    printf("\n----- Simulation -----\n");
    sim.simulate(142, false);
    // sim.simulate(70, 10000);

    printf("\n----- Statistics -----\n");
    auto stats = sim.calc_statistics();


    assert_that(
        *max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()) == 6,
        "Longest mining time should be 6 minutes."
    );

    assert_that(
        *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()) == 0,
        "Longest waiting time should be 0 minutes."
    );

    assert_that(
        stats.max_queue_length == 0,
        "Max queue length should be 0 minutes."
    );

    assert_that(
        stats.total_mining_min == 12,
        "Total mining minutes should be 12 minutes (6*2)"
    );

    assert_that(
        stats.total_waiting_min == 0,
        "Total waiting minutes should be 0 minutes"
    );
}


// Runs with 
// - 1000 trucks and 1000 stations
// - random mining OFF (6 minutes)
// - 142 minutes (2 cycles of mining and unloading)
void test_ten_trucks() {
    Simulation sim2;

    int trucks = 1000;
    int stations = 1000;

    sim2.add_trucks(trucks, false);
    sim2.add_stations(stations);

    // 72 Hours
    printf("\n----- Simulation -----\n");
    sim2.simulate(142, false);
    // sim.simulate(70, 10000);

    printf("\n----- Statistics -----\n");
    auto stats = sim2.calc_statistics();


    assert_that(
        *max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()) == 6,
        "Longest mining time should be 6 minutes."
    );

    assert_that(
        *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()) == 0,
        "Longest waiting time should be 0 minutes."
    );

    assert_that(
        stats.max_queue_length == 0,
        "Max queue length should be 0 minutes."
    );

    assert_that(
        stats.total_mining_min == 12000,
        "Total mining minutes should be 12000 minutes (1000*6*2)"
    );

    assert_that(
        stats.total_waiting_min == 0,
        "Total waiting minutes should be 0 minutes"
    );
}

int main(int argc, char* argv[]) {

    test_single_truck();
    test_single_truck();
    test_single_truck();
    test_ten_trucks();

    printf("\n\n\nPassed all tests!\n\n");
    
    return 0;
}
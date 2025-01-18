#include <iostream>
#include <assert.h>
#include "../src/Simulation.h"

#include "../unity/unity.h"

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
    LOG("\n----- Simulation -----\n");
    sim.simulate(142, false);
    // sim.simulate(70, 10000);

    LOG("\n----- Statistics -----\n");
    auto stats = sim.calc_statistics();


    // Longest mining time should be 6 minutes
    TEST_ASSERT_EQUAL(6,*max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()));

    // Longest waiting time should be 0 minutes
    TEST_ASSERT_EQUAL(0, *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()));
        
    // Max queue length should be 0
    TEST_ASSERT_EQUAL(0, stats.max_queue_length);

    // Total mining minutes should be 12 minutes (6*2)
    TEST_ASSERT_EQUAL(12, stats.total_mining_min);

    // Total waiting minutes should be 0 minutes 
    TEST_ASSERT_EQUAL(0, stats.total_waiting_min);
}


// Runs with 
// - 1000 trucks and 1000 stations
// - random mining OFF (6 minutes)
// - 142 minutes (2 cycles of 6 minute mining and 5 minute unloading)
void test_ten_trucks() {
    Simulation sim2;

    int trucks = 1000;
    int stations = 1000;

    sim2.add_trucks(trucks, false);
    sim2.add_stations(stations);

    // 72 Hours
    LOG("\n----- Simulation -----\n");
    sim2.simulate(142, false);
    // sim.simulate(70, 10000);

    LOG("\n----- Statistics -----\n");
    auto stats = sim2.calc_statistics();


    // Longest mining time should be 6 minutes
    TEST_ASSERT_EQUAL(6,*max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()));

    // Longest waiting time should be 0 minutes
    TEST_ASSERT_EQUAL(0, *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()));
        
    // Max queue length should be 0
    TEST_ASSERT_EQUAL(0, stats.max_queue_length);

    // Total mining minutes should be 12000 minutes (1000*6*2)
    TEST_ASSERT_EQUAL(12000, stats.total_mining_min);

    // Total waiting minutes should be 0 minutes 
    TEST_ASSERT_EQUAL(0, stats.total_waiting_min);
}

// Runs with 
// - 1000 trucks and 1 station
// - random mining OFF (6 minutes)
// - 36 minutes (1 cycle of mining and driving back)
// - Queue should be 999 trucks 
void test_ten_trucks_one_station_1() {
    Simulation sim;

    int trucks = 1000;
    int stations = 1;

    sim.add_trucks(trucks, false);
    sim.add_stations(stations);

    // 36 minutes
    LOG("\n----- Simulation -----\n");
    sim.simulate(60, false);

    LOG("\n----- Statistics -----\n");
    auto stats = sim.calc_statistics();


    // Longest mining time should be 6 minutes
    TEST_ASSERT_EQUAL(6,*max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()));

    // Longest waiting time should be 24 minutes (60 - 30 - 6 = 24)
    TEST_ASSERT_EQUAL(24, *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()));
        
    // Max queue length should be 999 trucks
    TEST_ASSERT_EQUAL(999, stats.max_queue_length);

    // Total mining minutes should be 6000 minutes (1000*6)
    TEST_ASSERT_EQUAL(6000, stats.total_mining_min);
}

// Runs with 
// - 1000 trucks and 2 stations
// - random mining OFF (6 minutes)
// - 36 minutes (1 cycle of mining and driving back)
// - Queue should be 499 trucks 
void test_ten_trucks_two_stations() {
    Simulation sim;

    int trucks = 1000;
    int stations = 2;

    sim.add_trucks(trucks, false);
    sim.add_stations(stations);

    // 36 minutes
    LOG("\n----- Simulation -----\n");
    sim.simulate(60, false);

    LOG("\n----- Statistics -----\n");
    auto stats = sim.calc_statistics();


    // Longest mining time should be 6 minutes
    TEST_ASSERT_EQUAL(6,*max_element(stats.longest_mining_times.begin(), stats.longest_mining_times.end()));

    // Longest waiting time should be 24 minutes (60 - 30 - 6 = 24)
    TEST_ASSERT_EQUAL(24, *max_element(stats.longest_waiting_times.begin(), stats.longest_waiting_times.end()));
        
    // Max queue length should be 499 trucks
    TEST_ASSERT_EQUAL(499, stats.max_queue_length);

    // Total mining minutes should be 6000 minutes (1000*6)
    TEST_ASSERT_EQUAL(6000, stats.total_mining_min);
}
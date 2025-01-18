#pragma once

#include <vector>
#include <memory>
#include "globals.h"

class Truck;
class Station;

struct SimulationStats {
    // Total stats
    int total_mining_min;
    int total_waiting_min;

    std::vector<int> longest_mining_times;
    std::vector<int> longest_waiting_times;

    std::vector<int> unloads; 

    int max_queue_length;

    SimulationStats() : total_mining_min{0}, total_waiting_min{0}, max_queue_length{0} {}
};

class Simulation {
private:
    long t_min;
    long end_time_min;
    std::vector<Truck*> trucks;
    std::vector<Station*> stations;

    SimulationStats stats;


public:
    Simulation();

    ~Simulation();

    // Adding objects to sim
    void add_trucks(int num_trucks, bool random_mining = true);
    void add_stations(int num_stations);

    // Starting 
    bool simulate(long end_time_min, bool report_time = true);

    void simulate_timestep(int minutes, bool report_time);
    Station* find_least_occupied_station();

    // Getters
    inline int get_sim_time() const {return t_min;}
    inline const std::vector<Truck*>& get_trucks() const {return trucks;}
    inline const std::vector<Station*>& get_stations() const {return stations;}
    
    // Reporting at the end of the sim
    const SimulationStats& calc_statistics();

    // static void report_statistics();

};
#pragma once

#include "SimObject.h"
#include "Simulation.h"
#include "globals.h"

#include <vector>
#include <queue>

class Truck;

struct StationStats {
    std::vector<int> num_trucks_waiting_by_min;
    std::vector<Truck*> current_truck_unloading_by_min;
};

class Station : public SimObject {
private:
    int action_length_min;
    std::queue<Truck*> truck_queue;


    // For keeping stats
    StationStats stats;
    
public:
    Station(Simulation* simulation);
    virtual ~Station();
    virtual void simulate_timestep();

    void add_truck(Truck* truck);
    void advance_queue();
    int get_queue_size() const;
    
    inline const std::queue<Truck*>& get_queue() const {return truck_queue;}

    void log_stats();

    const StationStats& finish_and_get_stats() const {return stats;}
};
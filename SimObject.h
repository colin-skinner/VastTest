#pragma once

#include <vector>

class Simulation;

// Base class for sim objects

class SimObject {
private:
public:
    Simulation* sim;
    int last_sim_time_min;
    virtual void simulate_timestep() = 0;

    virtual void log_stats() = 0;
};
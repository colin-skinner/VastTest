#pragma once

#include "SimObject.h"
#include "Simulation.h"
#include "globals.h"

#include <string>
#include <unordered_map>

class Station;

// States to return
#define MINING 0
#define DRIVING_FROM_MINE 1
#define WAITING_AT_STATION 2
#define UNLOADING 3
#define DRIVING_TO_MINE 4
#define BAD_STATE -1




// Struct for storing truck statistics
struct TruckStats {
    std::unordered_map<int, int> total_action_minutes_by_state{};

    // Longest
    int longest_mine;
    int longest_wait;

    // Total
    int mining_min;
    int waiting_min;
    int unloads;

    // To be initialized at the end
    float percent_of_time_mining;

    TruckStats() : longest_mine{0}, longest_wait{0}, mining_min{0}, waiting_min{0}, unloads{0}, percent_of_time_mining{0.0} {}

}; 


class Truck : public SimObject {
private:
    int last_action_start_min;
    int action_length_min;
    int state;
    Station* station;

    bool random_mining;

    // For keeping stats
    TruckStats stats;

    void run_state_machine_changes(int current_action_time_min);
    int select_mining_time(int smallest, int largest);

public:
    Truck(Simulation* simulation, bool random_mining = true);
    virtual ~Truck();

    // Runs every timestep
    virtual void simulate_timestep();
    void log_stats();

    // Function to call when station finishes unloading
    void notify_unloading();

    
    inline const int get_state() const {return state;}


    
    const TruckStats& finish_and_get_stats();

    // For LOgging purposes
    const char* get_state_string();

    
};
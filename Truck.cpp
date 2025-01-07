#include "Truck.h"
#include "Simulation.h"
#include "Station.h"


#include <math.h>

using namespace std;





// Not doing initializer lists so that I can group initializations
Truck::Truck(Simulation *simulation, bool random_mining)
{
    // Starts simulation at a mining site
    this->random_mining = random_mining;
    station = nullptr;

    // Truck variables
    state = MINING;
    action_length_min = select_mining_time(60, 5*60);
    last_action_start_min = 0;

    // SimObject variables
    last_sim_time_min = -1;
    sim = simulation;

    stats = TruckStats();
    
    // Preilitializing all states
    stats.total_action_minutes_by_state[MINING] = 0;
    stats.total_action_minutes_by_state[DRIVING_FROM_MINE] = 0;
    stats.total_action_minutes_by_state[WAITING_AT_STATION] = 0;
    stats.total_action_minutes_by_state[UNLOADING] = 0;
    stats.total_action_minutes_by_state[DRIVING_TO_MINE] = 0;
    

    // printf("ACTION LENGTH %d\n", action_length_min);
}

Truck::~Truck()
{
    
    // printf("Deleting truck\n");
}

void Truck::simulate_timestep()
{
    int current_sim_time_min = this->sim->get_sim_time();
    int time_diff_min = current_sim_time_min - last_sim_time_min;
    int action_time = current_sim_time_min - last_action_start_min;

    // For debugging
    // printf("time diff: %d\n", time_diff_min);
    // printf("current_time: %d\n", current_sim_time_min);
    // printf("action_time: %d\n", action_time);
    // printf("action_time: %d\n", action_length_min);

    // Must advance sim
    if (time_diff_min < 1) {
        return;
    }

    last_sim_time_min = current_sim_time_min;

    // If not finished with action, continue
    if (action_time < action_length_min) {
        // printf("ACTION\n");
        return;
    }

    
    run_state_machine_changes(action_time);
    
    
    // printf("CHANGING STATES\n");
    
    this->last_action_start_min = current_sim_time_min;

}


void Truck::run_state_machine_changes(int current_action_time)
{
    // printf("Switching state after %d min\n", action_length_min);

    // If mining is done done
    if (state == MINING) {
        // Track longest mining time
        action_length_min = DRIVING_TIME;
        this->state = DRIVING_FROM_MINE;
        return;
    }
            

    // Finished driving from mine 
    if (state == DRIVING_FROM_MINE) {
        // Find the station with the smallest queue length
        Station* least_station = sim->find_least_occupied_station();


        least_station->add_truck(this);
        this->station = least_station;
        this->state = WAITING_AT_STATION;

        return;
    }

    // Finished driving to mine
    if (state == DRIVING_TO_MINE) {

        // Set action time to a random minute from 60 to 300 minutes
        action_length_min = select_mining_time(60, 5*60);
        this->state = MINING;
        return;
    }   

    // Finished with unloading
    if (state == UNLOADING) {
        stats.unloads++;
        
        // Send signal to remove it from queue
        this->station->advance_queue();
        this->station = nullptr;

        action_length_min = DRIVING_TIME;
        this->state = DRIVING_TO_MINE;
        return;
    }

    

}

// From waiting to unloading
void Truck::notify_unloading()
{
    this->state = UNLOADING;
    action_length_min = UNLOADING_TIME;

    int wait_time = sim->get_sim_time() - last_action_start_min;
    stats.longest_wait = max(stats.longest_wait, wait_time);

    this->last_action_start_min = sim->get_sim_time();
    // printf("Unloading\n");
}

void Truck::log_stats()
{
    // printf("%d\t", state);
    // printf("%d\n", stats.total_action_minutes_by_state.at(MINING));
    stats.total_action_minutes_by_state[this->state]++;
}

int Truck::select_mining_time(int smallest, int largest) {
    int mining_time;
    if (random_mining) 
    {
        mining_time = smallest + (rand() % (largest-smallest + 1) );
    }
    else {
        mining_time = 6;
    }

    stats.longest_mine = max(stats.longest_mine, mining_time);

    return mining_time;
}


// For debugging purposes
const char* Truck::get_state_string()
{
    switch(state) {
        case DRIVING_FROM_MINE:
            return "driving from mine";

        case DRIVING_TO_MINE:
            return "driving to mine";

        case UNLOADING:
            return "unloading";

        case MINING:
            return "mining";

        case WAITING_AT_STATION:
            return "waiting at station";
        
        default:
            return "invalid state";
    }
    return nullptr;
}
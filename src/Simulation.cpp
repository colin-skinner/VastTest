#include "Truck.h"
#include "Station.h"
#include "Simulation.h"
#include <cstdio>
#include <stddef.h> // size_t
#include <unordered_map>


using namespace std;


Simulation::Simulation()
{
    // Member variables
    this->t_min = 0;
    this->end_time_min = 0;

}

Simulation::~Simulation()
{
    for (auto truckPtr : this->trucks) {
        delete truckPtr;
    }

    for (auto stationPtr : this->stations) {
        delete stationPtr;
    }
}

void Simulation::add_trucks(int num_trucks, bool random_mining)
{
    for (size_t i = 0; i < num_trucks; i++) {
        this->trucks.push_back(new Truck(this, random_mining));
    }

    LOG("Requested %d trucks and added %lu trucks\n", num_trucks, this->trucks.size());
}

void Simulation::add_stations(int num_stations)
{
    for (size_t i = 0; i < num_stations; i++) {
        this->stations.push_back(new Station(this));
    }

    LOG("Requested %d stations and added %lu stations\n", num_stations, this->stations.size());
}

bool Simulation::simulate(long end_time_min, bool report_time)
{
    this->end_time_min = end_time_min;
    LOG("Started %ld minute simulation\n",end_time_min);

    for (long i = 0; i < end_time_min; i++) {
        
        simulate_timestep(1, report_time);

    }

    LOG("Sim Stopped at %ld min\n",this->t_min);
    return false;
}

void Simulation::simulate_timestep(int minutes, bool report_time)
{
    
    if (trucks.size() == 0) {
        LOG("Need to add trucks to simulate");
        return;
    }

    if (stations.size() == 0) {
        LOG("Need to add stations to simulate");
        return;
    }

    if (report_time && (t_min % 10) == 0)
        LOG("Sim Time: %ld min\n", this->t_min);
    
    // LOG("Advanced sim time by %ld minutes to %ld\n", minutes, this->t_min);

    // Simulate trucks
    for (auto truck : trucks) {
        truck->simulate_timestep();
        
        // Use truck for stats
    }
    
    // Simulate stations
    for (auto station : stations) {
        station->simulate_timestep();
        
        // Use station for stats
    }


    // LOG("Truck is %s\n", trucks[0]->get_state_string());
    // Log truck and station states
    for (auto truck : trucks) {
        truck->log_stats();
        
        // Use truck for stats
    }
    
    // Simulate stations
    for (auto station : stations) {
        station->log_stats();
        
        // Use station for stats
    }


    this->t_min += minutes;
}

Station* Simulation::find_least_occupied_station() {

    unordered_map<int, Station*> queue_length_to_station;

    int min_queue_length = stations[0]->get_queue_size();

    for (const auto& station : stations) {
        int queue_size = station->get_queue_size();

        // Finds minimum queue size
        min_queue_length = min(queue_size, min_queue_length);

        queue_length_to_station[queue_size] = station;
    }

    return queue_length_to_station.at(min_queue_length);
}

const SimulationStats& Simulation::calc_statistics()
{
    stats = SimulationStats();

    stats.total_mining_min = 0;
    stats.total_waiting_min = 0;

    // Reports on simulation-wide stats 
    for (const auto& truck : trucks) {
        TruckStats truck_stats = truck->finish_and_get_stats();

        // Total stats
        stats.total_mining_min += truck_stats.total_action_minutes_by_state[MINING];
        stats.total_waiting_min += truck_stats.total_action_minutes_by_state[WAITING_AT_STATION];
        

        // Max stats
        stats.longest_mining_times.push_back(truck_stats.longest_mine);
        // printf("%d\n", truck_stats.longest_mine);
        stats.longest_waiting_times.push_back(truck_stats.longest_wait);
        // printf("%d\n", truck_stats.longest_wait);
        stats.unloads.push_back(truck_stats.unloads);


    }

    for (const auto& station : stations) {
        StationStats station_stats;
        station_stats = station->finish_and_get_stats();

        auto queues = station_stats.num_trucks_waiting_by_min;

        stats.max_queue_length = max(
            stats.max_queue_length, 
            *max_element(queues.begin(), queues.end())
        );

    }

    LOG("Most unloads: %d\n", *max_element(
        stats.unloads.begin(), stats.unloads.end())
    );

    LOG("Longest wait time: %d min\n", *max_element(
        stats.longest_waiting_times.begin(), stats.longest_waiting_times.end())
    );
    LOG("Longest mining time: %d min\n", *max_element(
        stats.longest_mining_times.begin(), stats.longest_mining_times.end())
    );

    LOG("Average time spent waiting: %.2f%%\n", 100 * (float)stats.total_waiting_min/ trucks.size() / end_time_min);
    LOG("Average time spent mining: %.2f%%\n", 100 * (float)stats.total_mining_min/ trucks.size() / end_time_min);

    LOG("Total mining minutes: %d min\n", stats.total_mining_min);
    LOG("Total waiting minutes: %d min\n", stats.total_waiting_min);

    LOG("Max queue length: %d trucks\n", stats.max_queue_length);

    
    // Reports on notable stats of distributions of individual trucks and stations
    // e.g. Truck that waited the most, truck that unloaded the most times

    return this->stats;
    

}

#include "Station.h"
#include "Truck.h"

Station::Station(Simulation *simulation)
{
    this->sim = simulation;
}

Station::~Station()
{
    // LOG("Deleting station\n");
}

void Station::simulate_timestep()
{
    if (truck_queue.size() == 0) {
        return;
    }

    Truck* front_truck = this->truck_queue.front();

    if (front_truck->get_state() == WAITING_AT_STATION) {
        front_truck->notify_unloading();
    }
    
}

void Station::add_truck(Truck *truck)
{
    truck_queue.push(truck);
}

void Station::advance_queue()
{
    // Send signal to new front of queue to advance
    this->truck_queue.pop();

    if (truck_queue.size() == 0) {
        return;
    }

    Truck* new_front = this->truck_queue.front();
    new_front->notify_unloading();
}

int Station::get_queue_size() const
{
    return truck_queue.size();
}

void Station::log_stats()
{
    // Queue includes the current truck that is unloading, so 1 is subtracted from the size
    stats.num_trucks_waiting_by_min.push_back(truck_queue.size() - 1);
    
    Truck* front_truck = nullptr;

    if (truck_queue.size() > 0) {
        front_truck = truck_queue.front();
    }
    stats.current_truck_unloading_by_min.push_back(front_truck);
}

## How to run
- To build, run `./build.sh`
    - Compiles using C++11 (which has range-based for loops and the "auto" type)
    - If there is an error running this script, run `chmod +x ./build.sh`
- To run, run `./simulation t s`, where t is the number of trucks and s is the number of stations
- Statistics should be reported at the end

## How the code is organized
Classes:
- SimObject:
    - Base class for all objects in the simulation
- Truck: 
    - Has a state machine
        - States: MINING, DRIVING_FROM_MINE, DRIVING_TO_MINE, UNLOADING, and WAITING_AT_STATION
    - Keeps track of number of its own statistics
- Station:
    - Keeps queue of Truck pointers that acts as its line of trucks waiting to unload
    - When a truck reaches the front of the queue, the station notifies the truck that it should begin unloading
- Simulation
    - Keeps time and calls the simulate_timestep() functions 
    - Has the "find station with least trucks" function for a truck to call


I ended up modeling this simulation after a CS polymorphism/inheritance project from one of my classes in which a central "Simulation" class calls the "simulate" functions of all the objects in the simulation. I also tried to avoid dynamic programming, since the only objects I needed to allocate were the trucks and stations at the beginning of the simulation.  


## Future Plan
As I neared about 4 total hours on the project, I realized that a lot of the rest of the implementation (in addition to finishing tests) would be logging and reporting all the statistics, which falls more into data science or analysis (like with GNC sims). It would take a lot more time to fully implement all my ideas (something I may do after I submit this because this is a really fun project). I had many more ideas for statistics that I included below but have not implemented all of them yet due to time constraints.

In general, I had more time, I would include more stats that track distributions rather than single numbers (i.e. maximum wait time).

I would include several more vectors that log the state of individual trucks/stations over the course of the simulation. I already included `total_action_minutes_by_state` for trucks and `current_truck_unloading_by_min` for stations, and theoretically, these could be used to derive all other stats. Here are some other stats that are useful.

_Possible Structures for Truck_
- Vector of mining times
    - e.g. If a truck mined twice first for 60 minutes, then for 120 minutes, it would create --> map[MINING] = {60,120};
    - Used to derive individual mining distributions
    - Can be used to determine
        - Truck with most mining sessions


- Vector of Station* at each unload
    - Which truck stopped at the most or fewest different stations.

_Possible Structures for Station_
- Vector of Truck* unloading at each minute
    - Can be used to determine distribution of which different trucks stopped at that station

_Possible Structutes for Simulation_
- Number of trucks in a given state per minute
    - e.g.
        - std::vector<int> trucks_mining_by_min
        - std::vector<int> trucks_waiting_at_stations_by_min
        - std::vector<int> current_truck_unloading_by_min
        - std::vector<int> trucks_going_to_mines_by_min
        - std::vector<int> trucks_coming_from_mines_by_min
    - Can graph distribution of trucks at each state over time



I would also add more stats that are helpful in assessing efficiency of the unloading stations. I already included `percent_of_time_mining` for each truck, which helps in maximizing the efficiency of an individual truck. One unimplemented stat might be `min_waiting_time`, which could be used to determine how many trucks had to wait 


## Closing Thoughts
I definitely think that I have a good intution for how to create a simulation such as this, with the central Simulation class running the whole program. But there are things I would improve for next time:

- Better testing (including a more test-as-I-go approach)
    - Includes modules that are better designed 
- Data validation for inputs
    - I didn't really have enough time
    - This also goes hand-in-hand with better testing, as this makes modules have more defined unit tests for each function

Overall, I think that given a larger timeframe to start (like a day or two), I would have spent some more time planning and creating tests for each module. In the past I've only used pytest and [Unity:https://www.throwtheswitch.org/unity] (but only in the context of microcontrollers and a specific VSCode IDE called PlatformIO), so it was a new experience trying to develop testing code for this simulation (I would have used Unity, but I did this challenge on my flight back from New Zealand, so I didn't have any internet to download the library). In the end, unfortunately I did not end up with enough time to close out the testing. Normally, my problem solving approach is to test as I go, but since I was a little pressed for time (and since this is a particularly large assignment), I defaulted to a "test the solution as a whole" approach, which is not something I normally do when coding. So that is something I would like to improve for next time, and homefully this summer working on Haven-1.

Thanks for this great opportunity!




echo "Building into \"simulation\""
clang++ -std=c++11 -o simulation Simulation.cpp Station.cpp Truck.cpp main.cpp
echo "Built!"
echo "Run with \"./simulation {num_trucks} {num_stations}\""

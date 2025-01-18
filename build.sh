echo "Building into \"build/simulation\""
clang++ -std=c++11 -DLOG_OUTPUT -o build/simulation src/Simulation.cpp src/Station.cpp src/Truck.cpp src/main.cpp
echo "Built!"
echo "Run with \"./build/simulation {num_trucks} {num_stations}\""

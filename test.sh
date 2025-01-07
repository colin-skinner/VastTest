echo "Building into \"test_sim\""
clang++ -std=c++11 -o test_sim Simulation.cpp Station.cpp Truck.cpp test/test_simulation.cpp
echo "Built!"
echo "Run with \"./test_sim\""

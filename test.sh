echo "Building into \"build/test_sim\""
clang -c ./unity/unity.c -o build/unity.o
clang++ -std=c++11 -DLOG_OUTPUT -o build/Simulation.o -c src/Simulation.cpp
clang++ -std=c++11 -o build/Station.o -c src/Station.cpp
clang++ -std=c++11 -DLOG_OUTPUT -o build/Truck.o -c src/Truck.cpp 
clang++ -std=c++11 -o build/test.o -c test/test_main.cpp 
clang++ build/Simulation.o build/Station.o build/Truck.o build/unity.o build/test.o -o build/test_sim
echo "Built!"
echo "Run with \"./build/test_sim\""

#include "../unity/unity.h"
#include "test_simulation.cpp"

void setUp(void) {
    // Setup code before each test (optional)
}

void tearDown(void) {
    // Cleanup code after each test (optional)
}


int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_single_truck);
    printf("\n");
    RUN_TEST(test_ten_trucks);
    printf("\n");
    RUN_TEST(test_ten_trucks_one_station_1);
    printf("\n");
    RUN_TEST(test_ten_trucks_two_stations);
    printf("\n");
    return UNITY_END();
}
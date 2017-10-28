#include "../libs/unity_fixture.h"
#include "LedDriver.h"

TEST_GROUP_RUNNER(LedDriver) {
    RUN_TEST_CASE(LedDriver, LedsOffAfterCreate);
    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
}

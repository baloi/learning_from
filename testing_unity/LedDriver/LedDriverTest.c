#include "../unity_fixture.h"
#include "LedDriver.h"

TEST_GROUP(LedDriver);

TEST_SETUP(LedDriver) {

}

TEST_TEAR_DOWN(LedDriver) {

}

TEST(LedDriver, LedsOffAfterCreate) {
    //TEST_FAIL_MESSAGE("Start here");
    uint16_t virtualLeds = 0xffff;
    LedDriver_Create(&virtualLeds);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne) {
    uint16_t virtualLeds;
    LedDriver_Create(&virtualLeds);
    LedDriver_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../libs/unity_fixture.h"
#include "LedDriver.h"

static uint16_t *ledsAddress; // static in this C file only
                    // makes ledsAddress only accessible to 
                    // this "module" effectively making it a
                    // private variable

void LedDriver_Create(uint16_t *address) {
    //*address = 0;
    ledsAddress = address;
    *ledsAddress = 0;
}

void LedDriver_TurnOn(int ledNumber) {
    *ledsAddress = 1;
}

void LedDriver_Destroy(void) {

}

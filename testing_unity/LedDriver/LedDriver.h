#ifndef D_LedDriver_H
#define D_LedDriver_H

void LedDriver_Create(uint16_t * address);
void LedDriver_TurnOn(int ledNumber);
void LedDriver_Destroy(void);
void LedsOffAfterCreate(void);

#endif

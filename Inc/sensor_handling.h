#ifndef _SENSOR_HANDLING_H
#define _SENSOR_HANDLING_H

#include "gpio.h"
#include <stdint.h>

void Sensor_CalculateSumValue(void);

int16_t Sensor_ReadSumValue(void);

#endif
#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

#include "tim.h"
#include <stdint.h>

typedef enum{
	MOTOR_0,
	MOTOR_1
}motor_t;


void Motor_Init (void);

void Motor_Set_Speed(motor_t motor,int16_t speed);

#endif
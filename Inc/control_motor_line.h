#ifndef _CONTROL_MOTOR_LINE_H_
#define _CONTROL_MOTOR_LINE_H_

#include <PID.h>
#include <motor_controller.h>
#include <sensor_handling.h>

void Control_CalculateValuePosition(int16_t valueSensor);

float Control_ReadValuePosition(void);

void Control_SetMotorLine(float value_position_PID,float position);

void Control_MotorByHand(uint8_t direction);
#endif
#include <control_motor_line.h>

float position_sensor;
//float pre_position_sensor;


void Control_CalculateValuePosition(int valueSensor){
	switch(valueSensor)
	{
		case 7:        
		{
			position_sensor=1.8;
			break;
		}
		case 12:
		{
			position_sensor=1.65;
			break;
		}
		case 15 :
		{
			position_sensor=1.65;
			break;
		}			
		case 5:
		{
			position_sensor=1.4;
			break;
		}
		case 3:
		{
			position_sensor=-1.4;
			break;
		}
		case 8:
		{
			position_sensor=0;
			break;
		}			
//		case 0:
//		{
//			position_sensor=0;
//		  break;
//		}
		case (4 | 9):
		{
			position_sensor= -1.65;
			break;
		}
		case 1:
		{
			position_sensor=-1.8;
			break;
		}
	}
	//pre_position_sensor=position_sensor;
}

float Control_ReadValuePosition(void){
	return position_sensor;
}

void Control_SetMotorLine(float value_position_PID,float ValuePosition)
{
	if(ValuePosition==0)
	{
		Motor_Set_Speed(MOTOR_0,180);
		Motor_Set_Speed(MOTOR_1,180);
	}
	
	if(value_position_PID<0)
	{
		if(ValuePosition<-1.5)
		{
			Motor_Set_Speed(MOTOR_0,-160);
			Motor_Set_Speed(MOTOR_1,value_position_PID*-1);
		}
		else
		{
			Motor_Set_Speed(MOTOR_0,0);
			Motor_Set_Speed(MOTOR_1,value_position_PID*-1);	
		}
	}
	if(value_position_PID>0)
	{
		if(ValuePosition>1.5)
		{
			Motor_Set_Speed(MOTOR_0,value_position_PID);
			Motor_Set_Speed(MOTOR_1,-160);
		}
		else
		{
			Motor_Set_Speed(MOTOR_0,value_position_PID);
			Motor_Set_Speed(MOTOR_1,0);
		}
	}
}
	
//float Control_ReadValuePrePosition(void){
//	return pre_position_sensor;
//}
	


/*
function Control by hand
*/
void Control_MotorByHand(uint8_t direction){
	switch (direction)
	{
		case 'r':
		{
			Motor_Set_Speed(MOTOR_0,100);
			Motor_Set_Speed(MOTOR_1,200);
			break;
		}
		case 'l':
		{
			Motor_Set_Speed(MOTOR_0,200);
			Motor_Set_Speed(MOTOR_1,100);
			break;
		}
		case 'f':
		{
			Motor_Set_Speed(MOTOR_0,210);
			Motor_Set_Speed(MOTOR_1,210);
			break;
		}
		case 'b':
		{
			Motor_Set_Speed(MOTOR_0,-210);
			Motor_Set_Speed(MOTOR_1,-210);
			break;
		}
	}
}



















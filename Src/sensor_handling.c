#include "sensor_handling.h"
#include "user_define.h"

int16_t ReadSensor[4];
int16_t SumIndexArrySensor=0;
int i;


void Sensor_CalculateSumValue(void){
	ReadSensor[0] = HAL_GPIO_ReadPin(SENSOR0_DIR_PORT,SENSOR0_DIR_PIN);  //7
	ReadSensor[1] = HAL_GPIO_ReadPin(SENSOR1_DIR_PORT,SENSOR1_DIR_PIN);  //5
	ReadSensor[2] = HAL_GPIO_ReadPin(SENSOR2_DIR_PORT,SENSOR2_DIR_PIN);  //3
	ReadSensor[3] = HAL_GPIO_ReadPin(SENSOR3_DIR_PORT,SENSOR3_DIR_PIN);  //1
	
	for(i=0;i<=3;i++){
		if(ReadSensor[i]==0){
			SumIndexArrySensor+=2*i+1;
		}
	}
}


int16_t Sensor_ReadSumValue(void){
	return SumIndexArrySensor;
}

void Sensor_ResetSumValue(void){
	SumIndexArrySensor=0;
}
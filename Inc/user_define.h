#ifndef _USER_DEFINE_H_
#define _USER_DEFINE_H_

/*
define motor right
*/
#define MOTOR0_DIR0_PORT 	GPIOB
#define MOTOR0_DIR1_PORT 	GPIOB
#define MOTOR0_DIR0_PIN 	GPIO_PIN_0
#define MOTOR0_DIR1_PIN 	GPIO_PIN_1
#define MOTOR0_TIMER 			htim4
#define MOTOR0_CHANNEL 		TIM_CHANNEL_3

/*
define motor left
*/
#define MOTOR1_DIR0_PORT 	GPIOB
#define MOTOR1_DIR1_PORT 	GPIOB
#define MOTOR1_DIR0_PIN 	GPIO_PIN_10
#define MOTOR1_DIR1_PIN 	GPIO_PIN_11
#define MOTOR1_TIMER 			htim4
#define MOTOR1_CHANNEL 		TIM_CHANNEL_4

/*
Using for revert motor
*/
//#define MOTOR0_REVERT
//#define MOTOR1_REVERT


/*
define pin read sensor
*/
#define SENSOR0_DIR_PORT 	GPIOB				// right
#define SENSOR0_DIR_PIN 	GPIO_PIN_5

#define SENSOR1_DIR_PORT 	GPIOB
#define SENSOR1_DIR_PIN 	GPIO_PIN_4


#define SENSOR2_DIR_PORT 	GPIOB
#define SENSOR2_DIR_PIN 	GPIO_PIN_3


#define SENSOR3_DIR_PORT 	GPIOA				// left
#define SENSOR3_DIR_PIN 	GPIO_PIN_15


#endif 


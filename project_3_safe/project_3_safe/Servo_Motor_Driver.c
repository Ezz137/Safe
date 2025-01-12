/*
 * Servo_Motor_Driver.c
 *
 * Created: 05/01/2025 01:38:26
 *  Author: zezom
 */ 
#include "Timer1_driver.h"

void Servo_Motor_vSend_Degree (double degree)
{
	Timer1_FAST_PWM_ICR(degree);
}
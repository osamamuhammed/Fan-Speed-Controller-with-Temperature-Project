 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: Source file for DC Motor Driver
 *
 * Author: Osama Muhammed
 *
 *******************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * Initialize the DC Motor:
 * 1. Setup the direction for the two motor pins through the GPIO driver.
 * 2. Stop at the DC-Motor at the beginning through the GPIO driver.
 *
 */
void DcMotor_Init(void){
	/* configure pin PB0 and PB1 as output pins */
	GPIO_setupPinDirection(PORTB_ID, PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);

	/*Stop the two DC Motors at the beginning*/
	GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);

}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 *
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	/* Choose rotation state : CW or CCW or Stop */
	switch (state) {
		case STOP:
			GPIO_writePin(PORTB_ID, PIN0_ID,LOGIC_LOW);
			GPIO_writePin(PORTB_ID, PIN1_ID,LOGIC_LOW);
			break;
		case CW:
			GPIO_writePin(PORTB_ID, PIN0_ID,LOGIC_HIGH);
			GPIO_writePin(PORTB_ID, PIN1_ID,LOGIC_LOW);
			break;
		case CCW:
			GPIO_writePin(PORTB_ID, PIN0_ID,LOGIC_LOW);
			GPIO_writePin(PORTB_ID, PIN1_ID,LOGIC_HIGH);
			break;
	}
	/*Send the required duty cycle to the PWM driver*/
		PWM_Timer0_Start(speed);
}

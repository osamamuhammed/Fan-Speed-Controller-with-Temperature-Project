/*
 ================================================================================================
 Name        : FanCtrl.c
 Author      : Osama M. Shehata
 Description : Test the controller system for a fan with temperature sensor
 Date        : 3/7/2023
 ================================================================================================
 */

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "dc_motor.h"

int main(void)
{
	uint8 temp;
	/* Initialize ADC with
	 * Internal reference voltage 2.56 volt
	 * Pre-scalar: F_CPU/8
	 */
	ADC_ConfigType ADC_Configurations = {INTERNAL, F_CPU_8};
	LCD_init(); /* initialize LCD driver */
	ADC_init(&ADC_Configurations); /* initialize ADC driver with required configuration*/
	DcMotor_Init();

	LCD_displayStringRowColumn(0,4,"Fan is OFF ");
	LCD_displayStringRowColumn(1, 4, "Temp =    C");

    while(1)
    {
    	// Update temprature value
    	temp = LM35_getTemperature();

    if(temp < 30)
	{
    	// If the temperature is less than 30C turn off the fan.
		LCD_displayStringRowColumn(0,4,"Fan is OFF ");
		DcMotor_Rotate(STOP,0);
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		LCD_moveCursor(1,13);
		LCD_displayCharacter(' ');
		if (temp <10){
			LCD_moveCursor(1,12);
			LCD_displayCharacter(' ');

		}
	}

	else if (temp >=30 && temp < 60)
	{
		// If the temperature is greater than or equal 30C turn on the fan with 25% of its maximum speed.
		LCD_displayStringRowColumn(0,4,"Fan is ON ");
		DcMotor_Rotate(CCW,25);
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		LCD_moveCursor(1,13);
		LCD_displayCharacter(' ');
	}
	else if (temp >=60 && temp < 90)
	{
		// If the temperature is between 60 and 90 turn on the fan with 50% of its maximum speed.
		LCD_displayStringRowColumn(0,4,"Fan is ON ");
		DcMotor_Rotate(CCW,50);
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		LCD_moveCursor(1,13);
		LCD_displayCharacter(' ');

	}

	else if (temp >=90 && temp < 120)
	{
		// If the temperature is between 90 and 120 turn on the fan with 75% of its maximum speed.
		LCD_displayStringRowColumn(0,4,"Fan is ON ");
		DcMotor_Rotate(CCW,75);
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
		LCD_moveCursor(1,13);
		LCD_displayCharacter(' ');
	}

	else if(temp >= 120)
	{
		// If the temperature is greater than or equal 120C turn on the fan with 100% of its maximum speed.
		LCD_displayStringRowColumn(0,4,"Fan is ON ");
		DcMotor_Rotate(CCW,100);
		LCD_moveCursor(1,11);
		LCD_intgerToString(temp);
	}

    }
}

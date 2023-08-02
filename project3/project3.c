 /******************************************************************************
 *
 * Project : Fan Controller System
 *
 * File Name: project3.c
 *
 * Description: control the fan speed based on the input of the LM35 temperature
 * 			    sensor
 *
 * Author: Mohamed Hossam
 *
 *******************************************************************************/
#include"lm35_sensor.h"
#include"dc_motor.h"
#include"lcd.h"
#include"adc.h"

int main()
{
	uint8 T;
	ADC_ConfigType config;
	config.prescaler=F_CPU_8;
	config.ref_volt=INTERNAL;
	ADC_init(&config);
	DcMotor_init();
	LCD_init();
	LCD_displayStringRowColumn(0, 3, "FAN is OFF");
	LCD_displayStringRowColumn(1, 3, "Temp =    C");
	for(;;)
	{
		/* get sensor temperature */
		T=LM35_getTemperature();
		/* display the temperature on the LCD */
		LCD_moveCursor(1,10);
		if(T < 10)
		{
			LCD_integerToString(T);
			LCD_displayString("  ");
		}
		else if(T < 100)
		{
			LCD_integerToString(T);
			LCD_displayCharacter(' ');
		}
		else
		{
			LCD_integerToString(T);
		}
		/* control the fan speed based on the temperature
		 * and display whether the fan is ON or OFF */
		if(T < 30)
		{
			DcMotor_Rotate(STOP, 0);
			LCD_displayStringRowColumn(0, 3, "FAN is OFF");
		}
		else if(T < 60)
		{
			DcMotor_Rotate(CW, 25);
			LCD_displayStringRowColumn(0, 3, "FAN is ON ");
		}
		else if(T < 90)
		{
			DcMotor_Rotate(CW, 50);
			LCD_displayStringRowColumn(0, 3, "FAN is ON ");
		}
		else if(T < 120)
		{
			DcMotor_Rotate(CW, 75);
			LCD_displayStringRowColumn(0, 3, "FAN is ON ");
		}
		else
		{
			DcMotor_Rotate(CW, 100);
			LCD_displayStringRowColumn(0, 3, "FAN is ON ");
		}
	}
}

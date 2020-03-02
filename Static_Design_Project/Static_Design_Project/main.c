/*
 * INTERUPSTRUCT.c
 *
 * Created: 12/24/2019 4:48:13 PM
 * Author : Ahmed
 */ 
/*
#include "../Static_Design_Project/MCAL/External Interrupt/ExternalInterrupt.h"
#include "../Static_Design_Project/MCAL/External Interrupt/interrupts.h"
#include "../Static_Design_Project/MCAL/DIO/DIO.h"
#include "../Static_Design_Project/MCAL/Timer/Timer.h"

//#include "motor.h"
//#include "PWM.h"
//#include "ICU.h"
#include "../Static_Design_Project/Extra/softwareDelay.h"
#include "../Static_Design_Project/ECUAL/US/Us.h"
#include "../Static_Design_Project/Application layer/Steering/Steering.h"
#include "../Static_Design_Project/Application layer/Car_SM/car_sm.h"
#include "../Static_Design_Project/MCAL/PWM/PWM.h"
*/

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "char_lcd.h"
#include "ICU.h"
#include "Us.h"
#include "interrupts.h"
#include "Steering.h"
#include "Timer.h"
#include "ExternalInterrupt.h"
#include "car_sm.h"

/*uint32 sg32_Distance;

void test (void)
{
	DIO_Toggle(GPIOC,FULL_PORT);
}*/

void main (void)
{
	GIE();
	/*char str[20];
	uint16 result;
	PORTB_DIR=BIT4|BIT6|BIT5|BIT7;
	Icu_cfg_s ICU;
	ICU.ICU_Ch_No=2;
	ICU.ICU_Ch_Timer=2;

	Car_SM_Init();
	LCD_init();
	LCD_send_string("Hiiii");
	_delay_ms(500);
	LCD_clear();*/
	Car_SM_Init();
	
	while (1)
	{
		/*Us_GetDistance(&sg32_Distance);
		Car_SM_Update();
		itoa(sg32_Distance, str, 10);
		LCD_goto_xy(0,0);
		LCD_clear();
		LCD_send_string(str);
		_delay_ms(200);*/
		Car_SM_Update();
	}
}
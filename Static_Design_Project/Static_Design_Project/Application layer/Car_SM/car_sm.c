/*
 * car_sm.c
 *
 * Created: 12/25/2019 5:28:33 PM
 *  Author: Johnny
 */ 


/********************************************************/
/*					Files Includes						*/
/********************************************************/

#include "car_sm.h"
#include "Steering.h"
#include "Us.h"
#include "softwareDelay.h"3
#if 0
#include <util/delay.h>
#endif


/********************************************************/
/*					Global variables					*/
/********************************************************/

uint32 sg32_Distance;

/*
 * Fun----------: ERROR_STATUS Car_SM_Init(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: Initiate the car state machine with state"forward at speed 80%",
 * -------------- And initiate steering and ultrasonic functions
*/

ERROR_STATUS Car_SM_Init(void)
{
	Us_Init();
	Steering_Init();
	return E_OK;
}


/*
 * Fun----------: ERROR_STATUS Car_SM_Update(void);
 * Input--------: Nothing
 * Output-------: Nothing
 * Return-------: ERROR_STATUES
 * -------------- #E_Ok	->function operation is okay, no error
 * -------------- #E_Nok->function operation faild, error exists
 * Description--: changes car state according to the ultrasonic input
 * -------------- And represents the motors output for each state
*/

enum States
{
	Forward,Backward,MaximumSpeed
}States;

ERROR_STATUS Car_SM_Update(void)
{
	Us_Trigger();
	Us_GetDistance(&sg32_Distance);
	switch (States)
	{
		case MaximumSpeed:
		Steering_SteerCar(CAR_FORWARD,60);
		if (sg32_Distance>50)
		{
			States=MaximumSpeed;
		}
		else if ((sg32_Distance<=50)&&(sg32_Distance>=40))
		{
			States = Forward;
		}
		
		else if (sg32_Distance <= 40)
		{
			States = Backward;
		}
		else
		{
			/*Do Nothing*/
		}
		
		break;
		
		case Forward:
		Steering_SteerCar(CAR_FORWARD,30);
		if (sg32_Distance<40)
		{
			States=Backward;
		}
		else if (sg32_Distance>50)
		{
			States=MaximumSpeed;
		}
		else if ((sg32_Distance >40 ) && (sg32_Distance <= 50))
		{
			States=Forward;
		}
		break;		
		
		case Backward:
		Steering_SteerCar(CAR_BACKWARD,60);	
		SwDelay_ms(100);
		if (sg32_Distance>=40)
		{
			Steering_SteerCar(CAR_RIGHT,60);
			SwDelay_ms(600);
			Steering_SteerCar(CAR_FORWARD,30);
			States=Forward;
		}
		break;
	}
	return E_OK;
}
/*
 * Motor.c
 *
 * Created: 12/25/2019 4:29:20 AM
 *  Author: Johnny
 */ 

#include "motor.h"
#include "PWM.h"
#include "DIO.h"

/********************************************************/
/*					 Structure	         				*/
/********************************************************/

Pwm_Cfg_s_t Pwm_Init_Motor1_s= {0};
Pwm_Cfg_s_t Pwm_Init_Motor2_s= {0};
DIO_Cfg_s DIO_Init_Motor1_s= {0};
DIO_Cfg_s DIO_Init_Motor2_s= {0};

/**
 * Function			: Motor_Init
 * Input		: motorNumber
 *	  	  		  #def
 *	  	  		  number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: ERROR_STATUS
 * Description	: Initialize (Enable, IN1, IN2) pins as digital outputs.
 */
 ERROR_STATUS Motor_Init(uint8 Motor_Number)
 { 
	 switch (Motor_Number)
	 {
		 case MOTOR_1:
		 Pwm_Init_Motor1_s.Channel=PWM_CH1A;
		 Pwm_Init_Motor1_s.Prescaler=PWM_PRESCALER_64;
		 Pwm_Init(&Pwm_Init_Motor1_s);
		 DIO_Init_Motor1_s.dir=OUTPUT;
		 DIO_Init_Motor1_s.GPIO=GPIOD;
		 DIO_Init_Motor1_s.pins=BIT2|BIT3;
		 DIO_init(&DIO_Init_Motor1_s);
		 break;
//------------------------------------------------------------------------------------------------------//
		 case MOTOR_2:
		 Pwm_Init_Motor2_s.Channel=PWM_CH1B;
		 Pwm_Init_Motor2_s.Prescaler=PWM_PRESCALER_64;
		 Pwm_Init(&Pwm_Init_Motor2_s);
		 DIO_Init_Motor2_s.dir=OUTPUT;
		 DIO_Init_Motor2_s.GPIO=GPIOD;
		 DIO_Init_Motor2_s.pins=BIT6|BIT7;
		 DIO_init(&DIO_Init_Motor2_s);
		 break;
//------------------------------------------------------------------------------------------------------//
		 default:
		 return E_NOK;
		 break;
	 }
	 return E_OK;
 }
 
/**
 * Fun		 : Motor_Direction
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2

			   @param Motor_Direction
			   #define
			   Stop, Forward, Backward
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor direction from getting the motor number and the direction.
*/
ERROR_STATUS Motor_Direction(uint8 Motor_Number, uint8 Motor_Direction)
{
	switch(Motor_Number)
	{
		case MOTOR_1:
		switch(Motor_Direction)
		{
			case MOTOR_STOP:
			DIO_Write(GPIOD,BIT2,LOW);
			DIO_Write(GPIOD,BIT3,LOW);
			break;
//------------------------------------------------------------------------------------------------------//
			case MOTOR_FORWARD:
			DIO_Write(GPIOD,BIT2,HIGH);
			DIO_Write(GPIOD,BIT3,LOW);
			break;
//------------------------------------------------------------------------------------------------------//
			case MOTOR_BACKWORD:
			DIO_Write(GPIOD,BIT2,LOW);
			DIO_Write(GPIOD,BIT3,HIGH);
			break;
//------------------------------------------------------------------------------------------------------//			
			default:
			return E_NOK;
			break;
		}
		break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
		case MOTOR_2:
		switch(Motor_Direction)
		{
			case MOTOR_STOP:
			DIO_Write(GPIOD,BIT6,LOW);
			DIO_Write(GPIOD,BIT7,LOW);
			break;
//------------------------------------------------------------------------------------------------------//			
			case MOTOR_FORWARD:
			DIO_Write(GPIOD,BIT6,HIGH);
			DIO_Write(GPIOD,BIT7,LOW);
			break;
//------------------------------------------------------------------------------------------------------//
			case MOTOR_BACKWORD:
			DIO_Write(GPIOD,BIT6,LOW);
			DIO_Write(GPIOD,BIT7,HIGH);
			break;
//------------------------------------------------------------------------------------------------------//
			default:
			return E_NOK;
			break;			
		}
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_Start
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Start the motor.
*/
ERROR_STATUS Motor_Start(uint8 Motor_Number, uint8 Mot_Speed)
{
	switch (Motor_Number)
	{
		case MOTOR_1:
		Pwm_Start(Pwm_Init_Motor1_s.Channel,Mot_Speed,1000);
		break;
//------------------------------------------------------------------------------------------------------//
		case MOTOR_2:
		Pwm_Start(Pwm_Init_Motor2_s.Channel,Mot_Speed,1000);	
		break;	
//------------------------------------------------------------------------------------------------------//
		default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/**
 * Fun		 : Motor_SpeedUpdate
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
			   @param Mot_Speed
			   set the motor speed
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: Controls the motor speed from getting the motor number and the speed.
*/
ERROR_STATUS Motor_SpeedUpdate(uint8 Motor_Number, uint8 Speed)
{
	switch (Motor_Number)
	{
		case MOTOR_1:
		Pwm_Update(Pwm_Init_Motor1_s.Channel,Speed,1000);
		break;
//------------------------------------------------------------------------------------------------------//
		case MOTOR_2:
		Pwm_Update(Pwm_Init_Motor2_s.Channel,Speed,1000);
		break;
//------------------------------------------------------------------------------------------------------//
		default:
		return E_NOK;
		break;		
	}
	return E_OK;
}

/**
 * Fun		 : Motor_Stop
 * input	 : @param Motor_Number
			   #define
		       MOTOR_1, MOTOR_2
 * output  	 : no output
 * return 	 : ERROR_STATUS
 * Description: stop the motor.
*/
ERROR_STATUS Motor_Stop(uint8 Motor_Number)
{
	switch (Motor_Number)
	{
		case MOTOR_1:
		Pwm_Stop(Pwm_Init_Motor1_s.Channel);
		break;
//------------------------------------------------------------------------------------------------------//
		case MOTOR_2:
		Pwm_Stop(Pwm_Init_Motor2_s.Channel);
		break;
//------------------------------------------------------------------------------------------------------//
		default:
		return E_NOK;
		break;
	}	
	return E_OK;
}

 /**
 * Func			: Motor_GetStatus
 * Input		: Motor_Number
 *	  	  		 #def
 *	  	  		 number of motor (MOTOR_1, MOTOR_2)
 * output		: none
 * In out		: none
 * Return		: Initialization_STATUS
 * Description	: Returns status of the motor whether initialized or not
 */
 uint8 Motor_GetStatus(uint8 Motor_Number)
 {
	 uint8 Status=0;
	 switch (Motor_Number)
	 {
		 case MOTOR_1:
		 if (DIO_Init_Motor1_s.dir==OUTPUT)
		 {
			 Status=E_OK;
			 return Status;
		 }
		 else if (DIO_Init_Motor1_s.dir==INPUT)
		 {
			 Status=E_NOK;
			 return Status;
		 }
		 break;
//------------------------------------------------------------------------------------------------------//
		 case MOTOR_2:
		 if (DIO_Init_Motor2_s.dir==OUTPUT)
		 {
			 Status=E_OK;
			 return Status;
		 }
		 else if (DIO_Init_Motor2_s.dir==INPUT)
		 {
			 Status=E_NOK;
			 return Status;
		 }
		 break;
//------------------------------------------------------------------------------------------------------//
		 default:
		 return E_NOK;
		 break;
	 }
	 return E_OK;
 }

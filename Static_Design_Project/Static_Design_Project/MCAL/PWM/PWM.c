/*
 * PWM.c
 *
 * Created: 12/23/2019 12:41:29 PM
 *  Author: Johnny
 */ 

/********************************************************/
/*					Files Includes						*/
/********************************************************/

#include "PWM.h"
#include "registers.h"


/********************************************************/
/*					 Macros		         				*/
/********************************************************/

static uint8 sgu8_PWM_CH0_Prescaler_Mask; // stores the values which will be used to set the TCCR register
static uint8 sgu8_PWM_CH1A_Prescaler_Mask;
static uint8 sgu8_PWM_CH1B_Prescaler_Mask;
static uint8 sgu8_PWM_CH2_Prescaler_Mask;
//------------------------------------------------------------------------------------------------------//
static uint16 sgu16_PWM_CH0_Prescaler_Value; // stores the values which will be used to calculate the ICR value
static uint16 sgu16_PWM_CH1A_Prescaler_Value;
static uint16 sgu16_PWM_CH1B_Prescaler_Value;
static uint16 sgu16_PWM_CH2_Prescaler_Value;
//------------------------------------------------------------------------------------------------------//


/*********************************************************************************/
/* Function: Error_State Pwm_Init(Pwm_Cfg_s_t *Pwm_Cfg);                         */
/* Type: public                                                                  */
/* Input parameters: Pwm_Cfg Structure (channel number, Prescaler)               */
/* Return type : void                                                            */
/*                                                                               */
/* Description: initialize the PWM configuration                                 */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Init(Pwm_Cfg_s_t *Pwm_Cfg)
{
	switch (Pwm_Cfg->Channel)
	{
		case PWM_CH0:
		switch (Pwm_Cfg->Prescaler)
		{
			case PWM_PRESCALER_NO:
			sgu8_PWM_CH0_Prescaler_Mask=0x01;
			sgu16_PWM_CH0_Prescaler_Value=1;
			break;
//------------------------------------------------------------------------------------------------------//
			case PWM_PRESCALER_8:
			sgu8_PWM_CH0_Prescaler_Mask=0x02;
			sgu16_PWM_CH0_Prescaler_Value=8;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_64:
			sgu8_PWM_CH0_Prescaler_Mask=0x03;
			sgu16_PWM_CH0_Prescaler_Value=64;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_256:
			sgu8_PWM_CH0_Prescaler_Mask=0x04;
			sgu16_PWM_CH0_Prescaler_Value=256;
			break;
//------------------------------------------------------------------------------------------------------//						
			case PWM_PRESCALER_1024:
			sgu8_PWM_CH0_Prescaler_Mask=0x05;
			sgu16_PWM_CH0_Prescaler_Value=1024;
			break;
//------------------------------------------------------------------------------------------------------//
			default:
			return E_NOK;
			break;
		}
//------------------------------------------------------------------------------------------------------//
		TCCR0|=(1<<5) | (1<<6);
		PORTB_DIR=(1<<3); 
		break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1A:
		switch(Pwm_Cfg->Prescaler)
		{
			case PWM_PRESCALER_NO:
			sgu8_PWM_CH1A_Prescaler_Mask=0x01;
			sgu16_PWM_CH1A_Prescaler_Value=1;
			break;
//------------------------------------------------------------------------------------------------------//
			case PWM_PRESCALER_8:
			sgu8_PWM_CH1A_Prescaler_Mask=0x02;
			sgu16_PWM_CH1A_Prescaler_Value=8;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_64:
			sgu8_PWM_CH1A_Prescaler_Mask=0x03;
			sgu16_PWM_CH1A_Prescaler_Value=64;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_256:
			sgu8_PWM_CH1A_Prescaler_Mask=0x04;
			sgu16_PWM_CH1A_Prescaler_Value=256;
			break;	
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_1024:
			sgu8_PWM_CH1A_Prescaler_Mask=0x05;
			sgu16_PWM_CH1A_Prescaler_Value=1024;
			break;	
		}
//------------------------------------------------------------------------------------------------------//		
		TCCR1A|=(1<<7);
		TCCR1B|=(1<<4);
		PORTD_DIR|=(1<<5);
		break;
//------------------------------------------------------------------------------------------------------//		
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1B:
		switch(Pwm_Cfg->Prescaler)
		{
			case PWM_PRESCALER_NO:
			sgu8_PWM_CH1B_Prescaler_Mask=0x01;
			sgu16_PWM_CH1B_Prescaler_Value=1;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_8:
			sgu8_PWM_CH1B_Prescaler_Mask=0x02;
			sgu16_PWM_CH1B_Prescaler_Value=8;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_64:
			sgu8_PWM_CH1B_Prescaler_Mask=0x03;
			sgu16_PWM_CH1B_Prescaler_Value=64;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_256:
			sgu8_PWM_CH1B_Prescaler_Mask=0x04;
			sgu16_PWM_CH1B_Prescaler_Value=256;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_1024:
			sgu8_PWM_CH1B_Prescaler_Mask=0x05;
			sgu16_PWM_CH1B_Prescaler_Value=1024;
			break;		
		}
//------------------------------------------------------------------------------------------------------//		
		TCCR1A|=(1<<5); //phase correct non inverting mode
		TCCR1B|=(1<<4);
		PORTD_DIR|=(1<<4);
		break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//		
		case PWM_CH2:
		switch (Pwm_Cfg->Prescaler)
		{
			case PWM_PRESCALER_NO:
			sgu8_PWM_CH2_Prescaler_Mask=0x01;
			sgu16_PWM_CH2_Prescaler_Value=1;
			break;
//------------------------------------------------------------------------------------------------------//
			case PWM_PRESCALER_8:
			sgu8_PWM_CH2_Prescaler_Mask=0x02;
			sgu16_PWM_CH2_Prescaler_Value=8;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_32:
			sgu8_PWM_CH2_Prescaler_Mask=0x03;
			sgu16_PWM_CH2_Prescaler_Value=32;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_64:
			sgu8_PWM_CH2_Prescaler_Mask=0x04;
			sgu16_PWM_CH2_Prescaler_Value=64;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_128:
			sgu8_PWM_CH2_Prescaler_Mask=0x05;
			sgu16_PWM_CH2_Prescaler_Value=128;
			break;
//------------------------------------------------------------------------------------------------------//\			
			case PWM_PRESCALER_256:
			sgu8_PWM_CH2_Prescaler_Mask=0x06;
			sgu16_PWM_CH2_Prescaler_Value=256;
			break;
//------------------------------------------------------------------------------------------------------//			
			case PWM_PRESCALER_1024:
			sgu8_PWM_CH2_Prescaler_Mask=0x07;
			sgu16_PWM_CH2_Prescaler_Value=1024;
			break;
		}
		TCCR2|=(1<<6) | (1<<5); //phase correct, non inverting.
		PORTD_DIR|=(1<<7);
		break;
	}
}

/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: starts the PWM on the dedicated channel with the required duty   */
/*				cycle and frequency                                              */
/*-------------------------------------------------------                        */
/*(IN timer 0) there are only 5 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*--------------------------------------------------------                       */
/*(IN timer 2) there are only 7 available Frequencies:                           */
/*-------------------------------------------------------                        */
/*Frequency (NO-Prescaler) --> 31,372HZ                                          */
/*Frequency (Prescaler 8) --> 3,921HZ                                            */
/*Frequency (Prescaler 32) --> 980HZ                                             */
/*Frequency (Prescaler 64) --> 490HZ                                             */
/*Frequency (Prescaler 128) --> 245HZ                                            */
/*Frequency (Prescaler 256) --> 122HZ                                            */
/*Frequency (Prescaler 1024) --> 31HZ                                            */
/*-------------------------------------------------------                        */
/*((all this calculations are for phase correct mode))                           */
/*all this calculation for F_CPU 16MHz                                           */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Start(uint8 Channel,uint8 Duty,uint32 Frequncy)
{
	switch(Channel)
	{
		case PWM_CH0:
		TCCR0|=sgu8_PWM_CH0_Prescaler_Mask;
		OCR0=Duty*0xFF/100;
		break;
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1A:
		TCCR1B|=sgu8_PWM_CH1A_Prescaler_Mask;
		ICR1=(16000000UL/(2*sgu16_PWM_CH1A_Prescaler_Value*Frequncy));
		OCR1A=Duty*ICR1/100;
		break;
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1B:
		TCCR1B|=sgu8_PWM_CH1B_Prescaler_Mask;
		ICR1=(16000000UL/(2*sgu16_PWM_CH1B_Prescaler_Value*Frequncy));
		OCR1B=Duty*ICR1/100;
		break;	
//------------------------------------------------------------------------------------------------------//
		case PWM_CH2:
		TCCR2|=sgu8_PWM_CH2_Prescaler_Mask;
		OCR2=Duty*0xFF/100;
		break;
	}
}


/*********************************************************************************/
/* Function: Error_State Pwm_Start(uint8_t channel,uint8_t Duty);                */
/* Type: public                                                                  */
/* Input parameters: Channel ID, Duty cycle(0:100)                               */
/* Return type : Error State                                                     */
/*                                                                               */
/* Description: updates the duty cycle and frequency of the dedicated channel    */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Update(uint8 Channel,uint8 Duty,uint32 Frequncy)
{
	if (Channel==PWM_CH0)
	{
		OCR0=Duty*0xFF/100;
	}
//------------------------------------------------------------------------------------------------------//
	else if (Channel==PWM_CH1A)
	{
		ICR1=(uint32)16000000UL/(2*sgu16_PWM_CH1A_Prescaler_Value*Frequncy);
		OCR1A=Duty*ICR1/100;
	}
//------------------------------------------------------------------------------------------------------//
	else if (Channel==PWM_CH1B)
	{
		ICR1=(uint32)16000000UL/(2*sgu16_PWM_CH1B_Prescaler_Value*Frequncy);
		OCR1B=Duty*ICR1/100;
	}
//------------------------------------------------------------------------------------------------------//
	else if (Channel==PWM_CH2)
	{
		OCR2=Duty*0xFF/100;
	}
//------------------------------------------------------------------------------------------------------//	
	else 
	{
		return E_NOK;
	}
	return E_OK;
}


/*********************************************************************************/
/* Function: Error_State Pwm_Stop(uint8_t channel);                              */
/* Type: public                                                                  */
/* Input parameters: channel ID                                                  */
/* Return type : Error state                                                     */
/*                                                                               */
/* Description: responsible of Stopping the PWM by clearing the prescaler		 */
/*				of the corresponding channel                                     */
/*********************************************************************************/

extern ERROR_STATUS Pwm_Stop(uint8 Channel)
{
	switch (Channel)
	{
		case PWM_CH0:
		TCCR0&=~(1<<5);
		break;
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1A:
		TCCR1B&=(1<<7);
		break;
//------------------------------------------------------------------------------------------------------//
		case PWM_CH1B:
		TCCR1B&=(1<<5);
		break;
//------------------------------------------------------------------------------------------------------//
		case PWM_CH2:
		TCCR2&=(1<<5);
		break;
//------------------------------------------------------------------------------------------------------//
		default:
		return E_NOK;
	}
	
	return E_OK;
}

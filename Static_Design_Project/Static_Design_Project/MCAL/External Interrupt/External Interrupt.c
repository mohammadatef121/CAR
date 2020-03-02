/*
 * External_Interrupt.c
 *
 * Created: 12/24/2019 3:59:17 PM
 *  Author: Johnny
 */ 


/********************************************************/
/*					Files Includes						*/
/********************************************************/

#include "interrupts.h"
#include "ExternalInterrupt.h"
#include "registers.h"
#include "DIO.h"


/********************************************************/
/*				CallBack Function prototype				*/
/********************************************************/

static void (*gsa_ExIntCBF[3])(void)={NULL,NULL,NULL};
	

/*
 * Function: ExternInt_Init 
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to structure that contain the initialized data.
 * Outputs: 
 * In Out: 
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Initiate the required external interrupt configuration as it specify
 *	event of interrupt and mode if polling or Interrupt.*/

ERROR_STATUS ExternInt_Init(ExternInt_Cfg_s *ExternIntCfg)
{	
	if (NULL==ExternIntCfg)
	{
		return E_NOK;
	}
	else
	{
		DIO_Cfg_s str_Dio_Ex;
		str_Dio_Ex.GPIO=GPIOB;
		str_Dio_Ex.dir=INPUT;
		str_Dio_Ex.pins=BIT2;
		DIO_init(&str_Dio_Ex);
		GIE();
		switch(ExternIntCfg->ExternInt_No)
		{
			case EXTRN_INT_0:
			gsa_ExIntCBF[0]=ExternIntCfg->ExternInt_CBF_Ptr;
			switch(ExternIntCfg->ExternInt_Event)
			{
				case LOW_LEVEL:
				MCUCR&=~( (1) | (1<<1) );
				break;
//------------------------------------------------------------------------------------------------------//
				case LOGICAL_CHANGE:
				MCUCR|=1;
				MCUCR&=~(1<<1);
				break;
//------------------------------------------------------------------------------------------------------//
				case FALLING_EDGE:
				MCUCR&=~(1);
				MCUCR|=(1<<1);
				break;				
//------------------------------------------------------------------------------------------------------//
				case RISING_EDGE:
				MCUCR|=( (1) | (1<<1) );
				break;
//------------------------------------------------------------------------------------------------------//
				default:
				return E_NOK;
				break;				
			}
			break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
			case EXTRN_INT_1:
			gsa_ExIntCBF[1]=ExternIntCfg->ExternInt_CBF_Ptr;
			switch(ExternIntCfg->ExternInt_Event)
			{
				case LOW_LEVEL:
				MCUCR&=~( (1<<2) | (1<<3) );
				break;
//------------------------------------------------------------------------------------------------------//
				case LOGICAL_CHANGE:
				MCUCR|=(1<<2);
				MCUCR&=~(1<<3);
				break;
//------------------------------------------------------------------------------------------------------//				
				case FALLING_EDGE:
				MCUCR&=~(1<<2);
				MCUCR|=(1<3);
				break;
//------------------------------------------------------------------------------------------------------//
				case RISING_EDGE:
				MCUCR|=( (1<<2) | (1<<3) );
				break;
//------------------------------------------------------------------------------------------------------//
				default:
				return E_NOK;
				break;
			}
			break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
			case EXTRN_INT_2:
			gsa_ExIntCBF[2]=ExternIntCfg->ExternInt_CBF_Ptr;
			switch(ExternIntCfg->ExternInt_Event)
			{
				case FALLING_EDGE:
				MCUCSR&=~(1<<6);
				break;
//------------------------------------------------------------------------------------------------------//
				case RISING_EDGE:
				MCUCSR|=(1<<6);
				break;
//------------------------------------------------------------------------------------------------------//
				default:
				return E_NOK;
				break;
			}		
		} 
	}
	return E_OK;
}


/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt from GICR but to allow the interrupt global interrupt must be set.
 */

ERROR_STATUS ExternInt_Enable(uint8 ExternInt_No)
{
	SREG|=(1<<7);
	switch (ExternInt_No)
	{
		case EXTRN_INT_0:
		GICR|=(1<<6);
		break;
//------------------------------------------------------------------------------------------------------//
		case EXTRN_INT_1:
		GICR|=(1<<7);
		break;
//------------------------------------------------------------------------------------------------------//		
		case EXTRN_INT_2:
		GICR|=(1<<5);
		break;
	}
	return E_OK;	
}


/*
 * Function: ExternInt_SetEvent
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * 	       InterruptEvent -> indicate required event for INT0 and INT1 there are 4 events to check (RISING_EDGE,FALLING_EDGE,LOW_LEVEL,LOGICAL_CHANGE).
							  But for Interrupt 2 there are only Two cases (Rising,Falling)	
 * Outputs: 
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to set event of required external interrupt. 
 * 				note: usually used to poll on the flag.*/

ERROR_STATUS ExternInt_SetEvent(uint8 ExternInt_No,uint8 InterruptEvent)
{
	switch(ExternInt_No)
	{
		case EXTRN_INT_0:
		switch(InterruptEvent)
		{
			case LOW_LEVEL:
			MCUCR&=~( (1) | (1<<1) );
			break;
//------------------------------------------------------------------------------------------------------//
			case LOGICAL_CHANGE:
			MCUCR|=1;
			MCUCR&=~(1<<1);
			break;
//------------------------------------------------------------------------------------------------------//
			case FALLING_EDGE:
			MCUCR&=~(1);
			MCUCR|=(1<<1);
			break;
//------------------------------------------------------------------------------------------------------//
			case RISING_EDGE:
			MCUCR|=( (1) | (1<<1) );
			break;
//------------------------------------------------------------------------------------------------------//
			default:
			return E_NOK;
			break;
		}
		break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
		case EXTRN_INT_1:
		switch(InterruptEvent)
		{
			case LOW_LEVEL:
			MCUCR&=~( (1<<2) | (1<<3) );
			break;
//------------------------------------------------------------------------------------------------------//				
			case LOGICAL_CHANGE:
			MCUCR|=(1<<2);
			MCUCR&=~(1<<3);
			break;
//------------------------------------------------------------------------------------------------------//				
			case FALLING_EDGE:
			MCUCR&=~(1<<2);
			MCUCR|=(1<<3);
			break;
//------------------------------------------------------------------------------------------------------//
			case RISING_EDGE:
			MCUCR|=( (1<<2) | (1<<3) );
			break;
//------------------------------------------------------------------------------------------------------//
			default:
			return E_NOK;
			break;
		}
		break;
//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------//
		case EXTRN_INT_2:
		switch(InterruptEvent)
		{
			case FALLING_EDGE:
			MCUCSR&=~(1<<6);
			break;
//------------------------------------------------------------------------------------------------------//				
			case RISING_EDGE:
			MCUCSR|=(1<<6);
			break;
//------------------------------------------------------------------------------------------------------//				
			default:
			return E_NOK;
			break;
		}	
	}
	return E_OK;
}

/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status. 
 * 				note: usually used to poll on the flag.
 */

ERROR_STATUS ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status)
{
	switch (ExternInt_No)
	{
		case EXTRN_INT_0:
		*Status=( GIFR & (1<<6) ) / GIFR;
		break;
//------------------------------------------------------------------------------------------------------//
		case EXTRN_INT_1:
		*Status=( GIFR & (1<<7) ) / GIFR;
		break;
//------------------------------------------------------------------------------------------------------//		
		case EXTRN_INT_2:
		*Status=( GIFR & (1<<5) ) / GIFR;
		break;
//------------------------------------------------------------------------------------------------------//		
		default:
		return E_NOK;
		break;				
	}
	return E_OK;
}


/* Function: ExternInt_Disable
* Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
* Outputs:
* In Out:
* Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
* Description: Disable the required external interrupt.
*/

ERROR_STATUS ExternInt_Disable(uint8 ExternInt_No)
{
	switch (ExternInt_No)
	{
		case EXTRN_INT_0:
		GICR&=~(1<<6);
		break;
//------------------------------------------------------------------------------------------------------//		
		case EXTRN_INT_1:
		GICR&=~(1<<7);
		break;
//------------------------------------------------------------------------------------------------------//		
		case EXTRN_INT_2:
		GICR&=~(1<<5);
		break;
//------------------------------------------------------------------------------------------------------//\		
		default:
		return E_NOK;
		break;
	}
	return E_OK;
}



/**********************************************/
/*            CallBack Functions              */
/*********************************************/


ISR (Ext_Inter_Req0_Vect)
{
	gsa_ExIntCBF[0]();
}

ISR (Ext_Inter_Req1_Vect)
{
	gsa_ExIntCBF[1]();
}

ISR (Ext_Inter_Req2_Vect)
{
	(*gsa_ExIntCBF[2])();
}
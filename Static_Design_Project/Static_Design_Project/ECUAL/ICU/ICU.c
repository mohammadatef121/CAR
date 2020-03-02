/*
 * ICU.c
 *
 * Created: 12/26/2019 4:44:28 PM
 *  Author: Johnny
 */ 

#include "DIO.h"
#include "ICU.h"
#include "ExternalInterrupt.h"
#include "Timer.h"


/********************************************************/
/*					 Macros        						*/
/********************************************************/

#define FromTicksToMicroSeconds 4
#define TCNT2MaxValue 256


/********************************************************/
/*					Variables    						*/
/********************************************************/

static volatile uint16 sgu8_NumberOfTicks=0;
static volatile uint32 sgu32_TotalNumberOfTicks=0;
static volatile uint32 sgu32_TimeInMicroSeconds=0;
static volatile uint8  sgu32_NumberOfOverFlows=0;
static volatile uint8  sgu8_Polling = 0;
 
 /********************************************************/
 /*					Structure    						*/
 /********************************************************/

ExternInt_Cfg_s ICU_Ex_Int_s = {0};
Timer_cfg_s ICU_Timer_Init_s = {0};


/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/


ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	if(Icu_Cfg==NULL)
	{
		return E_NOK;
	}
	else 
	{
		ICU_Ex_Int_s.ExternInt_CBF_Ptr = Icu_EdgeToEdge_Callback_Func;
		ICU_Ex_Int_s.ExternInt_Event=RISING_EDGE;
		ICU_Ex_Int_s.ExternInt_No=EXTRN_INT_2;
		ExternInt_Init(&ICU_Ex_Int_s);
//------------------------------------------------------------------------------------------------------//
		ICU_Timer_Init_s.Timer_Cbk_ptr = Icu_TimerOverFlows_Callback_Func;
		ICU_Timer_Init_s.Timer_CH_NO=TIMER_CH2;
		ICU_Timer_Init_s.Timer_Mode=TIMER_MODE;
		ICU_Timer_Init_s.Timer_Prescaler = TIMER_PRESCALER_64;
		ICU_Timer_Init_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
		Timer_Init(&ICU_Timer_Init_s);
	}
	return E_OK;
}

/***************************************************************************
 * Function		: Icu_RiseToFall										   *
 * Input		: ICU_Ch_No : external interrupt number					   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from rising edge to falling edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK  : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between the rising and the falling   *
 * 				  edges												 	   *
 ***************************************************************************/
ERROR_STATUS Icu_RiseToFall(uint8 ICU_Ch_No,uint32 * Icu_Time)
{
	if (Icu_Time==NULL)
	{
		return E_NOK;
	}
	else 
	{
		ExternInt_Enable(ICU_CH2);
		ExternInt_SetEvent(ICU_CH2, RISING_EDGE);
		while(sgu8_Polling != 1);
		/**(freq/time)* Duty*/
		sgu32_TotalNumberOfTicks=(sgu8_NumberOfTicks + (sgu32_NumberOfOverFlows * TCNT2MaxValue));
		sgu32_TimeInMicroSeconds=sgu32_TotalNumberOfTicks*FromTicksToMicroSeconds;
		*Icu_Time =sgu32_TimeInMicroSeconds;
		sgu8_Polling = 0;
		sgu32_NumberOfOverFlows = 0;		
	}
	return E_OK;
}


void Icu_TimerOverFlows_Callback_Func (void)
{
	sgu32_NumberOfOverFlows++;
}

void Icu_EdgeToEdge_Callback_Func (void)
{
	uint8 EdgeStatus;
	DIO_Read(GPIOB, PIN2, &EdgeStatus);
/********************************Trigger ICU falling age****************************/	
	if (EdgeStatus != 0)
	{
		Timer_Start(TIMER_CH2,256);
		ExternInt_SetEvent(ICU_Ex_Int_s.ExternInt_No, FALLING_EDGE);
	}
//------------------------------------------------------------------------------------------------------//	
	else if (EdgeStatus == 0)
	{
		ExternInt_SetEvent(ICU_Ex_Int_s.ExternInt_No, RISING_EDGE);
		sgu8_Polling = 1;
		Timer_GetValue(TIMER_CH2, &sgu8_NumberOfTicks);
		Timer_Stop(TIMER_CH2);
	}
}
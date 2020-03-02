/*
 * Us.c
 *
 * Created: 12/25/2019 1:06:17 PM
 *  Author: Ahmed
 */ 


/********************************************************/
/*					Files Includes						*/
/********************************************************/

#include "DIO.h"
#include "ICU.h"


/********************************************************/
/*					Macros								*/
/********************************************************/

#define FromMicroSecondsToCm 58
#define TriggerPort GPIOB
#define TriggerBit BIT1

/************************************************************************/
/*				   functions' prototypes	                            */
/************************************************************************/

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/



ERROR_STATUS Us_Init(void)
{
	//initiate the DIO to set the direction of the trigger pit
	DIO_Cfg_s Dio_Us_s ;
	Dio_Us_s.dir=OUTPUT;
	Dio_Us_s.GPIO=TriggerPort;
	Dio_Us_s.pins=TriggerBit;
	DIO_init(&Dio_Us_s);

	Icu_cfg_s Icu_Us_s;
	Icu_Us_s.ICU_Ch_No=ICU_CH2;
	Icu_Us_s.ICU_Ch_Timer=ICU_TIMER_CH2;
	Icu_Init(&Icu_Us_s);	
	return E_OK;
}




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void)
{
	DIO_Write(GPIOB,BIT1,HIGH);

	for (uint8 Delay=0;Delay<40;Delay++)
	{
		Delay++;
	}
	DIO_Write(GPIOB,BIT1,LOW);
	return E_OK;
}



/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/


ERROR_STATUS Us_GetDistance(uint32 *Distance)
{
	static uint32 su32Total_Time=0;
	Icu_RiseToFall(ICU_CH2,&su32Total_Time);
	*(Distance)=su32Total_Time/FromMicroSecondsToCm;
	return E_OK;
}


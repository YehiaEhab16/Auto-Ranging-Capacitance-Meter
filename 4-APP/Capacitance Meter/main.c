/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "../../5-LIB/STD_TYPES.h"
#include "../../5-LIB/BIT_MATH.h"
#include "../../1-MCAL/2-PORT/PORT_interface.h"
#include "../../1-MCAL/1-DIO/DIO_interface.h"
#include "../../1-MCAL/3-EXTI/EXTI_interface.h"
#include "../../1-MCAL/6-TIMERS/TIMERS_interface.h"
#include "../../1-MCAL/5-ADC/ADC_interface.h"
#include "../../1-MCAL/4-GIE/GIE_interface.h"

#include "../../2-HAL/1-CLCD/CLCD_interface.h"
#include "../../2-HAL/2-LED/LED_interface.h"
#include "../../2-HAL/3-SW/SW_interface.h"
#include "../../2-HAL/4-BUZZ/BUZZ_interface.h"

#include "Cap.h"

void ChargeTime (void);

u32 Global_ChargeCounter =0  ;

Timer_t ChargeCounter = {NORMAL, DIVIDE_BY_1, NORMAL};

u8 Global_u8StateRange =  RES_220;
void main (void)
{
	u16 Local_u32ReadAnalog = 0 ;
	u32 Local_u32TimeRead =0 ;
	u32 Local_u32Capacity =0 ;
	u8 Local_u8Unit = Farad;

	PORT_voidInit();
	CLCD_voidInit();

	ADC_voidInit();

	Timer1_voidInit(&ChargeCounter);
	Timer_u8SetCallback(TIMER1_PRELOAD, &ChargeTime);

	GIE_voidEnableGlobal();

	CLCD_voidSendString("Welcome To Capacitance Meter");



	while (1)
	{
		if (Global_u8StateRange == RES_220)
		{
			PORT_u8ModifyPin(RES_220_PORT,RES_220_PIN,OUTPUT);
			DIO_u8SetPinValue(RES_220_PORT,RES_220_PIN,DIO_u8PIN_HIGH);

			Global_ChargeCounter = 0 ;
			Timer_voidSetTimerValue (TIMER1_PRELOAD, 0 );

			ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);

			while (Local_u32ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
			{
				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);
			}

			Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER1)+ Global_ChargeCounter*65536;

			if (Local_u32TimeRead < 1000)
			{
				DIO_u8SetPinValue(RES_220_PORT,RES_220_PIN,DIO_u8PIN_LOW);
				delay(10);

				PORT_u8ModifyPin(RES_220_PORT,RES_220_PIN,INPUT);

				Global_u8StateRange = RES_1K ;
			}
			else
			{
				Local_u32Capacity = Local_u32TimeRead / 220 ;
				Local_u8Unit = Farad ;
				//Display Capacitance and unit


			}

		}
		else if (Global_u8StateRange == RES_1K)
		{
			PORT_u8ModifyPin(RES_1K_PORT,RES_1K_PIN,OUTPUT);
			DIO_u8SetPinValue(RES_1K_PORT,RES_1K_PIN,DIO_u8PIN_HIGH);

			Global_ChargeCounter = 0 ;
			Timer_voidSetTimerValue (TIMER1_PRELOAD, 0 );

			ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);

			while (Local_u32ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
			{
				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);
			}
			Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER1)+ Global_ChargeCounter*65536;


			if (Local_u32TimeRead < 500)
			{

				DIO_u8SetPinValue(RES_1K_PORT,RES_1K_PIN,DIO_u8PIN_LOW);
				delay(10);

				PORT_u8ModifyPin(RES_1K_PORT,RES_1K_PIN,INPUT);

				Global_u8StateRange = RES_10K ;


			}
			else
			{
				Local_u32Capacity = Local_u32TimeRead / 1000 ;

				Local_u8Unit = MileFarad ;

				Global_u8StateRange = RES_220;
				//Display Capacitance and unit


			}

		}
		else if (Global_u8StateRange == RES_10K)
		{
			PORT_u8ModifyPin(RES_10K_PORT,RES_10K_PIN,OUTPUT);
			DIO_u8SetPinValue(RES_10K_PORT,RES_10K_PIN,DIO_u8PIN_HIGH);
			Global_ChargeCounter = 0 ;
			Timer_voidSetTimerValue (TIMER1_PRELOAD, 0 );

			ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);

			while (Local_u32ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
			{
				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u32ReadAnalog);
			}

			Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER1)+ Global_ChargeCounter*65536;

			if (Local_u32TimeRead < 250)
			{
				//nothing can not measure this range
			}
			else
			{
				Local_u32Capacity = Local_u32TimeRead / 10000 ;

				Local_u8Unit = MicroFarad ;
				Global_u8StateRange = RES_220;

				//Display Capacitance and unit

			}

		}
		else
		{

			//nothing
		}


	}

}
void ChargeTime (void)
{
	Global_ChargeCounter++;

}

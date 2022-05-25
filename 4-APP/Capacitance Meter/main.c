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

#include <util/delay.h>

#include "Cap.h"

void ChargeTime(void);
void ChangeMeter(void);

u8 Global_u8StateRange =  RES_10, Global_u8MeterFlag=CAP_METER, Global_u8BuzzerFlag=0;
u32 Global_u32ChargeCounter = 0;

Timer_t Global_Timer_tChargeCounter = {NORMAL, DIVIDE_BY_1, NORMAL};
LED_t Global_LED_tExternal = {LED_PORTB, LED_PIN0, LED_u8ACTIVE_HIGH};
LED_t Global_LED_tInternal = {LED_PORTB, LED_PIN1, LED_u8ACTIVE_HIGH};

void main (void)
{
	u8 Local_u8Unit = Farad;
	u16 Local_u16ReadAnalog = 0;
	u32 Local_u32TimeRead = 0;
	u32 Local_u32Capacity = 0;

	PORT_voidInit();
	CLCD_voidInit();

	ADC_voidInit();

	Timer0_voidInit(&Global_Timer_tChargeCounter);
	Timer_u8SetCallback(TIMER0_PRELOAD, &ChargeTime);

	//EXTI_u8EnableInterrupt(EXTI_INT1);
	//EXTI_u8SetCallBack(&ChangeMeter,EXTI_INT1);

	GIE_voidEnableGlobal();

	LED_voidLedOff(&Global_LED_tExternal);
	LED_voidLedOn(&Global_LED_tInternal);

	CLCD_voidSendString("Welcome To Capacitance and Ohm Meter");
	_delay_ms(WELCOME_TIME);

	LED_voidLedOn(&Global_LED_tExternal);
	LED_voidLedOff(&Global_LED_tInternal);

	while (1)
	{
		if(Global_u8BuzzerFlag==1)
		{
			BUZZ_voidBuzzerOn();
			_delay_ms(BUZZER_TONE);
			BUZZ_voidBuzzerOff();
			Global_u8BuzzerFlag=0;
		}
		if(Global_u8MeterFlag==CAP_METER)
		{
			CLCD_voidSendString("  Capacitance  ");
			CLCD_voidGotoXY(0,1);
			CLCD_voidSendString("Cap:");
		}
		else
		{
			CLCD_voidSendString("     Ohm     ");
			CLCD_voidGotoXY(0,1);
			CLCD_voidSendString("Res:");
		}

	}

}
void ChargeTime (void)
{
	Global_u32ChargeCounter++;
}

void ChangeMeter(void)
{
	CLCD_voidClearDisplay();
	Global_u8BuzzerFlag = 1;
	Global_u8MeterFlag = !Global_u8MeterFlag;
}

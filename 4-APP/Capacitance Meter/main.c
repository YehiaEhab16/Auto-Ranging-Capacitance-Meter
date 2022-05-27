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
#include "../../2-HAL/5-MUX/MUX_interface.h"

#include <util/delay.h>

#include "Cap.h"

void ChargeTime(void);
void ChangeMeter(void);
u16 Range_MAP(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum);

u8 Globl_u8State = RES_50ohm, Global_u8StateRange =  RES_10,Global_u8Digit,Global_u8UnsigNum;
u8 Global_u8MeterFlag=CAP_METER, Global_u8BuzzerFlag=0,Global_u8Dispaly=DISP;
u32 Global_u32ChargeCounter = 0;

Timer_t Global_Timer_tChargeCounter = {NORMAL, DIVIDE_BY_1, NORMAL};
LED_t Global_LED_tExternal = {LED_PORTB, LED_PIN0, LED_u8ACTIVE_HIGH};
LED_t Global_LED_tInternal = {LED_PORTB, LED_PIN1, LED_u8ACTIVE_HIGH};

void main (void)
{
	u8 Local_u8Unit = Farad,Local_u8Value;
	u16 Local_u16ReadAnalog = 0,Local_u16Voltage=0;
	u32 Local_u32TimeRead = 0;
	u32 Local_u32Capacity = 0;
	f32 Local_f32Resistance;

	PORT_voidInit();
	CLCD_voidInit();

	ADC_voidInit();

	Timer0_voidInit(&Global_Timer_tChargeCounter);
	Timer_u8SetCallback(TIMER0_PRELOAD, &ChargeTime);

	EXTI_voidINT1Init();
	EXTI_u8SetCallBack(&ChangeMeter,EXTI_INT1);

	MUX_voidSelectPin(0);

	GIE_voidEnableGlobal();

	LED_voidLedOff(&Global_LED_tExternal);
	LED_voidLedOn(&Global_LED_tInternal);

	CLCD_voidSendString("Welcome To Capacitance and Ohm Meter");
	_delay_ms(WELCOME_TIME);
	CLCD_voidClearDisplay();
	DIO_u8GetPinValue(DIO_u8PORTD,DIO_u8PIN3,&Local_u8Value);
	if(Local_u8Value==DIO_u8PIN_HIGH)
		Global_u8MeterFlag=CAP_METER;
	else
		Global_u8MeterFlag=OHM_METER;

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
			if(Global_u8Dispaly==DISP)
			{
				CLCD_voidSendString("  Capacitance  ");
				CLCD_voidGotoXY(0,1);
				CLCD_voidSendString("Cap:");
				Global_u8Dispaly=NO_DISP;
			}
			if (Global_u8StateRange == RES_10)
			{
				PORT_u8ModifyPin(RES_10_PORT,RES_10_PIN,OUTPUT);
				DIO_u8SetPinValue(RES_10_PORT,RES_10_PIN,DIO_u8PIN_HIGH);

				Global_u32ChargeCounter = 0 ;
				Timer_voidSetTimerValue (TIMER0_PRELOAD, 0);

				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				while (Local_u16ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
					ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER0)+ Global_u32ChargeCounter*65536;

				if (Local_u32TimeRead < 1000)
				{
					DIO_u8SetPinValue(RES_10_PORT,RES_10_PIN,DIO_u8PIN_LOW);
					_delay_ms(10);
					PORT_u8ModifyPin(RES_10_PORT,RES_10_PIN,INPUT);
					Global_u8StateRange = RES_10K ;
				}
				else
				{
					Local_u32Capacity = Local_u32TimeRead / 10 ;
					Local_u8Unit = Farad ;
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_u32Capacity);
					CLCD_voidSendString("F          ");
				}

			}
			else if (Global_u8StateRange == RES_10K)
			{
				PORT_u8ModifyPin(RES_10K_PORT,RES_10K_PIN,OUTPUT);
				DIO_u8SetPinValue(RES_10K_PORT,RES_10K_PIN,DIO_u8PIN_HIGH);

				Global_u32ChargeCounter = 0 ;
				Timer_voidSetTimerValue (TIMER0_PRELOAD, 0 );

				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				while (Local_u16ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
					ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER0)+ Global_u32ChargeCounter*65536;

				if (Local_u32TimeRead < 500)
				{
					DIO_u8SetPinValue(RES_10K_PORT,RES_10K_PIN,DIO_u8PIN_LOW);
					_delay_ms(10);
					PORT_u8ModifyPin(RES_10K_PORT,RES_10K_PIN,INPUT);
					Global_u8StateRange = RES_10M ;
				}
				else
				{
					Local_u32Capacity = Local_u32TimeRead / 10000 ;
					Local_u8Unit = MileFarad ;
					Global_u8StateRange = RES_10;
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_u32Capacity);
					CLCD_voidSendString("mF          ");
				}

			}
			else if (Global_u8StateRange == RES_10M)
			{
				PORT_u8ModifyPin(RES_10M_PORT,RES_10M_PIN,OUTPUT);
				DIO_u8SetPinValue(RES_10M_PORT,RES_10M_PIN,DIO_u8PIN_HIGH);
				Global_u32ChargeCounter = 0 ;
				Timer_voidSetTimerValue (TIMER0_PRELOAD, 0 );

				ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				while (Local_u16ReadAnalog <CAPCITANCE_VALUE_63_PERCANTAGE)
					ADC_u8StartConversionSynch(CAPACITANCE_VOLTAGE_PIN, &Local_u16ReadAnalog);

				Local_u32TimeRead = Timer_u16ReadTimerValue(TIMER0)+ Global_u32ChargeCounter*65536;
				if (Local_u32TimeRead < 250)
				{
					//nothing can not measure this range
				}
				else
				{
					Local_u32Capacity = Local_u32TimeRead / 10000000 ;
					Local_u8Unit = MicroFarad ;
					Global_u8StateRange = RES_10;
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_u32Capacity);
					CLCD_voidSendString("uF          ");
				}
			}
		}
		else if(Global_u8MeterFlag==OHM_METER)
		{
			if(Global_u8Dispaly==DISP)
			{
				CLCD_voidSendString("      Ohm      ");
				CLCD_voidGotoXY(0,1);
				CLCD_voidSendString("Res:");
				Global_u8Dispaly=NO_DISP;
			}
			ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
			Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);

			if (Local_u16Voltage >4500)
			{
				CLCD_voidGotoXY(4,1);
				CLCD_voidSendString("OC");
			}
			else if (Globl_u8State == RES_50ohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);

				Local_f32Resistance = ((f32)(Local_u16Voltage * 50UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=100 && Local_u16Voltage<=3322 )
				{

					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)(Local_f32Resistance * 3.7));
					CLCD_voidSendString("Ohm        ");

				}
				else
				{
					MUX_voidSelectPin(1);
					Globl_u8State = RES_100ohm;
				}

			}

			else if (Globl_u8State == RES_100ohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 100UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2450 && Local_u16Voltage<4500 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("Ohm        ");
				}
				else
				{
					MUX_voidSelectPin(2);
					Globl_u8State = RES_1000ohm;
				}

			}
			else if (Globl_u8State == RES_1000ohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 1000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;
				Global_u8UnsigNum = (u32)((Local_f32Resistance)*100);
				Global_u8Digit = Global_u8UnsigNum - ((u32)(Global_u8UnsigNum/100000))*100 ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("KOhm        ");
				}
				else
				{
					MUX_voidSelectPin(3);
					Globl_u8State = RES_10kohm;
				}
			}
			else if (Globl_u8State == RES_10kohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 10000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("KOhm        ");
				}
				else
				{
					MUX_voidSelectPin(4);
					Globl_u8State = RES_100kohm;
				}
			}
			else if (Globl_u8State == RES_100kohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 100000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("KOhm        ");

				}
				else
				{
					MUX_voidSelectPin(5);
					Globl_u8State = RES_1Mohm;
				}
			}
			else if (Globl_u8State == RES_1Mohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 1000000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<4167 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("MOhm        ");

				}
				else
				{
					MUX_voidSelectPin(6);
					Globl_u8State = RES_5Mohm;
				}

			}
			else if (Globl_u8State == RES_5Mohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);

				Local_f32Resistance = ((Local_u16Voltage * 5000000UL) / ( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<3333 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("MOhm        ");
				}
				else
				{
					MUX_voidSelectPin(7);
					Globl_u8State = RES_10Mohm;
				}
			}
			else if (Globl_u8State == RES_10Mohm)
			{
				ADC_u8StartConversionSynch(5,&Local_u16ReadAnalog);
				Local_u16Voltage = Range_MAP(Local_u16ReadAnalog, 0 , 255, 0, 5000);
				Local_f32Resistance = ((f32)(Local_u16Voltage * 10000000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

				if (Local_u16Voltage>=2400 && Local_u16Voltage<1666 )
				{
					CLCD_voidGotoXY(4,1);
					CLCD_voidSendNumber((u16)Local_f32Resistance);
					CLCD_voidSendString("MOhm        ");
				}
				else
				{
					MUX_voidSelectPin(0);
					Globl_u8State = RES_50ohm ;
				}
			}
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
	Global_u8Dispaly=DISP;
	Global_u8MeterFlag = !Global_u8MeterFlag;
}

u16 Range_MAP(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum)
{
	u16 Local_u16OutputNumber = (((f32)(Copy_u16OutputMaximum - Copy_u16OutputMinimum) / (f32)(Copy_u16InputMaximum - Copy_u16InputMinimum))*(f32)(Copy_u16InputNumber - Copy_u16InputMinimum)) + Copy_u16OutputMinimum;

	return Local_u16OutputNumber;
}




/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include <util/delay.h>
#include "../../5-LIB/STD_TYPES.h"
#include "../../5-LIB/BIT_MATH.h"
#include "../../1-MCAL/2-PORT/PORT_interface.h"
#include "../../1-MCAL/1-DIO/DIO_interface.h"
#include "../../1-MCAL/3-EXTI/EXTI_interface.h"
#include "../../1-MCAL/5-ADC/ADC_interface.h"
#include "../../1-MCAL/4-GIE/GIE_interface.h"

#include "../../2-HAL/1-CLCD/CLCD_interface.h"
#include "../../2-HAL/2-LED/LED_interface.h"
#include "../../2-HAL/3-SW/SW_interface.h"
#include "../../2-HAL/4-BUZZ/BUZZ_interface.h"

#include "Cap.h"

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum);

u8 Globl_u8State = RES_1000ohm ;
void main(void)
{


	u16 Local_u16Analog, Local_u16Voltage;
	f32 Local_f32Resistance ;

	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();


	while(1)
	{

		ADC_u8StartConversionSynch(5,&Local_u16Analog);
		Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

		if (Local_u16Voltage == 5000)
		{

			CLCD_voidClearDisplay();
			CLCD_voidSendString("No Connection");
		}

		else if (Globl_u8State == RES_50ohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 50UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=100 && Local_u16Voltage<=3322 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)Local_f32Resistance);
				CLCD_voidSendString("   Ohm");

			}
			else
			{
				Globl_u8State = RES_100ohm;
			}
			_delay_ms(100);

		}

		else if (Globl_u8State == RES_100ohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 100UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2450 && Local_u16Voltage<4500 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)Local_f32Resistance);
				CLCD_voidSendString("  Ohm");

			}
			else
			{
				Globl_u8State = RES_1000ohm;
			}
			_delay_ms(100);

		}

		else if (Globl_u8State == RES_1000ohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 1000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
			{


				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u32)(Local_f32Resistance/950));
				CLCD_voidSendString("  KOhm");

			}
			else
			{
				Globl_u8State = RES_10kohm;
			}
			_delay_ms(100);

		}
		else if (Globl_u8State == RES_10kohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 10000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;



			if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)(Local_f32Resistance/1000));
				CLCD_voidSendString("   kOhm");

			}
			else
			{
				Globl_u8State = RES_100kohm;
			}
			_delay_ms(100);

		}
		else if (Globl_u8State == RES_100kohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 100000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2400 && Local_u16Voltage<4500 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber(Local_f32Resistance/1000);
				CLCD_voidSendString("  kOhm");

			}
			else
			{
				Globl_u8State = RES_1Mohm;
			}
			_delay_ms(100);


		}
		else if (Globl_u8State == RES_1Mohm)
		{

			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 1000000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2400 && Local_u16Voltage<4167 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)(Local_f32Resistance/1000000));
				CLCD_voidSendString("   MOhm");

			}
			else
			{
				Globl_u8State = RES_5Mohm;
			}
			_delay_ms(100);

		}
		else if (Globl_u8State == RES_5Mohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((Local_u16Voltage * 5000000UL) / ( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2400 && Local_u16Voltage<3333 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)(Local_f32Resistance/1000000));
				CLCD_voidSendString("   MOhm");

			}
			else
			{
				Globl_u8State = RES_10Mohm;
			}
			_delay_ms(100);

		}
		else if (Globl_u8State == RES_10Mohm)
		{
			ADC_u8StartConversionSynch(5,&Local_u16Analog);
			Local_u16Voltage = mapping(Local_u16Analog, 0 , 255, 0, 5000);

			Local_f32Resistance = ((f32)(Local_u16Voltage * 10000000UL) / (f32)( 5000UL-(u32)Local_u16Voltage)) ;

			if (Local_u16Voltage>=2400 && Local_u16Voltage<1666 )
			{

				CLCD_voidClearDisplay();
				CLCD_voidSendString("Res:");
				CLCD_voidSendNumber((u16)(Local_f32Resistance/1000000));
				CLCD_voidSendString("   MOhm");

			}
			else
			{
				//nothing
			}
			_delay_ms(100);

		}


		_delay_ms(50);
	}
}

u16 mapping(u16 Copy_u16InputNumber, u16 Copy_u16InputMinimum, u16 Copy_u16InputMaximum, u16 Copy_u16OutputMinimum, u16 Copy_u16OutputMaximum)
{
	u16 Local_u16OutputNumber = (((f32)(Copy_u16OutputMaximum - Copy_u16OutputMinimum) / (f32)(Copy_u16InputMaximum - Copy_u16InputMinimum))*(f32)(Copy_u16InputNumber - Copy_u16InputMinimum)) + Copy_u16OutputMinimum;

	return Local_u16OutputNumber;
}


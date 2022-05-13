/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "TIMERS_interface.h"
#include "ADC_interface.h"



#define R1               100000
#define R2               10000
#define R3               1000

##define R_D          	 DIO_u8PIN0

u32 Tau;
f64 Capacitance;
u8 Copy_CAP8Discharging;
u8 Copy_CAP8RangeLow;
u8 Copy_CAP8RangeMedium;
u8 Copy_CAP8RangeHigh;


void main(void)
{
	PORT_voidInit();
	ADC_voidInit();
	CLCD_voidInit();
	CLCD_voidClearDisplay();
	
	

	
	while (1){
		DIO_u8GetPinValue(DIO_u8PORTA , DIO_u8PIN1, &Copy_CAP8RangeLow);
		DIO_u8GetPinValue(DIO_u8PORTA , DIO_u8PIN2, &Copy_CAP8RangeMedium);
		DIO_u8GetPinValue(DIO_u8PORTA , DIO_u8PIN3, &Copy_CAP8RangeHigh);
		
		

		if (Copy_CAP8RangeLow == DIO_u8PIN_HIGH){
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_HIGH);
			DIO_u8GetPinValue(DIO_u8PORTA, R_D, Copy_CAP8Discharging);

			

		}
		else if (Copy_CAP8RangeMedium == DIO_u8PIN_HIGH){
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_HIGH);
			DIO_u8GetPinValue(DIO_u8PORTA, R_D, Copy_CAP8Discharging);


		}

		else if (Copy_CAP8RangeHigh == DIO_u8PIN_HIGH){
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_HIGH);
			IO_u8GetPinValue(DIO_u8PORTA, R_D, Copy_CAP8Discharging);


		}
		
		else{
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN1, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN2, DIO_u8PIN_LOW);
			DIO_u8SetPinValue(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_LOW);

		}
		
		
	}
	
}
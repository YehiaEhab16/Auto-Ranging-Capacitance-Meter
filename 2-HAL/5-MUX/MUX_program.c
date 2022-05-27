/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: HAL	     		************/
/************		SWC: MUX 				************/
/************		Version: 1.00	 		************/
/************		Date: 25-5-2022 		************/
/*******************************************************/
/*******************************************************/

#include "..\..\5-LIB\STD_TYPES.h"

#include <util/delay.h>

#include "..\..\1-MCAL\1-DIO\DIO_interface.h"

#include "MUX_config.h"
#include "MUX_interface.h"
#include "MUX_private.h"

void MUX_voidSelectPin(u8 Copy_u8Pin)
{
	switch(Copy_u8Pin)
	{
		case 0:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,0);
			   break;
		case 1:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,0);
			   break;
		case 2:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,0);
			   break;
		case 3:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,0);
			   break;
		case 4:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,1);
			   break;
		case 5:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,1);
			   break;
		case 6:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,0);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,1);
			   break;
		case 7:DIO_u8SetPinValue(MUX_PORT,MUX_PIN_A,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_B,1);
			   DIO_u8SetPinValue(MUX_PORT,MUX_PIN_C,1);
			   break;		
	}
}
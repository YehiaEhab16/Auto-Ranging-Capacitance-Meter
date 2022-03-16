/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: HAL	     		************/
/************		SWC: SW 				************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "..\..\5-LIB\STD_TYPES.h"

#include "..\..\1-MCAL\1-DIO\DIO_interface.h"
#include <delay.h>

#include "SW_config.h"
#include "SW_interface.h"
#include "SW_private.h"


u8 SW_u8ReadSwicth(SW_t* Copy_pu8Struct)
{
	u8 Local_u8SwicthValue, Local_u8Value;
	if(Copy_pu8Struct->SW_u8Connection==SW_u8PULL_UP)
	{
		DIO_u8SetPinValue(Copy_pu8Struct->SW_u8Port, Copy_pu8Struct->SW_u8Pin, DIO_u8PIN_HIGH);
		DIO_u8GetPinValue(Copy_pu8Struct->SW_u8Port, Copy_pu8Struct->SW_u8Pin, &Local_u8Value);
		if(Local_u8Value==0)
			Local_u8SwicthValue = PRESSED;
		else
			Local_u8SwicthValue = NOT_PRESSED;
	}
	else
	{
		DIO_u8SetPinValue(Copy_pu8Struct->SW_u8Port, Copy_pu8Struct->SW_u8Pin, DIO_u8PIN_LOW);
		DIO_u8GetPinValue(Copy_pu8Struct->SW_u8Port, Copy_pu8Struct->SW_u8Pin, &Local_u8Value);
		Local_u8SwicthValue = Local_u8Value;
	}
	delay_ms(Copy_pu8Struct->SW_u8DebounceTime);
	return Local_u8SwicthValue;
}

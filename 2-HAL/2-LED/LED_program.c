/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: HAL	     		************/
/************		SWC: LED 				************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "..\..\5-LIB\STD_TYPES.h"
#include "..\..\5-LIB\BIT_MATH.h"

#include "..\..\1-MCAL\1-DIO\DIO_interface.h"

#include "LED_config.h"
#include "LED_interface.h"
#include "LED_private.h"

void LED_voidLedOn(LED_t* Copy_pu8StructLed)
{
	if(Copy_pu8StructLed->LED_u8Connection == LED_u8ACTIVE_HIGH)
		DIO_u8SetPinValue(Copy_pu8StructLed->LED_u8Port, Copy_pu8StructLed->LED_u8Pin, DIO_u8PIN_HIGH);
	else
		DIO_u8SetPinValue(Copy_pu8StructLed->LED_u8Port, Copy_pu8StructLed->LED_u8Pin, DIO_u8PIN_LOW);
}
void LED_voidLedOff(LED_t* Copy_pu8StructLed)
{
	if(Copy_pu8StructLed->LED_u8Connection == LED_u8ACTIVE_HIGH)
		DIO_u8SetPinValue(Copy_pu8StructLed->LED_u8Port, Copy_pu8StructLed->LED_u8Pin, DIO_u8PIN_LOW);
	else
		DIO_u8SetPinValue(Copy_pu8StructLed->LED_u8Port, Copy_pu8StructLed->LED_u8Pin, DIO_u8PIN_HIGH);
}
void LED_voidLedToggle(LED_t* Copy_pu8StructLed)
{
	DIO_u8TogglePinValue(Copy_pu8StructLed->LED_u8Port, Copy_pu8StructLed->LED_u8Pin);
}

void LED_voidLedPortValue(LED_t* Copy_pu8StructLed, u8 Copy_u8Value)
{
	if(Copy_pu8StructLed->LED_u8Connection == LED_u8ACTIVE_HIGH)
		DIO_u8SetPortValue(Copy_pu8StructLed->LED_u8Port, Copy_u8Value);
	else
		DIO_u8SetPortValue(Copy_pu8StructLed->LED_u8Port, ~(Copy_u8Value));
}


/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "LED_interface.h"

void main(void)
{
	PORT_voidInit();
	
	typedef struct My_Struct1
	{
		LED_PORTA;
		LED_PIN0;
		LED_u8ACTIVE_HIGH;
	}LED_1;
	
	while(1)
	{
		if(DIO_u8GetPinValue(DIO_u8PORTA ,DIO_u8PIN1)==1)
		{
			LED_voidLedToggle(&LED_1);
		}
	}
}
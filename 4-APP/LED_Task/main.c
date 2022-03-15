/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "..\..\5-LIB\STD_TYPES.h"

#include <delay.h>

#include "..\..\1-MCAL\1-DIO\DIO_program.c"
#include "..\..\1-MCAL\2-PORT\PORT_program.c"

#include "..\..\2-HAL\2-LED\LED_program.c"
#include "..\..\2-HAL\3-SW\SW_program.c"

#define DEBOUNCE_TIME       20
#define DELAY_TIME          1000
#define F_CPU 8000000UL

LED_t Red = {LED_PORTA, LED_PIN0, LED_u8ACTIVE_HIGH};
SW_t PushButton = {SW_PORTA, SW_PIN1, SW_u8PULL_UP, DEBOUNCE_TIME};

void main(void)
{   
	PORT_voidInit();
	
	while(1)
	{
		while(SW_u8ReadSwicth(&PushButton)==PRESSED)
        {
            LED_voidLedToggle(&Red);
            delay_ms(DELAY_TIME);
        }
        LED_voidLedOff(&Red);
	}                 
}
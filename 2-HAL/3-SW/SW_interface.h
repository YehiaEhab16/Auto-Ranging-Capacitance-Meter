/*******************************************************/
/************		Author: Yehia Ehab 		************/
/************		Layer: HAL     		************/
/************		SWC: SW				************/
/************		Version: 1.00	 		************/
/************		Date: 1-9-2020 		************/
/*******************************************************/
/*******************************************************/


/* Preprocessor file guard */
#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

#define PRESSED					1
#define NOT_PRESSED				0

#define SW_u8PULL_UP 			0
#define SW_u8PULL_DOWN			1

#define SW_PORTA				DIO_u8PORTA
#define SW_PORTB				DIO_u8PORTB
#define SW_PORTC				DIO_u8PORTC
#define SW_PORTD				DIO_u8PORTD

#define SW_PIN0					DIO_u8PIN0
#define SW_PIN1					DIO_u8PIN1
#define SW_PIN2					DIO_u8PIN2
#define SW_PIN3					DIO_u8PIN3
#define SW_PIN4					DIO_u8PIN4
#define SW_PIN5					DIO_u8PIN5
#define SW_PIN6					DIO_u8PIN6
#define SW_PIN7					DIO_u8PIN7

typedef struct My_Struct
{
	u8 SW_u8Port;
	u8 SW_u8Pin;
	u8 SW_u8Connection;
	u8 SW_u8DebounceTime;
}SW_t;

u8 SW_u8ReadSwicth(SW_t* Copy_pu8Struct);


#endif

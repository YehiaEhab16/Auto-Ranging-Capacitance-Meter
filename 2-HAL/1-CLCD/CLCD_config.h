/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: HAL	     		************/
/************		SWC: CLCD 				************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

/* Preprocessor file guard */
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


#define CLCD_DATA_PORT 			DIO_u8PORTD

#define CLCD_CTRL_PORT 			DIO_u8PORTD

#define CLCD_RS_PIN 			DIO_u8PIN6
#define CLCD_RW_PIN 			DIO_u8PIN5
#define CLCD_E_PIN 				DIO_u8PIN4

#define CLCD_CONFIGURATION		CLCD_BITS_4

/* In case of 4 bits*/

#define CLCD_DB7			DIO_u8PIN0
#define CLCD_DB6 			DIO_u8PIN1
#define CLCD_DB5			DIO_u8PIN2
#define CLCD_DB4 			DIO_u8PIN3


#endif



#ifndef CAPACITANCE_FILE_H_
#define CAPACITANCE_FILE_H_


enum Range
{
	RES_220 ,
	RES_1K,
	RES_10K


};

enum Unit
{
	MileFarad ,
	MicroFarad,
	Farad


};


#define RES_220_PORT		DIO_u8PORTA
#define RES_1K_PORT         DIO_u8PORTA
#define RES_10K_PORT        DIO_u8PORTA

#define RES_220_PIN			DIO_u8PIN0
#define RES_1K_PIN          DIO_u8PIN1
#define RES_10K_PIN         DIO_u8PIN2


#define CAPACITANCE_VOLTAGE_PIN			DIO_u8PIN3


#define CAPCITANCE_VALUE_63_PERCANTAGE		646


#endif

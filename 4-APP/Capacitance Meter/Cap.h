

#ifndef CAPACITANCE_FILE_H_
#define CAPACITANCE_FILE_H_


enum Range
{
	RES_10,
	RES_10K,
	RES_10M,
	RES_50ohm,
	RES_100ohm,
	RES_1000ohm,
	RES_10kohm,
	RES_100kohm,
	RES_1Mohm,
	RES_5Mohm,
	RES_10Mohm
};

enum Unit
{
	MileFarad ,
	MicroFarad,
	Farad


};

#define CAP_METER		0
#define OHM_METER		1
#define DISP			0
#define NO_DISP			1
#define BUZZER_TONE		100
#define WELCOME_TIME	500

#define RES_10_PORT			DIO_u8PORTB
#define RES_10K_PORT        DIO_u8PORTB
#define RES_10M_PORT        DIO_u8PORTB
#define RES_330_PORT		DIO_u8PORTB

#define RES_10_PIN			DIO_u8PIN3
#define RES_10K_PIN         DIO_u8PIN4
#define RES_10M_PIN         DIO_u8PIN5
#define RES_330_PIN         DIO_u8PIN6


#define CAPACITANCE_VOLTAGE_PIN			DIO_u8PIN0


#define CAPCITANCE_VALUE_63_PERCANTAGE		646


#endif

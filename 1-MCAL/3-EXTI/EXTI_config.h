/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: MCAL	     		************/
/************		SWC: EXTI 				************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

/* Preprocessor file guard */
#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_


/*Choose INT0 Sense Control
 * Options: 1-LOW_LEVEL
 * 			2-ON_CHANGE
 * 			3-FALLING_EDGE
 * 			4-RISING_EDGE
 */
#define EXTI_INT0_SENSE		FALLING_EDGE
#define EXTI_INT1_SENSE		ON_CHANGE
#define EXTI_INT2_SENSE		FALLING_EDGE

/*Choose INT0 peripheral interrupt enable state
 * Options: 1-ENABLED
 * 			2-DISABLED
 */
#define EXTI_INT0_INITIAL_STATE		ENABLED
#define EXTI_INT1_INITIAL_STATE		ENABLED
#define EXTI_INT2_INITIAL_STATE		ENABLED

#endif

/*******************************************************/
/*******************************************************/
/************		T20: Capacitance Meter	************/
/************		Layer: MCAL	     		************/
/************		SWC: GIE 				************/
/************		Version: 1.00	 		************/
/************		Date: 13-3-2022 		************/
/*******************************************************/
/*******************************************************/

#include "..\..\5-LIB\STD_TYPES.h"
#include "..\..\5-LIB\BIT_MATH.h"

#include "GIE_register.h"
#include "GIE_interface.h"

void GIE_voidEnableGlobal(void)
{
	SET_BIT(SREG, SREG_I);
}

void GIE_voidDisableGlobal(void)
{
	CLR_BIT(SREG, SREG_I);
}


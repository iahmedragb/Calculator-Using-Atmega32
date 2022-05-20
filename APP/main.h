/*======================================================================================
========================    - main.h					 ===========================
========================    - Created: May 20, 2022			     ===========================
========================    - Author: Ahmed Tiba   			 ===========================
========================    - Version : _1_				     ===========================
========================    - Note :
									*-
									*-
=======================================================================================*/
/*====================================================================================
	- The Optiones Which Developer Choose From Which What Is Appropriate To App
=====================================================================================*/

#ifndef APP_MAIN_H_
#define APP_MAIN_H_
/*===========   INCLUDE LIB   ===========*/
#include "../LIB/Bit_Math.h"
#include "../LIB/Error_State.h"
#include "../LIB/Std_Types.h"
#include "util/delay.h"
/*===========  INCLUDE HAL   ===========*/
#include "../HAL/Keypad/Keypad_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
/*======================================*/

/*===========  INCLUDEAPP   ===========*/

/*=====================================*/

#define UP_DECIMAL_UNIT(N)	(N) *= 10
#define REVERSE_SIGN(N)	(N) *= (-1)
#define EMPTY		   		0
#define RAISED		   		1
#define POSTIVE			 	0
#define NEGATIVE		 	1
#define STAND_BY_MODE		'Z'

typedef struct
{
	u8 Error_Flag:1;
	u8 Sign_Flag1:1;
	u8 Sign_Flag2:1;
	u8 Sign_result_float_Flag:1;
	u8 First_Entery_Flag:1;
	u8 Second_Entery_Flag:1;
	u8 First_First_Digit_Flag:1;
	u8 Second_First_Digit_Flag:1;
	u8 result_flag:1;
	u8 operation:7;
	u8 key;
	s32 num1,num2;
	s32 result_Integer;
	f32 result_float;

}Calculator;
void Calculator_Init(Calculator *ptrStruct);

#endif /* APP_MAIN_H_ */

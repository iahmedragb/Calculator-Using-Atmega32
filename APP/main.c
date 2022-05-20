/*=======================================================================================
============================   - main.c						 ============================
============================   - Created: March 10, 2022	 ============================
============================   - Author: Ahmed Tiba			 ============================
============================   - Version : _1_				 ============================
============================   - Note :
									     *-
									     *-
=======================================================================================*/


/*====================================================   Application   ====================================================*/
/*
@Brief	:	This Application Operate as a real calculator with taking two negative or positive integers
 	 	 	 through a keypad and as Input then according to the specified operation print the result on LCD

*/
#include "main.h"
int main(void)
{
	Calculator MyCalculator;
	KEYPAD_enuInit();
	LCD_enuInit();
	Calculator_Init(&MyCalculator);

	while(1)
	{

		KEYPAD_enuGetPressedKey(&(MyCalculator.key));
		if ((MyCalculator.key != NOT_PRESSED)&&(MyCalculator.Error_Flag == EMPTY))
		{
			if(MyCalculator.result_flag == RAISED)
			{
				if(MyCalculator.key != '=')
				{
					u8 temp =MyCalculator.key;

					Calculator_Init(&MyCalculator);
					LCD_enuWriteCommand(0x01);

					MyCalculator.key = temp;
				}else
				{
					MyCalculator.key = STAND_BY_MODE;
				}
			}

			if(MyCalculator.key == 'C')
			{
				Calculator_Init(&MyCalculator);
				LCD_enuWriteCommand(0x01);
			}
			else if(MyCalculator.First_Entery_Flag)
			{
				if(((MyCalculator.key>='1')&&(MyCalculator.key<='9'))||(MyCalculator.key == '-')||(MyCalculator.key == '+'))
				{
					MyCalculator.First_Entery_Flag = EMPTY;
					LCD_enuWriteData(MyCalculator.key);
					if(MyCalculator.key == '-')
					{
						MyCalculator.Sign_Flag1 = NEGATIVE;
					}else if(MyCalculator.key == '+')
					{
						MyCalculator.Sign_Flag1 = POSTIVE;
					}else
					{
						MyCalculator.Sign_Flag1 = POSTIVE;
						MyCalculator.First_First_Digit_Flag = EMPTY;
						MyCalculator.num1=(MyCalculator.key-'0');
					}
				}else
				{
					//MyCalculator.Error_Flag = RAISED;
				}
			}else if(MyCalculator.First_First_Digit_Flag)
			{
				if((MyCalculator.key>='1')&&(MyCalculator.key<='9'))
					{
						MyCalculator.First_First_Digit_Flag = EMPTY;
						LCD_enuWriteData(MyCalculator.key);
						MyCalculator.num1=(MyCalculator.key-'0');
					}else
					{
						//MyCalculator.Error_Flag = RAISED;
					}
			}else if(MyCalculator.operation == EMPTY)
			{
				if((MyCalculator.key>='0')&&(MyCalculator.key<='9'))
				{
					UP_DECIMAL_UNIT(MyCalculator.num1);
					MyCalculator.num1 += ((MyCalculator.key)-'0');
					LCD_enuWriteData(MyCalculator.key);
				}else if((MyCalculator.key == '/')||(MyCalculator.key == 'x')||(MyCalculator.key == '+')||(MyCalculator.key == '-'))
				{
					MyCalculator.operation = MyCalculator.key;
					MyCalculator.Second_Entery_Flag = RAISED;
					MyCalculator.Second_First_Digit_Flag = RAISED;
					LCD_enuWriteData(MyCalculator.key);
				}else if(MyCalculator.key == '=')
				{
					MyCalculator.result_flag =RAISED;
					//LCD_enuWriteCommand(0x01);
					//LCD_enuWriteString("Result =");
					LCD_enuWriteData(MyCalculator.key);
					LCD_enuGoToPosition(2,1);
					if(MyCalculator.Sign_Flag1 == NEGATIVE)
					{
						REVERSE_SIGN(MyCalculator.num1);
					}
					LCD_enuWriteIntegerNum(MyCalculator.num1);
				}
			}else if(MyCalculator.Second_Entery_Flag)
			{
				if(((MyCalculator.key>='1')&&(MyCalculator.key<='9'))||(MyCalculator.key == '-')||(MyCalculator.key == '+'))
				{
					MyCalculator.Second_Entery_Flag = EMPTY;
					LCD_enuWriteData(MyCalculator.key);
					if(MyCalculator.key == '-')
					{
						MyCalculator.Sign_Flag2 = NEGATIVE;
					}else if(MyCalculator.key == '+')
					{
						MyCalculator.Sign_Flag2 = POSTIVE;
					}else
					{
						MyCalculator.Second_First_Digit_Flag = EMPTY;
						MyCalculator.Sign_Flag2 = POSTIVE;
						MyCalculator.num2=(MyCalculator.key-'0');
					}
				}else
				{
					//MyCalculator.Error_Flag = RAISED;
				}
			}else if(MyCalculator.Second_First_Digit_Flag)
			{
				if((MyCalculator.key>='1')&&(MyCalculator.key<='9'))
				{
					MyCalculator.Second_First_Digit_Flag = EMPTY;
					LCD_enuWriteData(MyCalculator.key);
					MyCalculator.num2=(MyCalculator.key-'0');
				}else
				{
					//MyCalculator.Error_Flag = RAISED;
				}
			}else if(MyCalculator.key != '=')
			{
				if((MyCalculator.key>='0')&&(MyCalculator.key<='9'))
				{
					UP_DECIMAL_UNIT(MyCalculator.num2);
					MyCalculator.num2 += ((MyCalculator.key)-'0');
					LCD_enuWriteData(MyCalculator.key);
				}else
				{
					//MyCalculator.Error_Flag = RAISED;
				}
			}
			else if(MyCalculator.key == '=')
			{
				MyCalculator.result_flag = RAISED;
				if(MyCalculator.operation != '/')
				{
					if(MyCalculator.Sign_Flag1 == NEGATIVE)
					{
						REVERSE_SIGN(MyCalculator.num1);
					}
					if(MyCalculator.Sign_Flag2 == NEGATIVE)
					{
						REVERSE_SIGN(MyCalculator.num2);
					}
				}else
				{
					if(MyCalculator.Sign_Flag1 == MyCalculator.Sign_Flag2)
					{
						MyCalculator.Sign_result_float_Flag =POSTIVE;
					}else
					{
						MyCalculator.Sign_result_float_Flag = NEGATIVE;
					}
				}

				//LCD_enuWriteCommand(0x01);
				//LCD_enuWriteString("Result =");
				LCD_enuWriteData(MyCalculator.key);
				LCD_enuGoToPosition(2,1);
				switch(MyCalculator.operation)
				{
				case '+' :
							MyCalculator.result_Integer = ((MyCalculator.num1) + (MyCalculator.num2));
							LCD_enuWriteIntegerNum(MyCalculator.result_Integer);
							break;
				case '-' :
							MyCalculator.result_Integer = MyCalculator.num1 - MyCalculator.num2;
							LCD_enuWriteIntegerNum(MyCalculator.result_Integer);
							break;
				case 'x' :
							MyCalculator.result_Integer = MyCalculator.num1 * MyCalculator.num2;
							LCD_enuWriteIntegerNum(MyCalculator.result_Integer);
							break;
				case '/' :
							if(MyCalculator.num2 == 0)
							{
								LCD_enuWriteString((u8*)"Undefined Value");
							}else
							{

								MyCalculator.result_float = ((f32)MyCalculator.num1) / MyCalculator.num2;
								if(MyCalculator.Sign_result_float_Flag == NEGATIVE)
								{
									LCD_enuWriteData('-');
								}
								LCD_enuWriteFloatNum(MyCalculator.result_float);
							}
							break;
				}
			}
		}else if(MyCalculator.Error_Flag == RAISED)
		{
			LCD_enuWriteCommand(0x01);
			LCD_enuWriteString((u8*)"Error Detected!");
			Calculator_Init(&MyCalculator);
			_delay_ms(500);
			LCD_enuWriteCommand(0x01);
		}
	}
}
void Calculator_Init(Calculator *ptrStruct)
{
	ptrStruct-> key = NOT_PRESSED;
	ptrStruct-> Sign_Flag1=POSTIVE;
	ptrStruct-> Sign_Flag2=POSTIVE;
	ptrStruct-> Sign_result_float_Flag=POSTIVE;
	ptrStruct-> Error_Flag=EMPTY;
	ptrStruct-> First_Entery_Flag=RAISED;
	ptrStruct-> Second_Entery_Flag=EMPTY;
	ptrStruct-> First_First_Digit_Flag=RAISED;
	ptrStruct-> Second_First_Digit_Flag=EMPTY;
	ptrStruct-> num1=EMPTY;
	ptrStruct-> num2=EMPTY;
	ptrStruct-> operation = EMPTY;
	ptrStruct-> result_flag =EMPTY;
	ptrStruct-> result_float=EMPTY;
	ptrStruct-> result_Integer=EMPTY;
}

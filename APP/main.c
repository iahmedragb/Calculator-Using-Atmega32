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
	/*Initialize HAL Layer*/
	KEYPAD_enuInit();
	LCD_enuInit();

	/*Create an object of type Calculator*/
	Calculator MyCalculator;
	/*Initialize the object*/
	Calculator_Init(&MyCalculator);

	while(1)
	{

		/*Read User Input*/
		KEYPAD_enuGetPressedKey(&(MyCalculator.key));

		/*Check if there is an input with no errors detected*/
		if ((MyCalculator.key != NOT_PRESSED)&&(MyCalculator.Error_Flag == EMPTY))
		{
			/*Check if result tab was entered*/
			if(MyCalculator.result_flag == RAISED)
			{
				/*Result tab*/

				/*Check if a new input was entered (excluded '=')*/
				if(MyCalculator.key != '=')
				{
					/*Store The entered key*/
					u8 temp =MyCalculator.key;

					/*Reinitialize the calculator*/
					Calculator_Init(&MyCalculator);

					/*Clear Display*/
					LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);

					/*Load the entered key to the Calculator key*/
					MyCalculator.key = temp;

				}else
				{
					/*Keep the result and do nothing*/
					MyCalculator.key = STAND_BY_MODE;
				}
			}

			/*Default Calculator tab*/

			/*If Clear Command was entered*/
			if(MyCalculator.key == 'C')
			{
				/*Reinitialize the system*/
				Calculator_Init(&MyCalculator);
				LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);
			}
			/*If an input was entered ('C' excluded)*/
			else if(MyCalculator.First_Entery_Flag)
			{
				/*Check if the input is valid for a first entery */
				if(((MyCalculator.key>='1')&&(MyCalculator.key<='9'))||(MyCalculator.key == '-')||(MyCalculator.key == '+'))
				{
					/*Clear First entry flag*/
					MyCalculator.First_Entery_Flag = EMPTY;
					/*Print Key*/
					LCD_enuWriteData(MyCalculator.key);

					/*Check if the value is a sign*/
					/*Set Number 1 flag to the proper sign*/
					if(MyCalculator.key == '-')
					{
						MyCalculator.Sign_Flag1 = NEGATIVE;
					}else if(MyCalculator.key == '+')
					{
						MyCalculator.Sign_Flag1 = POSTIVE;
					}else
					{
						/*Clear First_First_Digit_Flag */
						MyCalculator.Sign_Flag1 = POSTIVE;
						/*Print the input to LCD*/
						MyCalculator.First_First_Digit_Flag = EMPTY;
						/*Convert from ASCII to Integer and store in num1*/
						MyCalculator.num1=(MyCalculator.key-'0');
					}
				}else
				{
					/*Set the error flag for invalid Entry*/
					MyCalculator.Error_Flag = RAISED;
				}
				/*Check if first digit was entered*/
			}else if(MyCalculator.First_First_Digit_Flag)
			{
				/*Check if the input is valid*/
				if((MyCalculator.key>='1')&&(MyCalculator.key<='9'))
					{
						/*Clear First_First_Digit_Flag */
						MyCalculator.First_First_Digit_Flag = EMPTY;
						/*Print the input to LCD*/
						LCD_enuWriteData(MyCalculator.key);
						/*Convert from ASCII to Integer and store in num1*/
						MyCalculator.num1=(MyCalculator.key-'0');
					}else
					{
						/*Set the error flag for invalid Entry*/
						MyCalculator.Error_Flag = RAISED;
					}
				/*This condition to detect either the rest of number1 or operator*/
			}else if(MyCalculator.operation == EMPTY)
			{
				/*if the input is a number then this the rest of number1*/
				if((MyCalculator.key>='0')&&(MyCalculator.key<='9'))
				{
					/*Up the decimal Value of the number1*/
					UP_DECIMAL_UNIT(MyCalculator.num1);
					/*Add the new value*/
					MyCalculator.num1 += ((MyCalculator.key)-'0');
					/*Print the input*/
					LCD_enuWriteData(MyCalculator.key);

				}
				/*If the input is an operator*/
				else if((MyCalculator.key == '/')||(MyCalculator.key == 'x')||(MyCalculator.key == '+')||(MyCalculator.key == '-'))
				{
					/*Set Operator Flag*/
					MyCalculator.operation = MyCalculator.key;
					/*Set Second Entry Flag*/
					MyCalculator.Second_Entery_Flag = RAISED;
					/*Set Second Digit Flag*/
					MyCalculator.Second_First_Digit_Flag = RAISED;
					/*Print To LCD*/
					LCD_enuWriteData(MyCalculator.key);
				}
				/*if input is '=' Print the result of number1 only*/
				else if(MyCalculator.key == '=')
				{
					/*Set Result flag*/
					MyCalculator.result_flag =RAISED;
					//LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);
					//LCD_enuWriteString("Result =");
					LCD_enuWriteData(MyCalculator.key);
					LCD_enuGoToPosition(2,1);
					/*Check if the entered number is negative*/
					if(MyCalculator.Sign_Flag1 == NEGATIVE)
					{
						/*Modify the number sign*/
						REVERSE_SIGN(MyCalculator.num1);
					}
					/*Print To LCD*/
					LCD_enuWriteIntegerNum(MyCalculator.num1);
				}
			}
			/*Check user input for second Number*/
			else if(MyCalculator.Second_Entery_Flag)
			{
				/*Check if the input is valid*/
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
					/*Set the error flag for invalid Entry*/
					MyCalculator.Error_Flag = RAISED;
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
					/*Set the error flag for invalid Entry*/
					MyCalculator.Error_Flag = RAISED;
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
			/*In case the result was wanted by user*/
			else if(MyCalculator.key == '=')
			{
				/*Set Result flag*/
				MyCalculator.result_flag = RAISED;
				if(MyCalculator.operation != '/')
				{
					/*Modify Number1 and Number2 signs based on sign flag*/
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

				//LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);
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
			LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);
			LCD_enuWriteString((u8*)"Error Detected!");
			Calculator_Init(&MyCalculator);
			_delay_ms(500);
			LCD_enuWriteCommand(COMMAND_CLEAR_DISPLAY);
		}
	}
}
void Calculator_Init(Calculator *ptrStruct)
{
	/*Initialize Object*/
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

/*
 * Keypad_Config.h
 *
 * Created: 3/23/2022 7:47:38 PM
 *  Author: Ahmed
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define Col					4
#define Row					4

#define R1_PRT			DIO_PORTC
#define R1_PIN			DIO_Pin0

#define R2_PRT			DIO_PORTC
#define R2_PIN			DIO_Pin1

#define R3_PRT			DIO_PORTC
#define R3_PIN			DIO_Pin2

#define R4_PRT			DIO_PORTC
#define R4_PIN			DIO_Pin3

#define C1_PRT			DIO_PORTC
#define C1_PIN			DIO_Pin4

#define C2_PRT			DIO_PORTC
#define C2_PIN			DIO_Pin5

#define C3_PRT			DIO_PORTC
#define C3_PIN			DIO_Pin6

#define C4_PRT			DIO_PORTC
#define C4_PIN			DIO_Pin7

#define KEYS_VALUES			{				\
							{'7','8','9','/'},\
							{'4','5','6','x'},\
							{'1','2','3','-'},\
							{'C','0','=','+'}\
}
#endif /* KEYPAD_CONFIG_H_ */

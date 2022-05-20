/*
 * LCD_Interface.h
 *
 * Created: 3/19/2022 3:58:58 AM
 *  Author: Ahmed
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_



ES_t LCD_enuInit(void);
ES_t LCD_enuWriteCommand(u8 Copy_u8Command);
ES_t LCD_enuWriteData(u8 Copy_u8Data);
ES_t LCD_enuWriteString(const u8 *Copy_pu8String);
ES_t LCD_enuWriteIntegerNum(s32 Copy_s32IntegerNum);
ES_t LCD_enuWriteFloatNum(f32 Copy_f32FloatNum);
ES_t LCD_enuGoToPosition(u8 Copy_u8Row, u8 Copy_u8Column);
ES_t LCD_enuCharacterGenerator(u8 Pattern, const u8 *Copy_u8CustomCharacter);


ES_t LCD_enuStopWatch(u8 Seconds,u8  Minutes,u8  Hours);


#endif /* LCD_INTERFACE_H_ */
/*
 * LCD.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */

#ifndef LCD_H_
#define LCD_H_

//#include<stdio.h>
//#include<stdlib.h>


void LCD_vidWriteCharacter(u8 data);
void LCD_vidWriteCommand(u8 data);
void LCD_vidInit(void);
void LCD_vidWriteString(u8* ptr);
void LCD_vidWriteNumber(u32 number);
void LCD_vidSetPosition(u8 row,u8 colum);
void LCD_delay(void);


#endif /* LCD_H_ */

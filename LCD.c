/*


 * LCD.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */
#define F_CPU 8000000
#include<util/delay.h>
#include"types.h"
#include"register.h"
#include"micros.h"
#include "DIO.h"
#include "LCD_cfg.h"
#include"LCD.h"



void LCD_vidInit(void)
{
	DIO_vidSetPinDirection	(LCD_ControlPort,RS,1);
	DIO_vidSetPinDirection (LCD_ControlPort,RW,1);
	DIO_vidSetPinDirection (LCD_ControlPort,E,1);
	DIO_vidSetPortDirection (LCD_DataPort,255);
	_delay_ms(50);
	LCD_vidWriteCommand(0b00111000);
	_delay_ms(1);
	LCD_vidWriteCommand(0b00001100);
	_delay_ms(1);
	LCD_vidWriteCommand(0b00000001);
	_delay_ms(2);
}



void LCD_vidWriteCharacter(u8 data) //8bit
{
	DIO_vidSetPinValue(LCD_ControlPort, RW ,0);
	DIO_vidSetPinValue(LCD_ControlPort, RS ,1);
	DIO_vidSetPortValue(LCD_DataPort,data);
	DIO_vidSetPinValue(LCD_ControlPort,E,1);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_ControlPort,E,0);
	_delay_ms(1);

}




void LCD_vidWriteCommand(u8 data) //8bit
{
	DIO_vidSetPinValue(LCD_ControlPort,RW,0);
	DIO_vidSetPinValue(LCD_ControlPort,RS,0);
	DIO_vidSetPortValue(LCD_DataPort,data);
	DIO_vidSetPinValue(LCD_ControlPort,E,1);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_ControlPort,E,0);
	_delay_ms(1);

}







void LCD_vidWriteString(u8* ptr)
{
	u8 i=0;
	while(ptr[i]!=0)  /*='\0'*/
	{
		LCD_vidWriteCharacter(ptr[i]);
		i++;

	}

}

void LCD_vidWriteNumber(u32 number)
{
	u32 reversed_number = 1;
	if(number == 0)
	{
		LCD_vidWriteCharacter('0');
	}

	while(number != 0)
	{
		reversed_number = number % 10+ reversed_number * 10;
		number /= 10;
	}
	while(reversed_number != 1)
	{
		LCD_vidWriteCharacter((reversed_number % 10)+'0');
		reversed_number /= 10;
		//if(reversed_number==0) break;
	}

}
/*
void LCD_vidWriteNumber(u32 number)
{
	u8 arr_str[10] = {0};
	itoa(number,arr_str[10],10);
	LCD_vidWriteString((u8*) arr_str[10]);
}
*/
void LCD_vidSetPosition(u8 row,u8 colum)
{

	if(row==0)
	{
		LCD_vidWriteCommand(128+colum);
	}
	else if(row==1)
	{
		LCD_vidWriteCommand(128+64+colum);
	}

}


void LCD_delay(void)
{

	DIO_vidSetPortValue(0,0);
	_delay_ms(300);
	DIO_vidSetPortValue(0,225);
	_delay_ms(300);
	LCD_vidWriteCommand(0b00000001);
}



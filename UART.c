/*

 * UART.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Doaa
 */



#include"types.h"
#include"register.h"
#include"micros.h"
#include "DIO.h"



void UART_vidinit(void)
{
	DIO_vidSetPinDirection(3,0,0);
	DIO_vidSetPinDirection(3,1,1);

	UCSRA=0b00000000;
	//UCSRA=0b11100000;

	UCSRB=0x18;
	//UCSRB=0b00011011;


	//UCSRC=0b10000110;
	UCSRC=0x86;

	//UBRRL=0b00110011;
	UBRRL=51;


	UBRRH=0b00000000;
}

u8 UART_u8Reciver(void)

{
	while(GetBit(UCSRB,7) == 0)
	{

	}


	return UDR;

}

void UART_vidTransmitter(u8 data)
{
	UDR = data;
	while(GetBit(UCSRA,5) == 0)
	{


	}
}

void writeString(u8 *str)
{
	u8 j=0;
	while (str[j] != 0)
	{
		UART_vidTransmitter(str[j]);
		j++;
	}
}


/*
void writeString(char *str)
{
	while (*str != '\0')
	{
		putByte(*str);
		++str;
	}
}
*/

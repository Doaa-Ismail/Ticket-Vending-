/*

 * DIO.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */

#include"types.h"
#include"register.h"
#include"micros.h"

void DIO_vidSetPortDirection (u8 PortNumber,u8 Value)
{
	switch(PortNumber)
	{
	case 0 :
		DDRA = Value;
		break;
	case 1 :
		DDRB =Value;
		break;
	case 2 :
		DDRC =Value;
		break;
	case 3 :
		DDRD=Value;
		break;
	}
}

void DIO_vidSetPortValue(u8 PortNumber,u8 Value)
{
	switch(PortNumber)
	{
	case 0 :
		PORTA= Value;
		break;
	case 1 :
		PORTB =Value;
		break;
	case 2 :
		PORTC =Value;
		break;
	case 3 :
		PORTD =Value;
		break;

	}
}

u8 DIO_u8ReadPort(u8 PortNumber)
{
	u8 value;
	switch(PortNumber)
	{
	case 0 :
		value=PINA;
		break;
	case 1 :
		value=PINB;
		break;
	case 2 :
		value=PINC;
		break;
	case 3 :
		value=PIND;
		break;

	}

	return value;
}

void DIO_vidSetPinValue(u8 PortNumber,u8 PinNumber,u8 Value)
{
	switch (PortNumber)
	{
	case 0 :
		if(Value==1)
		{SetBit(PORTA,PinNumber);}
		else if (Value==0)
		{ClrBit(PORTA,PinNumber);}
		break;
	case 1:
		if(Value==1)
		{SetBit(PORTB,PinNumber);}
		else if (Value==0)
		{ClrBit(PORTB,PinNumber);}
		break;
	case 2:
		if(Value==1)
		{SetBit(PORTC,PinNumber);}
		else if (Value==0)
		{ClrBit(PORTC,PinNumber);}
		break;
	case 3:
		if(Value==1)
		{SetBit(PORTD,PinNumber);}
		else if (Value==0)
		{ClrBit(PORTD,PinNumber);}
		break;
	}
}
void DIO_vidSetPinDirection(u8 PortNumber,u8 PinNumber,u8 Value)
{
	switch(PortNumber)
	{
	case 0:
		if(Value==1)
		{SetBit(DDRA,PinNumber);}
		else if(Value==0)
		{ClrBit(DDRA,PinNumber);}
		break;
	case 1:
		if(Value==1)
		{SetBit(DDRB,PinNumber);}
		else if(Value==0)
		{ClrBit(DDRB,PinNumber);}
		break;
	case 2:
		if(Value==1)
		{SetBit(DDRC,PinNumber);}
		else if(Value==0)
		{ClrBit(DDRC,PinNumber);}
		break;

	case 3:
		if(Value==1)
		{SetBit(DDRD,PinNumber);}
		else if(Value==0)
		{ClrBit(DDRD,PinNumber);}
		break;
	}

}


u8 DIO_u8ReadPin(u8 PortNumber,u8 PinNumber)
{
	u8 value;

	switch(PortNumber)
	{
	case 0:
		value =GetBit(PINA,PinNumber);
		break;
	case 1:
		value =GetBit(PINB,PinNumber);
		break;
	case 2:
		value =GetBit(PINC,PinNumber);
		break;
	case 3:
		value =GetBit(PIND,PinNumber);
		break;
	}
	return value;
}

void DIO_vidTogglePin(u8 PortNumber,u8 PinNumber)
{
	switch(PortNumber)
	{
	case 0:
		ToggleBit(PORTA,PinNumber);
		break;
	case 1:
		ToggleBit(PORTB,PinNumber);
		break;
	case 2:
		ToggleBit(PORTC,PinNumber);
		break;
	case 3:
		ToggleBit(PORTD,PinNumber);
		break;
	}


}



/*u16 DIO_vidTogglePin(u8 PortNumber,u8 PinNumber)
{
	u16 Pin=0;
	switch(PortNumber)
	{
	case 0:
		Pin=ToggleBit(PORTA,PinNumber);
		break;
	case 1:
		Pin=ToggleBit(PORTB,PinNumber);
		break;
	case 2:
		Pin=ToggleBit(PORTC,PinNumber);
		break;
	case 3:
		Pin	=ToggleBit(PORTD,PinNumber);
		break;
	}

	return Pin;
}

*/



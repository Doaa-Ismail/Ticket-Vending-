/*

 * KEY.c
 *
 *  Created on: Aug 30, 2019
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
#include "KEY_cfg.h"
#include "KEY.h"

void Keybad_vidInit(void)
{
	DIO_vidSetPinDirection (Keybad_Port,R1,0);
	DIO_vidSetPinDirection (Keybad_Port,R2,0);
	DIO_vidSetPinDirection (Keybad_Port,R3,0);
	DIO_vidSetPinDirection (Keybad_Port,R4,0);

	DIO_vidSetPinValue (Keybad_Port,R1,1);
	DIO_vidSetPinValue (Keybad_Port,R2,1);
	DIO_vidSetPinValue (Keybad_Port,R3,1);
	DIO_vidSetPinValue (Keybad_Port,R4,1);

	DIO_vidSetPinDirection (Keybad_Port,C1,1);
	DIO_vidSetPinDirection (Keybad_Port,C2,1);
	DIO_vidSetPinDirection (Keybad_Port,C3,1);
	DIO_vidSetPinDirection (Keybad_Port,C4,1);


}


u8 Keybad_GetButtonStatus(u8 ButtonNo)
{
	u8 row,colum;
	u8 Real_col[]={C1,C2,C3,C4};
	u8 Real_row[]={R1,R2,R3,R4};
	u8 status =0,value;
	/*row =button/4+(button%4!=0)*/

	row=((ButtonNo-1)/4)+1;
	colum=((ButtonNo-1)%4)+1;

	DIO_vidSetPinValue (Keybad_Port,C1,1);
	DIO_vidSetPinValue (Keybad_Port,C2,1);
	DIO_vidSetPinValue (Keybad_Port,C3,1);
	DIO_vidSetPinValue (Keybad_Port,C4,1);

	DIO_vidSetPinValue (Keybad_Port,Real_col[colum-1],0);

	value= DIO_u8ReadPin(Keybad_Port,Real_row[row-1]);
	if(value==0)
	{
		_delay_ms(20);
		value= DIO_u8ReadPin(Keybad_Port,Real_row[row-1]);
		if(value==0)
		{
			status=1;
		}
	}
	return status;
}

/*u16 Keybad_Read (u16 number)
{
	u16 value;
    Keybad_GetButtonStatus(number);
	value=DIO_u8ReadPin(Keybad_Port,number);

	return value;
}
*/


u8 kpad_u8GetBtnSym( u8 ButtonNo )
{
	u8 but;
	switch( ButtonNo )
	{
	case BTN1:
		but=1;
		return but;
		break;
	case BTN2:
		but=2;
		return but;
		break;
	case BTN3:
		but=3;
		return but;
		break;
	case BTN4:
		but=4;
		return but;
		break;
	case BTN5:
		but=5;
		return but;
		break;
	case BTN6:
		but=6;
		return but;
		break;
	case BTN7:
		but=7;
		return but;
		break;
	case BTN8:
		but=8;
		return but;
		break;
	case BTN9:
		but=9;
		return but;
		break;
	case BTN10:
		but=0;
		return but;
		break;
	case BTN_EQU:
		but=250;
		return but;
		break;
	case BTN_CLR:
		but=240;
		return but;
		break;
	case BTN_ti3:
		but=50;
		return but;
		break;
	case BTN_ti5:
		but=100;
		return but;
		break;
	case BTN_ti7:
		but=150;
		return but;
		break;
	case BTN_t10:
		but=200;
		return but;
		break;
	}
	return 0;
}


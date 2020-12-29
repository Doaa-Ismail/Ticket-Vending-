/*



 * main.c


 *
 *  Created on: Feb 12, 2020
 *      Author: Doaa
 */

#define F_CPU 8000000
#include<util/delay.h>
#include"types.h"
#include"DIO.h"
#include"micros.h"
#include"register.h"
#include"LCD.h"
#include"LCD_cfg.h"
#include"KEY.h"
#include"KEY_cfg.h"
#include "UART.h"

/// cash and coin acceptor and keypad and h.bridge

volatile static u8 on_off_switch=0;
volatile static u8 counter=0;
volatile static u8 counter1=0;
volatile static u8 counter2=0;
volatile static u8 credit=0;
volatile static u8 flag = 0;
volatile static u8 flagx= 0;
volatile static u8 flag2=0;
volatile static u8 flag3=0;


//**********************external coin acceptor******************//
#define __INTR_ATTRS used, externally_visible
void __vector_1 (void) __attribute__ ((signal,__INTR_ATTRS)) ;
void __vector_1 (void)
{
	// your code0
	_delay_ms(10);
	counter1=DIO_u8ReadPin(3,2);
	_delay_ms(20);
	counter2=DIO_u8ReadPin(3,2);

	if((counter1== 1)&&(counter2==0))
	{
		LCD_vidSetPosition(1,0);
		credit=credit+50;
		LCD_vidWriteString( (u8*) "credit");
		LCD_vidWriteCharacter('=');
		LCD_vidWriteNumber(credit);
		counter = counter +(50/100);
		_delay_ms(500);
	}

	else if((counter1==1)&&(counter2==1))
	{
		LCD_vidSetPosition(1,0);
		credit=credit+1;
		LCD_vidWriteString( (u8*) "credit");
		LCD_vidWriteCharacter('=');
		LCD_vidWriteNumber(credit);
		_delay_ms(500);
		counter = counter +1;
	}
}


int main(void)
{
	u16 x,y,z,r,rest ;
	u8 i,j,res3=0,res5=0,res7=0,res10=0,result=0,ticket,sum=0 ;
	u8 result0=0,result1=0,result2=0,result3=0,result4=0,result5=0,result6=0,result7=0,result8=0,result9=0;
	u32 value;
	u16 keyflag[16] ;
	u8 sym;

	UART_vidinit();
	LCD_vidInit();
	Keybad_vidInit();

	//TIMER1 PWM TO CONTROL SERVO MOTOR
	TCCR1A = 0b01010010;
	TCCR1B = 0b00011101;
	ICR1 = 156;

	//EXTERNAL INTERRUPT IO0

	SetBit(MCUCR,0);
	SetBit(MCUCR,1);
	ClrBit(MCUCR,2);
	ClrBit(MCUCR,3);

	SetBit(GICR,6);
	ClrBit(GICR,7);
	ClrBit(GICR,5);

	SetBit(SREG,7);

	//**PORTA Keypad,PORTB LCD(DATA),PORTC (0,1,7 [CONFG. LCD],6 [MOTOR DRIVER])*//

	DIO_vidSetPinDirection(3,7,0);     //INPUT PIN CASH =1LE
	DIO_vidSetPinDirection(3,6,0);     //INPUT PIN CASH =5LE
	DIO_vidSetPinDirection(3,3,0);     //INPUT PIN CASH =10LE
	DIO_vidSetPinDirection(3,4,0);     //INPUT PIN CASH =20LE
	DIO_vidSetPinDirection(3,5,255);   //OUTPUT PIN FOR SERVO MOYTOR USING PWM
	DIO_vidSetPinDirection(3,2,0);     //INPUT PIN FOR COIN ACCPATOR
	// PORTD BITS 0,1 UART (RX and TX )

	DIO_vidSetPinDirection(2,6,255);   //OUTPUT PIN FOR MOTOR DC DRIVER
	DIO_vidSetPinDirection(2,2,0);     //INPUT PIN FOR ON/OFF SWITCH

	while(1)
	{
		DIO_vidSetPinValue(2,2,1);
		on_off_switch = DIO_u8ReadPin(2,2);
		if(on_off_switch == 1)
		{LCD_vidSetPosition(0,0);
		LCD_vidWriteString((u8*)"*PleasePressON*");}

		DIO_vidSetPinValue(3,7,255);  //INPUT PULLUP FOR CASH =1LE
		DIO_vidSetPinValue(3,6,255);  //INPUT PULLUP FOR CASH =5LE
		DIO_vidSetPinValue(3,3,255);  //INPUT PULLUP FOR CASH =10LE
		DIO_vidSetPinValue(3,4,255);  //INPUT PULLUP FOR CASH =20LE
		DIO_vidSetPinValue(3,2,0);    //INPUT FOR COIN ACCEPTOR
		DIO_vidSetPinValue(3,5,1);    //OUTPUT SERVO MOTOR T01

		while (flag == 1)
		{
			LCD_vidSetPosition(0,0);
			LCD_vidWriteString((u8*)"EnterCredit:");
			_delay_ms(50);
			while(flag3 != 1)
			{
				DIO_vidTogglePin(3,7);  //CASH 1LE
				DIO_vidTogglePin(3,6);  //CASH 5LE
				DIO_vidTogglePin(3,3);  //CASH 10LE
				DIO_vidTogglePin(3,4);  //CASH 20LE

				x=DIO_u8ReadPin(3,7);  //CASH 1LE
				y=DIO_u8ReadPin(3,6);  //CASH 5LE
				z=DIO_u8ReadPin(3,3);  //CASH 10LE
				r=DIO_u8ReadPin(3,4);  //CASH 20LE

				if(x==0)
				{
					LCD_vidSetPosition(1,0);
					credit=credit+1;
					LCD_vidWriteString( (u8*) "credit");
					LCD_vidWriteCharacter('=');
					LCD_vidWriteNumber(credit);
					_delay_ms(100);
				}
				if(y==0)
				{
					LCD_vidSetPosition(1,0);
					credit=credit+5;
					LCD_vidWriteString( (u8*) "credit");
					LCD_vidWriteCharacter('=');
					LCD_vidWriteNumber(credit);
					_delay_ms(100);
				}
				if(z==0)
				{
					LCD_vidSetPosition(1,0);
					credit=credit+10;
					LCD_vidWriteString( (u8*) "credit");
					LCD_vidWriteCharacter('=');
					LCD_vidWriteNumber(credit);
					_delay_ms(100);
				}
				if(r==0)
				{
					LCD_vidSetPosition(1,0);
					credit=credit+20;
					LCD_vidWriteString( (u8*) "credit");
					LCD_vidWriteCharacter('=');
					LCD_vidWriteNumber(credit);
					_delay_ms(100);
				}
				while(Keybad_GetButtonStatus(13)==1)
				{
					LCD_vidSetPosition(1,12);
					LCD_vidWriteString((u8*)"OK");
					flag3 = 1;

				}
			}

			flag=0;
		}
		while(flag3==1)
		{
			LCD_vidSetPosition(0,0);
			LCD_vidWriteCommand(0b00000001);
			if(credit == sum)
			{
				LCD_vidSetPosition(0,0);
				LCD_vidWriteString((u8*)"DoneCredit");
				UART_vidTransmitter('E');
				LCD_vidSetPosition(1,0);
				LCD_vidWriteString((u8*)"TicketsarePrinted");
				_delay_ms(1000);
				flag = 0;
				flag3 =0;
			}
			if(credit > sum)
			{
				LCD_vidSetPosition(0,0);
				rest=credit-sum;
				LCD_vidWriteString((u8*)"YourRest=");
				LCD_vidWriteNumber(rest);
				for(j = 0;j<= rest;j++)
				{
					OCR1A=2;
					_delay_ms(1500);
					OCR1A=15.6;
					_delay_ms(1000);
					OCR1A=2;
					_delay_ms(1500);
					if(i == rest)
					{break;}
				}
				if(rest>=5)
				{
					//motor driver
					flag2=1;
				}
				UART_vidTransmitter('E');
				LCD_vidWriteString((u8*)"TicketsarePrinted");
				_delay_ms(1000);
			}
			if(credit < sum)
			{
				LCD_vidSetPosition(0,0);
				rest=sum-credit;
				LCD_vidWriteString((u8*)"NotEnough:");
				LCD_vidWriteNumber(rest);
				_delay_ms(400);
				LCD_vidSetPosition(1,0);
				LCD_vidWriteString((u8*)"EnterMoreCredit:");
				_delay_ms(500);
				if(Keybad_GetButtonStatus(15)==1)
				{
					LCD_vidSetPosition(1,5);
					LCD_vidWriteString((u8*)"CencelTicket");
					UART_vidTransmitter('Q');
				}
				while(flag3==1)
				{
					DIO_vidTogglePin(3,7);  //CASH 1
					DIO_vidTogglePin(3,6);  //CASH 5
					DIO_vidTogglePin(3,3);  //CASH 10
					DIO_vidTogglePin(3,4);  //CASH20

					x=DIO_u8ReadPin(3,7);
					y=DIO_u8ReadPin(3,6);
					z=DIO_u8ReadPin(3,3);
					r=DIO_u8ReadPin(3,4);
					if(x==0)
					{
						LCD_vidSetPosition(1,0);
						credit=credit+1;
						LCD_vidWriteString( (u8*) "credit");
						LCD_vidWriteCharacter('=');
						LCD_vidWriteNumber(credit);
						//flag_A = 1;
						//counter++;
						_delay_ms(500);
					}
					if(y==0)
					{
						LCD_vidSetPosition(1,0);
						credit=credit+5;
						LCD_vidWriteString( (u8*) "credit");
						LCD_vidWriteCharacter('=');
						LCD_vidWriteNumber(credit);
						//flag_B = 1;
						//counter++;
						_delay_ms(500);
					}
					if(z==0)
					{
						LCD_vidSetPosition(1,0);
						credit=credit+10;
						LCD_vidWriteString( (u8*) "credit");
						LCD_vidWriteCharacter('=');
						LCD_vidWriteNumber(credit);
						//flag_C = 1;
						//counter++;
						_delay_ms(500);
					}
					if(r==0)
					{
						LCD_vidSetPosition(1,0);
						credit=credit+20;
						LCD_vidWriteString( (u8*) "credit");
						LCD_vidWriteCharacter('=');
						LCD_vidWriteNumber(credit);
						//flag_D = 1;
						//counter++;
						_delay_ms(500);
					}
					while(Keybad_GetButtonStatus(13)==1)
					{
						LCD_vidSetPosition(1,12);
						LCD_vidWriteString((u8*)"Okay");
						//flag3 = 1;

						if(credit == sum)
						{
							LCD_vidSetPosition(0,0);
							LCD_vidWriteString((u8*)"Done credit");
							DIO_vidSetPinValue(3,0,255);
							_delay_ms(500);
							UART_vidTransmitter('E');
							LCD_vidSetPosition(1,0);
							LCD_vidWriteString((u8*)"TicketsarePrinted");
							_delay_ms(1000);
						}
						if(credit > sum)
						{
							LCD_vidSetPosition(1,0);
							rest=credit-sum;
							LCD_vidWriteString((u8*)"YourRest=");
							LCD_vidWriteNumber(rest);
							for(j = 0;j<= rest;j++)
							{
								OCR1A=2;
								_delay_ms(1500);
								OCR1A=15.6;
								_delay_ms(1000);
								OCR1A=2;
								_delay_ms(1500);
								if(i == rest)
								{break;}
							}
							if(rest>=5)
							{
								//motor driver
								flag2=1;
							}
							UART_vidTransmitter('E');
							LCD_vidSetPosition(0,0);
							LCD_vidWriteString((u8*)"TicketsarePrinted");
							_delay_ms(1000);
						}
					}
				}

				flag3=0;
				flag =0;
			}
			if(flag2==1)
			{
				DIO_vidSetPinValue(2,6,1);
				_delay_ms(2000);
				DIO_vidSetPinValue(2,6,0);
				_delay_ms(2000);
				flag2 = 0;
			}
			flag = 0;
		}
		//*********************KEYPAD*********************//
		while ((flag==0)&&(flag3 ==0))
		{
			LCD_vidSetPosition(0,0);
			LCD_vidWriteString((u8*) "Ticket:A|B|C|D:");
			for(i=1;i<17;i++)
			{
				value=Keybad_GetButtonStatus(i);
				if ((value==1)&&(keyflag[i]==0))
				{
					sym= kpad_u8GetBtnSym(i);
					switch (sym)
					{
					case 50:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteCharacter('A');
						ticket=3;
						flagx = 1;
						break;
					case 100:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteCharacter('B');
						ticket=5;
						flagx = 2;
						break;
					case 150:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteCharacter('C');
						ticket=7;
						flagx =3;
						break;
					case 200:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteCharacter('D');
						ticket=10;
						flagx = 4;
						break;
					case 240:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteString((u8*) "Cancel");
						sum=0;
						result=0;
						result0=0;
						result1=0;
						result2=0;
						result3=0;
						result4=0;
						result5=0;
						result6=0;
						result7=0;
						result8=0;
						result9=0;
						flag=0;
						credit=0;
						flagx = 0;
						LCD_vidWriteCommand(0b00000001);
						UART_vidTransmitter('Q');
						break;
					case 250:
						LCD_vidSetPosition(1,0);
						LCD_vidWriteString((u8*) "Okay");
						_delay_ms(600);
						LCD_vidWriteCommand(0b00000001);
						sum = result;
						LCD_vidSetPosition(0,0);
						LCD_vidWriteString((u8*) "Tickets:");
						LCD_vidWriteNumber(result);
						_delay_ms(600);
						flag = 1;
						break;
					case 0:
						if(ticket==3)
						{res3=10*ticket;}
						if(ticket==5)
						{res5=10*ticket;}
						if(ticket==7)
						{res7=10*ticket;}
						if(ticket==10)
						{res10=10*ticket;}
						result0=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						//LCD_vidWriteCharacter('Z');
						result= result0;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A');UART_vidTransmitter('1'); UART_vidTransmitter('0');}
						if(flagx == 2)
						{UART_vidTransmitter('B');UART_vidTransmitter('1'); UART_vidTransmitter('0');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('1'); UART_vidTransmitter('0');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('1'); UART_vidTransmitter('0');}
						break;
					case 1:
						if(ticket==3)
						{res3=1*ticket;}
						if(ticket==5)
						{res5=1*ticket;}
						if(ticket==7)
						{res7=1*ticket;}
						if(ticket==10)
						{res10=1*ticket;}
						result1=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						//LCD_vidWriteCharacter('O');
						result =result1;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('1');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('1');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('1');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('1');}
						break;
					case 2:
						if(ticket==3)
						{res3=2*ticket;}
						if(ticket==5)
						{res5=2*ticket;}
						if(ticket==7)
						{res7=2*ticket;}
						if(ticket==10)
						{res10=2*ticket;}
						result2=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						//LCD_vidWriteCharacter('T');
						result = result2;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('2');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('2');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('2');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('2');}
						break;
					case 3:
						if(ticket==3)
						{res3=3*ticket;}
						if(ticket==5)
						{res5=3*ticket;}
						if(ticket==7)
						{res7=3*ticket;}
						if(ticket==10)
						{res10=3*ticket;}
						result3=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						//LCD_vidWriteCharacter('H');
						result = result3;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('3');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('3');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('3');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('3');}
						break;
					case 4:
						UART_vidTransmitter('4');
						if(ticket==3)
						{res3=4*ticket;}
						if(ticket==5)
						{res5=4*ticket;}
						if(ticket==7)
						{res7=4*ticket;}
						if(ticket==10)
						{res10=4*ticket;}
						result4=res3+res5+res7+res10;
						LCD_vidSetPosition(0,8);
						//LCD_vidWriteCharacter('F');
						result = result4;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('4');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('4');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('4');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('4');}
						break;
					case 5:
						UART_vidTransmitter('5');
						if(ticket==3)
						{res3=5*ticket;}
						if(ticket==5)
						{res5=5*ticket;}
						if(ticket==7)
						{res7=5*ticket;}
						if(ticket==10)
						{res10=5*ticket;}
						result5=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						result = result5;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('5');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('5');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('5');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('5');}
						break;
					case 6:
						UART_vidTransmitter('6');
						if(ticket==3)
						{res3=6*ticket;}
						if(ticket==5)
						{res5=6*ticket;}
						if(ticket==7)
						{res7=6*ticket;}
						if(ticket==10)
						{res10=6*ticket;}
						result6=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						result = result6;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('6');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('6');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('6');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('6');}
						break;
					case 7:
						UART_vidTransmitter('7');
						if(ticket==3)
						{res3=7*ticket;}
						if(ticket==5)
						{res5=7*ticket;}
						if(ticket==7)
						{res7=7*ticket;}
						if(ticket==10)
						{res10=7*ticket;}
						result7=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						result = result7;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('7');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('7');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('7');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('7');}
						break;
					case 8:
						UART_vidTransmitter('8');
						if(ticket==3)
						{res3=8*ticket;}
						if(ticket==5)
						{res5=8*ticket;}
						if(ticket==7)
						{res7=8*ticket;}
						if(ticket==10)
						{res10=8*ticket;}
						result8=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						result = result8;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('8');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('8');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('8');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('8');}
						break;
					case 9:
						UART_vidTransmitter('9');
						if(ticket==3)
						{res3=9*ticket;}
						if(ticket==5)
						{res5=9*ticket;}
						if(ticket==7)
						{res7=9*ticket;}
						if(ticket==10)
						{res10=9*ticket;}
						result9=res3+res5+res7+res10;
						LCD_vidSetPosition(1,1);
						result = result9;
						LCD_vidWriteNumber(result);
						if(flagx == 1)
						{UART_vidTransmitter('A'); UART_vidTransmitter('9');}
						if(flagx == 2)
						{UART_vidTransmitter('B'); UART_vidTransmitter('9');}
						if(flagx == 3)
						{UART_vidTransmitter('C'); UART_vidTransmitter('9');}
						if(flagx == 4)
						{UART_vidTransmitter('D'); UART_vidTransmitter('9');}
						break;
					default:
						break;
					}
					keyflag[i]=1;
				}

				else if(value==0)
				{
					keyflag[i]=0;
				}

			}
		}
	}
	return 1;
}

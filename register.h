/*
 * register.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#define DDRA *((u8 *)0x3A)
#define PORTA *((u8 *)0x3B)
#define PINA *((volatile u8 *)0x39)

#define DDRB *((u8 *)0x37)
#define PORTB *((u8 *)0x38)
#define PINB *((volatile u8 *)0x36)

#define DDRC *((u8 *)0x34)
#define PORTC *((u8 *)0x35)
#define PINC *((volatile u8 *)0x33)

#define DDRD *((u8 *)0x31)
#define PORTD *((u8 *)0x32)
#define PIND *((volatile u8 *)0x30)


#define SREG *((volatile u8 *)0x5f)
#define MCUCR *((volatile u8 *)0x55)
#define GICR *((volatile u8 *)0x5B)

#define TCCR0 *((volatile u8 *)0x53)
#define TCNTO *((volatile u8 *)0x52)
#define TIMSK *((volatile u8 *)0x59)
#define TIFR *((volatile u8 *)0x58)
#define OCR0 *((volatile u8 *)0x5c)


#define OCR1A *((volatile u16 *)0x4A)
#define ICR1 *((volatile u16 *)0x46)
#define TCCR1A *((volatile u8 *)0x4F)
#define TCCR1B *((volatile u8 *)0x4E)


#define MCUCSR *((volatile u16 *)0x54)
#define WDTCR *((volatile u16 *)0x41)

#define ADMUX *((volatile u16 *)0x27)
#define ADCSRA *((volatile u16 *)0x26)
#define SFIOR *((volatile u16 *)0x50)
#define ADCH *((volatile u16 *)0x25)
//#define ADCH *((volatile u16 *)0x24)


#define UDR *((volatile u8 *)0x2C)
#define UCSRA *((volatile u8 *)0x2B)
#define UCSRB *((volatile u8 *)0x2A)
#define UCSRC *((volatile u8 *)0x40)
#define UBRRH *((volatile u8 *)0x40)
#define UBRRL *((volatile u8 *)0x29)

#endif /* REGISTER_H_ */

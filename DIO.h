/*
 * DIO.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */

#ifndef DIO_H_
#define DIO_H_

void DIO_vidSetPortDirection (u8 PortNumber,u8 Value);
void DIO_vidSetPortValue(u8 PortNumber,u8 Value);
u8 DIO_u8ReadPort(u8 PortNumber);
void DIO_vidSetPinValue(u8 PortNumber,u8 PinNumber,u8 Value);
u8 DIO_u8ReadPin(u8 PortNumber,u8 PinNumber);
void DIO_vidSetPinDirection(u8 PortNumber,u8 PinNumber,u8 Value);
void DIO_vidTogglePin(u8 PortNumber,u8 PinNumber);

#endif /* DIO_H_ */

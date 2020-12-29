/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Doaa
 */

#ifndef UART_H_
#define UART_H_

void UART_vidinit(void);
u8 UART_u8Reciver(void);
void UART_vidTransmitter(u8 data);
void writeString(u8 *str);



#endif /* UART_H_ */

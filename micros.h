/*
 * micros.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Doaa
 */

#ifndef MICROS_H_
#define MICROS_H_

#define SetBit(data,bit) data |= (1<<bit)
#define ClrBit(data,bit) data &= ~(1<<bit)
#define ToggleBit(data,bit) data ^=(1<<bit)
#define GetBit(data,bit)  (data>>bit)&1



#endif /* MICROS_H_ */

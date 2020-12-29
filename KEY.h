/*
 * KEY.h
 *
 *  Created on: Aug 30, 2019
 *      Author: Doaa
 */

#ifndef KEY_H_
#define KEY_H_

void Keybad_vidInit(void);
u8 Keybad_GetButtonStatus(u8 ButtonNo);
//u16 Keybad_Read (u16 number);
u8 kpad_u8GetBtnSym( u8 ButtonNo );

#endif /* KEY_H_ */

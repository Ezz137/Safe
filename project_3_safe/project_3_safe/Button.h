/*
 * Button.h
 *
 * Created: 02/12/2024 18:50:50
 *  Author: zezom
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
void But_vInit(unsigned char PORT,unsigned char pin);
unsigned char But_uRead(unsigned char PORT, unsigned char pin,unsigned char PULLUPDOWN);
#endif /* BUTTON_H_ */
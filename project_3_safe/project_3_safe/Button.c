/*
 * Button.c
 *
 * Created: 02/12/2024 18:32:54
 *  Author: zezom
 */ 
#include "DIO.h"

void But_vInit(unsigned char PORT,unsigned char pin)
{
	DIO_vSet_pin(PORT,pin,0);
}

unsigned char But_uRead(unsigned char PORT, unsigned char pin,unsigned char PULLUPDOWN)
{
	unsigned char return_valu=0;
	switch(PULLUPDOWN)
	{
		case 0:
		{
			return_valu=DIO_uRead_pin(PORT,pin);
			break;
		}
		default:
		{
			return_valu=DIO_uRead_pin(PORT,pin);
			if(return_valu==0)
			{
				return_valu=1;
			}
			else
			{
				return_valu=0;
			}
			break;
		}		
	}
	return return_valu;
}
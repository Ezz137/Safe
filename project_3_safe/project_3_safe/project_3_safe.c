/*
 * project_3_safe.c
 *
 * Created: 17/12/2024 22:20:02
 *  Author: zezom
 */ 

#include "EEPROM.h"
#include "LCD.h"
#include "Keypad.h"
#include "Button.h"
#define F_CPU 1000000LU
#include "util/delay.h"
#include "Servo_Motor_Driver.h"
#define Status_Value_address 0x20
#define first_letter_address 0x21
#define second_letter_address 0x22
#define third_letter_address 0x23
#define fourth_letter_address 0x24
#define tries 3
unsigned char arr[4];

int main(void)
{
	LCD_vInit();
	Keypad_vInit();
	But_vInit('b',7);
	But_vInit('a',0);
	Servo_Motor_vSend_Degree(180);
	static unsigned char Number_tries=tries;
	static unsigned char flag;
	unsigned char entered_value,i=0;
    while(1)
    {
	   if (EEPROM_uRead(Status_Value_address)==0xff)
	   {
		   LCD_vSendString("set pass:");
		   for (i=0;i<4;i++)
		   {
			    while ((entered_value = Keypad_uRead()) == 0xFF);
				 if (entered_value!=0xff)
				 {
					LCD_vSendChar(entered_value);
					_delay_ms(500);
					LCD_vMoveCursor(1,10+i);
					LCD_vSendChar('*');
					EEPROM_vWrite(first_letter_address+i,entered_value);
				}			   
		   }
		   EEPROM_vWrite(Status_Value_address, 0x00);
		}	   
	   LCD_vClrscreen();
	   while (flag==0)
	   {	LCD_vSendString("check pass:");
			for (i=0;i<4;i++)
			{
				while (Keypad_uRead() == 0xFF);
				arr[i]=Keypad_uRead();
				LCD_vSendChar(arr[i]);
				_delay_ms(500);
				LCD_vMoveCursor(1,12+i);
				LCD_vSendChar('*');
			}		   
	   if ((arr[0]==EEPROM_uRead(first_letter_address))&&(arr[1]==EEPROM_uRead(second_letter_address))&&(arr[2]==EEPROM_uRead(third_letter_address))&&(arr[3]==EEPROM_uRead(fourth_letter_address)))
	   {
			 Servo_Motor_vSend_Degree(0);
			 LCD_vClrscreen();
			 LCD_vSendString("correct pass");
			 LCD_vMoveCursor(2,1);
			 LCD_vSendString("safe is open");
			 _delay_ms(1000);
			  LCD_vClrscreen();
			 LCD_vSendString("Close the safe");
			 _delay_ms(5000);
			 LCD_vClrscreen();
			flag=1;		
	   }
	   else 
	   {
		   LCD_vClrscreen();
		   LCD_vSendString("wrong pass");
		   LCD_vMoveCursor(2,1);
		   LCD_vSendString("safe is close");
		   _delay_ms(1000);
		   LCD_vClrscreen();
		   LCD_vSendString("tries number:");
		   LCD_vSendChar(Number_tries+48);
		   _delay_ms(1000);
		   LCD_vClrscreen();
		   Number_tries--;
		   if (Number_tries==0)
		   {
			   LCD_vClrscreen();
			   LCD_vSendString("Closed Safe");
			   LCD_vMoveCursor(2,1);
			   LCD_vSendString("wait 5 mins");
			   _delay_ms(5000);
			   LCD_vClrscreen();
		   }
	   }
	}			   	   	   	   
	   if (But_uRead('b',7,0)==1)
	   {
		   EEPROM_vWrite(Status_Value_address,0xff);
		   flag=0;
		   Servo_Motor_vSend_Degree(180);
		   _delay_ms(250);
	   }
	   if (But_uRead('a',0,0)==1)
	   {
		   Servo_Motor_vSend_Degree(180);
		   flag=0;
		   _delay_ms(250);
	   }
	}		
}
	
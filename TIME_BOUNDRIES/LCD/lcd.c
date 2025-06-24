#include "types.h"
#include "lcd_define.h"
#include <lpc21xx.h>
#include "delay.h"
void writeLCD(u8 byte)
{
	IOCLR0=1<<LCD_RW;
	IOPIN1=(IOPIN1&~(255<<LCD_DATA))|(byte<<LCD_DATA);
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;
        delay_ms(2);
}
void  cmdLCD(u8 cmd)
{
	 //select cmd register 
	 IOCLR0=1<<LCD_RS;
	 //WRITE TO CMD REG VIA I/O BUFFER
	 writeLCD(cmd);
}
void initLCD(void)
{
	//CFG P0.8 TO PO.18 GPIO PINS
	IODIR1=255<<LCD_DATA;
	IODIR0|=1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
	delay_ms(15);
	cmdLCD(0x30);
	delay_ms(2);
	cmdLCD(0x30);
	delay_us(100);
	cmdLCD(0x30);
	cmdLCD(MODE_8BIT_2LINE);
	cmdLCD(DSP_ON_CUR_ON);
	cmdLCD(CLEAR_LCD);
	cmdLCD(SHIFT_CUR_RIGHT);
}
void charLCD(u8 ascii)
{
	//select data
	IOSET0=1<<LCD_RS;
	//WRITE TO THE DDRAM VIA I/O BUFFER->DATAREG
	writeLCD(ascii);
}
void u32LCD(u32 n)
{
	s32 i=0;
        u8 a[10];
	if(n==0)
	{
           charLCD(0);
	}
	else
	{
		while(n)
		{
			a[i++]=(n%10)+48;
			n/=10;
		}
		for(--i;i>=0;i--)
		{
			charLCD(a[i]);	 
		}
	}
}
void strLCD(s8 *p)
{
      while(*p)
      charLCD(*p++);
}
/*void s32LCD(s32 n)
{
	if(n<0)
	{
		charLCD('-');
		n=-n;
	}
	u32LCD(n);
} */
/*void f32LCD(f32 n,u8 s)
{
	u32 d,i;
	if(n<0.0)
	{
		charLCD('-');
		n=-n;
	}
	d=n;
	u32LCD(d);
	charLCD('.');
	for(i=0;i<s;i++)
	{
		n=((n-d)*10);
		d=n;
		charLCD(d+48);
	}
} */

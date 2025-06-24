#include<lpc21xx.h>
#include<string.h>
#include "types.h"
#include "delay.h"	
#include "lcd.h"
#include "lcd_define.h"
#include "kpm.h"
#include "ADC.h"
#include "adc_define.h"
#include "rtc.h"
#include "rtc_defines.h"

#define ADMIN_SW 1
//const u8 kpmLUT[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
//const u8 kpmLUT[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'e','0','=','+'}};
const u8 kpmLUT[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'p','0','b','D'}};
void initKPM()
{
      IODIR1|=(15<<ROW0);
	IOCLR1=15<<ROW0;
}
u32 colSCAN()
{

return ((((IOPIN1>>COL0)&15)<15)?0:1);
}
u32 rowCHECK(void)
{
	u32 r;
	for(r=0;r<=3;r++)
	{
		IOPIN1=(IOPIN1&~(15<<ROW0))|(~(1<<r)<<ROW0);
		if(colSCAN()==0)
		{
			break;
		}
	}
	IOCLR1=15<<ROW0;
	return r;
}
u32 colCHECK()
{
		 u32 c;
		 for(c=0;c<=3;c++)
		 {
		     if(((IOPIN1>>(COL0+c))&1)==0)
			 {
			   break;
			   }
		 }
		 return c;
}
u32 keySCAN()
{
 u32 r,c;
 while(colSCAN());
 r=rowCHECK();
 c=colCHECK();
 while(!(colSCAN()));
  //delay_ms(50);
 return  kpmLUT[r][c];
  
}
/*int readNUM2(u32 *sum,u8 *key)
{
u8 flag=0,cnt=0;
while(1){
		 if(((IOPIN0>>ADMIN_SW)&1)==0)
		 { 
		    while(((IOPIN0>>ADMIN_SW)&1)==0);
			cnt++;
			if(cnt==3)
			{
		    goto label;
			}
		 }
}
cmdLCD(GOTO_LINE2_POS0);
while(1)
{
    *key=keySCAN();
	delay_ms(200);
	if((*key>='0')&&(*key<='9'))
	{
	charLCD(*key);
	if(flag==1)
	{
	delay_ms(50);
	cmdLCD(GOTO_LINE2_POS0+cnt);
	charLCD('*');
	cnt++;
	}
	*sum=(*sum*10)+(*key-48);
	//while(colSCAN()==0);
	}
	else{
	//while(colSCAN()==0);
	break;
	}
}
}  */
 void displaytemp()
{
        f32 ear;
		u16 dval;
	   READ_ADC(1,&dval,&ear);
	   cmdLCD(0x8b);
	 u32LCD(ear*100);
	 charLCD(223);
	 charLCD('c');
}
void readNUM(u32 *sum,u8 *key,unsigned int hex)
{
u8 flag=0;int cnt2=0;int i;
cmdLCD(hex);
if(*key=='z')
{
 flag=1;
}
while(1)
{
while(1)
{
a:displaytemp();
for(i=0;i<800000;i++){
      	if(colSCAN()==0)
	{
	  goto a2;
	}    
}
}
a2:    *key=keySCAN();
	delay_ms(200);
	if(*key=='b')
	{
	     *sum=*sum/10;
		  cnt2--;
		  if(cnt2<0) cnt2=0;
		 cmdLCD(hex+cnt2);
		 charLCD(' ');
		 cmdLCD(hex+cnt2);
	}
	
	else if((*key>='0')&&(*key<='9'))
	{
	if(cnt2==5)
	{
	cmdLCD(hex);
	strLCD("limit");
	delay_ms(500);
	strLCD("     ");
	cmdLCD(hex);
	if(flag!=1)
	u32LCD(*sum);
	else{		     
	for(i=0;i<cnt2;i++) charLCD('*');
	}
	goto a; 
	}
	cmdLCD(hex+cnt2);
    charLCD(*key);
	if(flag==1)
	{
	delay_ms(100);                                                                                                                                                                                                                                                 
	cmdLCD(hex+cnt2);
	charLCD('*');

	}
	cnt2++;
	*sum=(*sum*10)+(*key-48);
	//while(colSCAN()==0);
	}
	else{
	//while(colSCAN()==0);
	break;
	}
}
}

int readSTR(char *p)
{
  u8 key,j;
  int i;
  s32 hour,min,sec,dt,mo,yr;
  u32 cnt,cnt2;
  i=0;
  cnt=cnt2=0;
  Init_ADC();
  while(1){
//READ_ADC(1,&dval,&ear);
cmdLCD(0x01);
displaytemp();
for(j=0;j<120;j++){

cmdLCD(GOTO_LINE1_POS0);

GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
//strLCD("  ");
//u32LCD(ear*100);
//strLCD("'c");

GetRTCDateInfo(&dt,&mo,&yr);
cmdLCD(GOTO_LINE2_POS0);
DisplayRTCDate(dt,mo,yr);
charLCD(' ');
//GetRTCDay(&day)	 ;
//DisplayRTCDay(day);
		 if(((IOPIN0>>ADMIN_SW)&1)==0)
		 { 
           while(((IOPIN0>>ADMIN_SW)&1)==0);
			cnt++;
			if(cnt==3)
			{
		    return 3;
			}
		 }
		 if((colSCAN())==0)
		 {
		  goto option;
		 }
		 }
}
myoption:
while(1)
{
	displaytemp();
	for(j=0;j<40000;j++) {
    if(((IOPIN0>>ADMIN_SW)&1)==0)
    {
	cnt++;
	 while(((IOPIN0>>ADMIN_SW)&1)==0);
	 //charLCD(' ');
	 //u32LCD(cnt);
	 delay_ms(100);
	 //cnt++;
	  if(cnt==3)
	{
	return 3;
	}
	}
	if(colSCAN()==0)
	{
     	cnt=0;
	  goto option2;
	} 
	}
}
 option: cmdLCD(0x01);
  cmdLCD(GOTO_LINE1_POS0);
  strLCD("userid");
  while(1){
     //cmdLCD(0xcb);
option2:     
	// u32LCD(ear*100);
    //strLCD("'c");
	//cmdLCD(GOTO_LINE2_POS0);
    key=keySCAN(); 
    delay_ms(200);
	if(key=='b')
	{
	i--;
	if(i<0) i=0;
	cmdLCD(0xc0+i);
	  charLCD(' ');
      cmdLCD(0xc0+i);
	 //goto myoption;
	}
  else if((key>='0'&&key<='9')||(key>='A'&&key<='D'))
  {
  
    if(i==5){
	cmdLCD(0xc0);
	strLCD("max limit");
	delay_ms(500);
    cmdLCD(0xc0);
	strLCD("         ");
	cmdLCD(0xc0);
	strLCD((u8*)p);
	//goto myoption;
	}
	else{
     cmdLCD(0xc0+i);
	 charLCD(key);
		 cnt2++;
	p[i++]=key;
	}
	 //goto myoption; 
  }
  else{
   p[i]='\0';
       return 0;
     }
	 goto myoption; 
  }
    
}
void readSTR2(char *p,unsigned int hex)
{
  u8 key,j;
  int i;
  i=0;			
  while(1){
     //READ_ADC(1,&dval,&evar);	 
	 while(1)
{
	displaytemp();
	for(j=0;j<40000;j++) {
	if(colSCAN()==0)
	{
 
	  goto option2;
	} 
	}
}
 option2:
  key=keySCAN(); 
  delay_ms(200);
  if(key=='b')
  {
      i--;
	  if(i<0) i=0;
     cmdLCD(0xc0+i);
	  charLCD(' ');
      cmdLCD(0xc0+i);
	  
  }
 else if((key>='0'&&key<='9')||(key>='A'&&key<='D'))
  {
  	//displaytemp();
  if(i==5){	
	cmdLCD(hex);
	strLCD("max limit");
	delay_ms(500);
	cmdLCD(hex);
	strLCD("         ");
	cmdLCD(hex);
	strLCD((u8*)p);
	displaytemp();
	continue;
	}
    cmdLCD(hex+i);
	p[i++]=key;
    charLCD(key);

  }
  else{
   p[i]=0;
       break;
     } 
  }
}

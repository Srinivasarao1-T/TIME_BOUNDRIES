#include<lpc21xx.h>
#include "delay.h"
#include "lcd_define.h"
#include "lcd.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "types.h"
#include "kpm.h"
#include "pro.h"
#include<string.h>
#define REDLED 6
#define GREENLED 5
char p[6];
main()
{
int i,res=0;
u32 sum;
u8 key;
obj arr[4]={{"User1","1111",1234,9,0,11,0},{"User2","2222",2345,12,0,14,0},{"User3","3333",3456,15,0,17,0},{"Admin","AAAA",5555,0,0,23,59}};
initLCD();										  
RTC_Init();
initKPM();
IODIR0|=1<<REDLED|1<<GREENLED;
IOSET0=1<<REDLED;
IOCLR0=1<<GREENLED;
SetRTCTimeInfo(9,5,0);
SetRTCDateInfo(19,6,2025);
label1:		 while(1){ 
		   res=readSTR(p);
		   if(res==3)
		   {
		      goto label;
		   }
		   for(i=0;i<3;i++)
		   {
		   if((strcmp(arr[i].userid,p))==0)  break;
		   }
		    if(i==3)
			{
	            goto not;		  
			}
			sum=0;key='z';
			cmdLCD(0x01);
			 cmdLCD(0x80);
			 strLCD("enter pwd");
			 readNUM(&sum,&key,0xc0);
			 
			 for(i=0;i<3;i++)
			  {
				   if(sum==arr[i].num)
				   { 
				      if(((HOUR>=arr[i].inhr)&&(HOUR<=arr[i].outhr))){
				       	cmdLCD(0x01);
			            cmdLCD(0x80);
			            strLCD("Thankyou");
			            cmdLCD(0xc0);
				       strLCD(" login is sucess ");
					   IOSET0=1<<GREENLED;
					   delay_ms(1000);
					   IOCLR0=1<<GREENLED;
					   goto label1;
					   }
					   else{
					   cmdLCD(0x01);
				       cmdLCD(GOTO_LINE1_POS0);
				       strLCD(" time_bounded ");
				       cmdLCD(0xc0);
				       charLCD(((arr[i].inhr)/10)+48);
				       charLCD(((arr[i].inhr)%10)+48);
				       charLCD(':');
				       charLCD(((arr[i].inmin)/10)+48);
				       charLCD(((arr[i].inmin)%10)+48);
				       strLCD("to");
				       charLCD(((arr[i].outhr)/10)+48);
				       charLCD(((arr[i].outhr)%10)+48);
				       charLCD(':');
				       charLCD(((arr[i].outmin)/10)+48);
				       charLCD(((arr[i].outmin)%10)+48);
				       goto not;
					   }
				   }	  
			 }
not:			 IOCLR0	=1<<REDLED;
			 if(i==3) 
			 {
			  cmdLCD(0x01);
			  cmdLCD(0x80);
			  strLCD("login fail");
			  cmdLCD(0xc0);
			  strLCD("try again");
			 }
			 delay_ms(1000);
			 IOSET0=1<<REDLED;
			 goto label1;                                             
         }
label:	     	cmdLCD(0x01);
			 cmdLCD(0x80);
			 strLCD("adminid");
             readSTR2(p,0xc0);
			 if(strcmp(arr[3].userid,p)!=0)
				  {
				  cmdLCD(0xc0);
				  strLCD("wrong id");
				  goto  label1;
				  }
			 sum=0;key='z';
                         cmdLCD(0x01);
			 cmdLCD(0x80);
			 strLCD("enter pwd");			 
			 readNUM(&sum,&key,0xc0);     
				   if(sum==arr[3].num)
				   { 
				       cmdLCD(0x01);
			           cmdLCD(0x80);
			           strLCD("Thankyou");
			           cmdLCD(0xc0);
				       strLCD(" login is sucess ");
					   IOSET0=1<<GREENLED;
					   delay_ms(1000);
                                           IOCLR0=1<<GREENLED;   
					    goto time;
				   }
                IOCLR0=1<<REDLED;
			    cmdLCD(0x01);
			    cmdLCD(0x80);
			    strLCD("login fail");
			    cmdLCD(0xc0);
			   strLCD("try again");
			  delay_ms(1000);
			 IOSET0=1<<REDLED;
			 goto label1;
time:  cmdLCD(CLEAR_LCD);
       cmdLCD(GOTO_LINE1_POS0);  
	   strLCD("1.TME 2.DT");

	   cmdLCD(0x87);
	   displaytemp();
	   cmdLCD(GOTO_LINE2_POS0);
       strLCD("3.BND 4.EX:");
	   delay_ms(500);
	   key=sum=0;
	   readNUM(&sum,&key,0xcb);       
       switch(sum)
	   {  case 1:timechange();
	              goto time;
	      case 2:changedate(); 
				 goto time;
	      case 3:timebund(arr);
		         goto time;
		  case 4:goto label1;
		  default:cmdLCD(CLEAR_LCD);
                  cmdLCD(GOTO_LINE1_POS0);
		          strLCD("wrong option");
				  delay_ms(500);
				  goto time;
	   }
}

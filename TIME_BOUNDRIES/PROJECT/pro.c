#include<lpc21xx.h>
#include "delay.h"
#include "lcd.h"
#include "lcd_define.h"
#include "kpm.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "adc.h"
typedef struct 
{ 
   char name[6];
   char userid[6];
   int num;
   int inhr;
   int inmin;
   int outhr;
   int outmin;   	   
}obj;
void timechange()
{
	 u32 sum;
	 u8 key;
jump: cmdLCD(0x01);
	 cmdLCD(0x80);
	 strLCD("1.H 2.M");
	 cmdLCD(0xc0);
	 sum=key=0;
     readNUM(&sum,&key,0xc0);
	 switch(sum){
hrs :   case 1:    cmdLCD(0x01);
	      cmdLCD(0x80);	  

	   strLCD("enter hrs");
	   cmdLCD(0xc0);
      sum=key=0;
       readNUM(&sum,&key,0xc0);
        if(sum<=23)
		{
		HOUR=sum;
		}
		else{
		cmdLCD(0xc0);
		strLCD("wrong input");
		goto hrs; 
	}
	  break;
 min: case 2:  cmdLCD(0x01);
	 cmdLCD(0x80);	  
	   strLCD("enter min");
       sum=key=0;
       readNUM(&sum,&key,0xc0);
        if(sum<=59)
		{
	    MIN=sum;
		}
		else
		{
			cmdLCD(0xc0);
		strLCD("wrong input");
		goto min; 
		}
		delay_ms(500);
		break;
	default:cmdLCD(0x01);
	      cmdLCD(0x80);
		  strLCD("worng input");
		  delay_ms(500);
		  goto jump;	
 }	     
}
int checkleap(u32 n)
{
    if(n%4==0)
	{
	    if(n%400==0)
		{
		 return 1;
		}
		if(n%100==0)
		{
		   return 0;
		}
		  return 1;
	}
	return 0;
}
void changedate()
{
       u32 sum;
	   u8 key;
	   int day;
	   u32 flag=0,flag2;
y:	   cmdLCD(0x01);
	   cmdLCD(0x80);
	//   READ_ADC(1,&dval,&ear);
	   strLCD("1.y 2.m ");	   
	   cmdLCD(0xc0);
	  strLCD("3.d");
	   displaytemp();
	   sum=key=0;
	   readNUM(&sum,&key,0xc5);
	   switch(sum){	  
	           case 1:  cmdLCD(0x01);
			            cmdLCD(0x80);       
			            strLCD("ent yr");
                        sum=key=0;
                        readNUM(&sum,&key,0xc0);
		                delay_ms(500);
	                    YEAR=sum;
						break;
	           case 2:	 if(checkleap(YEAR)){
							flag=1;
		                  }
						  day =DOM;
m:                        cmdLCD(0x01);
		                  cmdLCD(0x80);	  
                          strLCD("ent mon");
                          sum=key=0;
                          readNUM(&sum,&key,0xc0);
		                if((sum==1)||(sum==3)||(sum==5)||(sum==7)||(sum==8)||(sum==10)||(sum==12)) 
	                     {
	                       if(day>=1&&day<=31)
						   {
						    MONTH=sum;
						   }
						   else goto pos;

	                     }
	                   else if((sum==4)||(sum==6)||(sum==9)||(sum==11)) 
	                     {
						 if(day>=1&&day<=30)
						 {
						  MONTH=sum;
						 }
						 else goto pos;
	                     }
	                    else if((sum==2)&&flag==1)
	                     {
						     if(day>=1&&day<=29)
							 {
							    MONTH=sum;
							 }
							 else goto pos;
						 }
						 else if(sum==2)
						 {
						     if(day>=1&&day<=28)
							 {
							 MONTH =sum;
							 }
							 else goto pos;
						 }
	                  
	 				 else{
	            pos:            cmdLCD(0x01);
	                        cmdLCD(0xc0);
		                    strLCD("wrong input");
			                delay_ms(500);
		                     goto m;
	                        }
						  break;
			case 3:		if(checkleap(YEAR)){
							flag=1;
		                  }	  		
  d:                    if((sum>=1&&sum<=12))
		                 {
	                    	MONTH=sum;
		                if((sum==1)||(sum==3)||(sum==5)||(sum==7)||(sum==8)||(sum==10)||(sum==12)) 
	                     {
	                       flag2=31;
	                     }
	                   if((sum==4)||(sum==6)||(sum==9)||(sum==11)) 
	                     {
	                    flag2=30;
	                     }
	                    if((sum==2)&&flag==1)
	                     {
	                    flag2=29;
	                     }
	                     }
	                     else{
	                     flag2=28;
	                      }  
                        cmdLCD(0x01);  	   
                        cmdLCD(0x80);	  
                        strLCD("ent day");
                        sum=key=0;
                        readNUM(&sum,&key,0xc0);
	                    if((sum>=1&&sum<=flag2))
			           {
			            DOM=sum;
		             	}
			           else{
				      cmdLCD(0x01);
			  	      cmdLCD(0xc0);
		              strLCD("wrong input");
			          delay_ms(500);
			          goto d;
			           }
					   break;
			  default: cmdLCD(0x01);
			           cmdLCD(0x80);
					   strLCD("wrong input");
					   delay_ms(500);
					   goto y;
			}
}
void  changebund(int a,obj *arr){ 
            u32 sum;
			u8 key,flag=0;
			cmdLCD(0x01);
			cmdLCD(0x80);
			strLCD("1.intime");
			cmdLCD(0xc0);
			strLCD("2.outtime:");
			readNUM(&sum,&key,0xca);
			switch(sum){
      one:               case 1: cmdLCD(CLEAR_LCD);
                                   cmdLCD(GOTO_LINE1_POS0);
		                           strLCD("ent inhr");
								   cmdLCD(0xc0);
	                               strLCD("1hr gap:");
        	                        sum=key=0;
			                        readNUM(&sum,&key,0xc8);
		                        	if(sum<=23)
		                         	arr[a].inhr=sum;
		 	                        else {cmdLCD(0xc0);strLCD("invalidoption");delay_ms(500);goto one;};
			                       delay_ms(500);
	two:	                       cmdLCD(0x01);
		                           cmdLCD(0x80);
			                       strLCD("ent inmin");
			                       sum=key=0;
	                         	   readNUM(&sum,&key,0xc0);
			                        if(sum<=59)
			                        arr[a].inmin=sum;
			                        else {cmdLCD(0xc0);strLCD("invalidoption");delay_ms(500);goto two;};
			                        delay_ms(500);
									break;
     three:               case 2 :cmdLCD(0x01);
			                     cmdLCD(0x80);
			                    strLCD("ent outhr");
								cmdLCD(0xc0);
								strLCD("1hr gap:");
        	                    sum=key=0;
			                    readNUM(&sum,&key,0xc8);
		                        if((sum>=arr[a].inhr)&&sum<=23)
			                    arr[a].outhr=sum;
		                      	else {cmdLCD(0x01);cmdLCD(0xc0);strLCD("invalidoption");delay_ms(500);goto three;};
		                     	if(sum==arr[a].inhr) flag=1;
		                     	delay_ms(500);
     four:	                   cmdLCD(0x01);
			                   cmdLCD(0x80);
			                   strLCD("ent outmin");
                            	sum=key=0;
                               readNUM(&sum,&key,0xc0);
                               if(flag==1){
				               if((sum>=arr[a].inmin)&&(sum<=59))
				     	    	arr[a].outmin=sum;
				                else {cmdLCD(0x01);cmdLCD(0xc0);strLCD("invalidoption");delay_ms(500);goto four;};
	                          		}
		                      	else{ 
		                     	if(sum<=59)
			                   arr[a].outmin=sum;
			                 else {cmdLCD(0xc0);strLCD("invalidoption");delay_ms(500);goto four;};
		                     	}
			                     }
			                  delay_ms(500);
							  }   
void timebund(obj *arr)
{
   u32 sum;u8 key;
  pos: cmdLCD(CLEAR_LCD);
   cmdLCD(GOTO_LINE1_POS0);
 //  READ_ADC(1,&dval,&ear);
   strLCD("1.u1 2.u2");  
   displaytemp();
   cmdLCD(0xc0);
   strLCD("3.u3 :");
   sum=key=0;
   readNUM(&sum,&key,0xc7);
   switch(sum)
   {
     case 1:changebund(0,arr);break;
	 case 2:changebund(1,arr);break;           
	 case 3:changebund(2,arr);break;
	 default:cmdLCD(0xc0);
	       strLCD("invalid option");
		   delay_ms(500);
		   goto pos; 
   }
}  

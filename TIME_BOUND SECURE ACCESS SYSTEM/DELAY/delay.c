#include "types.h"
#include "delay.h"
void delay_us(u32 delayMs)
 {
 //unsigned int i;
    // for(i=500;i>0;--i);
         delayMs*=12;                              //1Ms
         while(delayMs--);
 }
 void delay_ms(u32 delayms)
 {
       delayms*=12000;                   //1ms
           while(delayms--);
 }
 /*void delay_s(u32 delays)
{
       delays *= 12000000;// 1s
           while(delays--);
}  */

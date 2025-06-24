#ifndef _PRO_H_
#define _PRO_H_
#include "types.h"
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
void timechange(void);
int checkleap(u32 n);
void changedate(void);
void  changebund(int a,obj *arr);  
void timebund(obj *arr);
#endif

#include <LPC21xx.h>

#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "lcd_define.h"

unsigned char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
  // Disable & Reset the RTC 
	CCR = RTC_RESET;
  // Set prescaler integer part
	PREINT = PREINT_VAL;
	// Set prescaler fractional part
	PREFRAC = PREFRAC_VAL;
  // Enable the RTC
	CCR = RTC_ENABLE|RTC_CLKRTC;
}

void GetRTCTimeInfo(s32 *hr,s32 *mi,s32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;
}											          

void DisplayRTCTime(u32 hr,u32 mi,u32 se)
{
	//cmdLCD(GOTO_LINE1_POS0);
	charLCD((hr/10)+48);
	charLCD((hr%10)+48);
	charLCD(':');
	charLCD((mi/10)+48);
	charLCD((mi%10)+48);
	charLCD(':');
	charLCD((se/10)+48);
	charLCD((se%10)+48);
	
}

void GetRTCDateInfo(s32 *dt,s32 *mo,s32 *yr)
{
	*dt = DOM;
	*mo = MONTH;
	*yr = YEAR;
	
}
void DisplayRTCDate(u32 dt,u32 mo,u32 yr)
{
	//cmdLCD(GOTO_LINE2_POS0);
	charLCD((dt/10)+48);
	charLCD((dt%10)+48);
	charLCD('/');
	charLCD((mo/10)+48);
	charLCD((mo%10)+48);
	charLCD('/');
	u32LCD(yr);
	
	
}
// RTC_SetTime: Sets the time and date on the RTC
void SetRTCTimeInfo(u32 hour, u32 min, u32 sec) 
{
	// Set hours
	HOUR = hour;  
  // Set minutes
	MIN = min;
	// Set seconds
	SEC = sec;
}

void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
	
}

void GetRTCDay(s32 *day)
{
	*day = DOW;
}
void DisplayRTCDay(u32 day)
{
	strLCD(week[day]);
}
/*void SetRTCDay(u32 day)
{
	DOW = day;
}*/



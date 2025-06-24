#ifndef _KPM_H_
#define _KPM_H_
#define ROW0 24
#define COL0 28
void initKPM(void);
u32 colSCAN(void);
u32 rowCHECK(void);
void displaytemp(void);
u32 keySCAN(void);
void readNUM(unsigned int *sum,unsigned char *key,unsigned int);
int readSTR(char*);
void readSTR2(char *p,unsigned int hex);
#endif

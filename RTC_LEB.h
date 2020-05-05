#ifndef RTC_LEB_H
#define RTC_LEB_H
#include"Wire.h"



class DS1307
{
public:
int DS1307_address, Clock_Mode_Bit;

    
    
   
    public:
	char BCD_To_Decimal(char BCD);
	char Decimal_To_BCD(char dec);
	char getSec();
	char getMin();
	char getHour();
	char getdayofweek();
	char getDate();
	char getMonth();
	char getYear();
        void Clock_Mode(uint8_t Mode);
        char Find_AM_PM();
        void Set_AM_PM(uint8_t Data);	
void setTime(char Sec, char Min, char Hour, char dayOftheweek, char Date, char Month, char Year);
          
};
#endif



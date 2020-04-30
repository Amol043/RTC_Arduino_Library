#ifndef RTC_LEB_H
#define RTC_LEB_H
#include"Wire.h"
#define Address 0x68
class DS1307
{
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
	void setTime(char Sec, char Min, char Hour, char dayOftheweek, char Date, char Month, char Year);

};
#endif



#include "RTC_LEB.h"

    //funtion convert BCD format value to Decimal
	char DS1307::BCD_To_Decimal(char BCD){
	    return( (BCD/16*10) + (BCD%16) );
	}

	char DS1307::Decimal_To_BCD(char dec){
	    return( (dec/10*16) + (dec%10) );
	}

	//Function return Seconds value in decimal format
	char DS1307::getSec()
	{
	    Wire.beginTransmission(Address);
	    Wire.write(0);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);

	    return(BCD_To_Decimal(Wire.read() & 0x7f));
	}

	//Function return Minutes value in decimal format
	char DS1307::getMin()
	{
	    Wire.beginTransmission(Address);
	    Wire.write(1);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);

	    return(BCD_To_Decimal(Wire.read() & 0x7f));
	}

	//Function return hour value in decimal format
	char DS1307::getHour()
	{
	    Wire.beginTransmission(Address);
	    Wire.write(2);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);

	    return (BCD_To_Decimal(Wire.read() & 0xff));
	}

	char DS1307::getdayofweek()
	{
	    Wire.beginTransmission(Address);
	    Wire.write(3);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);
	    return(BCD_To_Decimal(Wire.read() & 0x0f));

	}

	char DS1307::getDate()
	{
	    Wire.beginTransmission(Address);
	    Wire.write(4);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);
	    return (BCD_To_Decimal(Wire.read()));
	}

	char DS1307::getMonth(){
	    Wire.beginTransmission(Address);
	    Wire.write(5);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);
	    return(BCD_To_Decimal(Wire.read()));
	}

	char DS1307::getYear(){
	    Wire.beginTransmission(Address);
	    Wire.write(6);
	    Wire.endTransmission();

	    Wire.requestFrom(Address,1);
	    return(BCD_To_Decimal(Wire.read()));
	}
	void DS1307::setTime(char Sec, char Min, char Hour, char dayOftheweek, char Date, char Month, char Year)
	{

	    Wire.beginTransmission(Address);
	    Wire.write(0);                             //Start writting values from Rigister number 0
	    Wire.write(Decimal_To_BCD(Sec));           //set Seconds
	    Wire.write(Decimal_To_BCD(Min));           // set Minute
	    Wire.write(Decimal_To_BCD(Hour));          // set hour
	    Wire.write(Decimal_To_BCD(dayOftheweek));  // set day of week (1=Sunday, 7=Saturday)
	    Wire.write(Decimal_To_BCD(Date));          // set the Date
	    Wire.write(Decimal_To_BCD(Month));         // set month
	    Wire.write(Decimal_To_BCD(Year));          // set year (0 to 99)
	    Wire.endTransmission();
	}

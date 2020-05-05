#include "RTC_LEB.h"


//funtion convert BCD format value to Decimal
char DS1307::BCD_To_Decimal(char BCD){
    return( (BCD/16*10) + (BCD%16) );
}

char DS1307::Decimal_To_BCD(char dec){
    return( (dec/10*16) + (dec%10) );
}

void DS1307::Set_AM_PM(uint8_t Data)
{

    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address,1);

    uint8_t byte_data;

    if(Data)
    byte_data = Wire.read() | 0x20;
    else 
    byte_data = Wire.read() & 0x5f;

    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    
    Wire.write(byte_data);
    Wire.endTransmission();
}

/*char DS1307::check()
{
    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address,1);
    uint8_t byte_data = BCD_To_Decimal(Wire.read() & 0x6f);
    return byte_data;
}*/
char DS1307::Find_AM_PM()
{

    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    char bit = BCD_To_Decimal((Wire.read() & (1 << 5)) >> 5);

    return bit;
}
void DS1307::Clock_Mode(uint8_t Mode)
{
    Clock_Mode_Bit = Mode;

    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address,1);
    uint8_t byte_data = Wire.read();

    Wire.beginTransmission(DS1307_address); 
    Wire.write(2);

    if(Mode)
    Wire.write(byte_data | (1 << 6));
    else
    Wire.write(byte_data & 0x3F);

    Wire.endTransmission();
}

//Function return Seconds value in decimal format
char DS1307::getSec()
{
    Wire.beginTransmission(DS1307_address); //At starting send address of that device you want to communicate and read/write the data
    Wire.write(0);                          //send register number which mention in timerkeeper register table
    Wire.endTransmission();                 //End the trasmitor data operation by master

    Wire.requestFrom(DS1307_address, 1);      //Now master in reciver mode and request data from slave device

    return(BCD_To_Decimal(Wire.read() & 0x7f)); //Read the data from slave and "AND" with specific value bez Seconds value present in 7 bit(As mentioned in Timekeeper register table) so After convert to decimal format
}

//Function return Minutes value in decimal format
char DS1307::getMin()
{
    Wire.beginTransmission(DS1307_address);
    Wire.write(1);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);

    return(BCD_To_Decimal(Wire.read() & 0x7f));
}

//Function return hour value in decimal format
char DS1307::getHour()
{
    Wire.beginTransmission(DS1307_address);
    Wire.write(2);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    
    if(Clock_Mode_Bit)                                   //if clock Mode is 12 then Condition true
    return BCD_To_Decimal(Wire.read() & 0x1F);
    else
    return BCD_To_Decimal(Wire.read() & 0x3F);
}

//function of get day of week value from perticular registor and return in decimal format
char DS1307::getdayofweek()
{
    Wire.beginTransmission(DS1307_address);
    Wire.write(3);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    return(BCD_To_Decimal(Wire.read() & 0x0f));

}

//function of get Date value from perticular registor and return in decimal format
char DS1307::getDate()
{
    Wire.beginTransmission(DS1307_address);
    Wire.write(4);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    return (BCD_To_Decimal(Wire.read()));
}

//function of get Month value from perticular registor and return in decimal format
char DS1307::getMonth(){
    Wire.beginTransmission(DS1307_address);
    Wire.write(5);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    return(BCD_To_Decimal(Wire.read()));
}
//function of get year value from perticular registor and return in decimal format
char DS1307::getYear(){
    Wire.beginTransmission(DS1307_address);
    Wire.write(6);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_address, 1);
    return(BCD_To_Decimal(Wire.read()));
}
//function of Set time of RTC by user, Note: Don't call this function in void loop call in void setup
void DS1307::setTime( char Sec, char Min, char Hour, char dayOftheweek, char Date, char Month, char Year)
{

    Wire.beginTransmission(DS1307_address);    //At stating send the device address from that device we want communicate
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

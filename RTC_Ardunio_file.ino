#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTC_LEB.h>
 
#define Add 0x68                                          //Address of the Device (RTC DS1307) mentioned in datasheet

byte flag;
String Comb_Date_month_year;          
String Comb_Time;
byte  Mode = 1;
LiquidCrystal_I2C lcd(0x3F,16, 2); //One type of construtor ):

char dayoftheweek[7][4] = {"Son","Mon","Tue","Wed","The","Fri","Sat"};


DS1307 rtc;                                                     //Create object of Class, using this object we call function of class
void setup() {
  lcd.begin();             
  Wire.begin();                                                 // initiate the wire library this library all I2C Function are define
  Serial.begin(9600);                                           // start serial for output
  rtc.DS1307_address = Add;                                     //Intialize address using class object
    
  //rtc.setTime(-Seconds-, -Minutes- , -Hour-,-dayOftheweek-, -Date- ,-Month- , -Year-); //Set time if you want,after that RTC maintain time from sete time 
  //Ex;-rtc.setTime(55,45,11,1,4,5,20);                               //Set time and Date as above line format
   //  rtc.Clock_Mode(Mode);                                         //Set Clock Mode if "1" then 12 hour mode, if its "0" then its 24 hour mode. 
    // rtc.Set_AM_PM(Mode);                                          //If you pass 1 as parameter then it set as PM if parameter is 0 then its "AM" 
  //Note :- setTime ,Clock_mode and Set_AM_PM Function don't call in void loop. 
}


void loop() {
    
  byte Day = rtc.getdayofweek();
      
  lcd.print(dayoftheweek[Day]);
  
  byte Date = rtc.getDate();
  
  byte Mon = rtc.getMonth();
  
  byte Year = rtc.getYear();
  
  Comb_Date_month_year = String (Date) + String ("/") + String (Mon) + String ("/") + String (Year);
  lcd.print(Comb_Date_month_year);
  
  lcd.setCursor(0,1);
  lcd.print("Time:");
  
  byte Hour = rtc.getHour();
  
  byte Minute = rtc.getMin();
  
  byte Seconds = rtc.getSec();
  Comb_Time = String(Hour) + String (":")  + String (Minute) + String (":") + String (Seconds);

  if(flag = rtc.Find_AM_PM())
   Comb_Time += String (" PM");
   else
   Comb_Time += String (" AM");

   if(Seconds == 0)
   {lcd.setCursor(14,1);
   lcd.print("    ");
   }
   
   lcd.print(Comb_Time);
 
  lcd.setCursor(0,0);  
}

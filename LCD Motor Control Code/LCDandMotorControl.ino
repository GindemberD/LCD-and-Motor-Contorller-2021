
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"

//LCD and RTC Defining variables

RTC_DS3231 rtc;

char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int Day; 
int Month;
int Year; 
int Secs;
int Minutes;
int Hours;

String dofweek; // day of week

String myDate; 
String myTime; 

// for the 16x2 LCD

const int rs = 2, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//////////////////////////////////////////////////////////////
// Motor Control Variables 
//////////////////////////////////////////////////////////////

int Speed = 3;

int pushButton = 6;
int buttonState;
int toggle,toggleFull, toggleHalf, toggleStop;
int pushButtonFull = 22;
int stateFull;
int pushButtonHalf = 24;
int stateHalf;
int pushButtonStop = 26;
int stateStop;

int input1 = 4;
int input2 = 5;
int mSpeed;

String CW = "CW";
String CCW = "CCW";
String fast = "Full";
String mid = "1/2";
String stopped = "0";

String rotation;
String rotationSpeed;
void setup() {


  ////////////////////////////////////////
  //-------Setting Time and Date--------
  ////////////////////////////////////////
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear(); 
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
  



  
  // put your setup code here, to run once:
  pinMode(Speed,OUTPUT);
  pinMode(pushButton,INPUT);
  pinMode(pushButtonFull,INPUT);
  pinMode(pushButtonHalf,INPUT);
  pinMode(pushButtonStop,INPUT);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);

  Serial.begin(9600);

  buttonState = digitalRead(pushButton);
  delay(1);
  Serial.println(buttonState);
  toggle = 0;
  toggleFull = 0;
  toggleHalf = 0;
  toggleStop = 1;

}

void loop() {
  while(toggle == 0){
    if(toggleFull == 1 ){
      mSpeed = 255;
      analogWrite(Speed,200);
    }
    if(toggleHalf == 1 && toggleFull == 0 && toggleStop == 0){
      mSpeed = 130;
      analogWrite(Speed,200);
    }
    if (toggleStop == 1){
      mSpeed = 0;
      analogWrite(Speed,0);
    }
    
    digitalWrite(input1,HIGH);
    digitalWrite(input2,LOW);
   // analogWrite(Speed,mSpeed);
    
    

    //////////////////////////////////////
    //Printing to LCD 
    //////////////////////////////////////

    DateTime now = rtc.now();
    lcd.clear();        
    Day = now.day(); 
    Month = now.month(); 
    Year = now.year();
    Secs = now.second(); 
    Hours = now.hour(); 
    Minutes = now.minute(); 
    dofweek = daysOfTheWeek[now.dayOfTheWeek()];  

    if(toggleFull == 1){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " "+ CW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " " + "Full" ; 
    }
    if(toggleHalf == 1 && toggleFull == 0 && toggleStop == 0){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " " + CW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " "+ "1/2" ; 
    }
    if (toggleStop == 1 && toggleFull == 0 && toggleHalf == 0){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " " + CW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " " + "0" ; 
    }

  
   
    // send to serial monitor
    Serial.println(dofweek); 
    Serial.println(myDate); 
    Serial.println(myTime);
    //Print on lcd
    lcd.setCursor(0,0);
    lcd.print(myDate); 
    lcd.setCursor(0,1); 
    lcd.print(myTime); 
    myDate = "";   
    myTime = ""; 
    delay(1000);

    stateFull = digitalRead(pushButtonFull);
    delay(1);
    if(stateFull == 1){
      toggleFull = 1;
      toggleHalf = 0;
      toggleStop =0;
    }
    stateHalf = digitalRead(pushButtonHalf);
    if(stateHalf == 1){
      toggleFull = 0;
      toggleHalf = 1;
      toggleStop =0;
      Serial.println(toggleHalf);
    }
    stateStop = digitalRead(pushButtonStop);
    if(stateStop == 1){
      toggleFull = 0;
      toggleHalf = 0;
      toggleStop = 1;
      
    }
      





    buttonState = digitalRead(pushButton);
    if(buttonState == 1){
      toggle = 1;
    }

    while(toggle == 1){
      
      if(toggleFull == 1 ){
      mSpeed = 255;
      analogWrite(Speed,200);
      }
      if(toggleHalf == 1 && toggleFull == 0 && toggleStop == 0){
      mSpeed = 130;
      analogWrite(Speed,200);
      }
      if (toggleStop == 1){
      mSpeed = 0;
      analogWrite(Speed,0);
      }
      
      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);

    //////////////////////////////////////
    //Printing to LCD 
    //////////////////////////////////////

    DateTime now = rtc.now();
    lcd.clear();        
    Day = now.day(); 
    Month = now.month(); 
    Year = now.year();
    Secs = now.second(); 
    Hours = now.hour(); 
    Minutes = now.minute(); 
    dofweek = daysOfTheWeek[now.dayOfTheWeek()];  

    if(toggleFull == 1){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " "+ CCW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " " + "Full" ; 
    }
    if(toggleHalf == 1 && toggleFull == 0 && toggleStop == 0){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " " + CCW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " "+ "1/2" ; 
    }
    if (toggleStop == 1 && toggleFull == 0 && toggleHalf == 0){
      myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year + " " + CCW ; 
      myTime = myTime + Hours +":"+ Minutes +":" + Secs + " " + "0" ; 
    }

   // myDate = myDate +dofweek+ " "+ Day + "/" + Month + "/" + Year ; 
  //  myTime = myTime + Hours +":"+ Minutes +":" + Secs + fast + " " + CCW ; 
    // send to serial monitor
    Serial.println(dofweek); 
    Serial.println(myDate); 
    Serial.println(myTime);
    //Print on lcd
    lcd.setCursor(0,0);
    lcd.print(myDate); 
    lcd.setCursor(0,1); 
    lcd.print(myTime); 
    myDate = "";   
    myTime = ""; 
    delay(1000);


    stateFull = digitalRead(pushButtonFull);
    delay(1);
    if(stateFull == 1){
      toggleFull = 1;
      toggleHalf = 0;
      toggleStop =0;
    }
    stateHalf = digitalRead(pushButtonHalf);
    if(stateHalf == 1){
      toggleFull = 0;
      toggleHalf = 1;
      toggleStop =0;
      Serial.println(toggleHalf);
    }
    stateStop = digitalRead(pushButtonStop);
    if(stateStop == 1){
      toggleFull = 0;
      toggleHalf = 0;
      toggleStop = 1;
      
    }

    buttonState = digitalRead(pushButton);
    if(buttonState == 1){
      toggle = 0;
    }
    }

    
  }
  


}

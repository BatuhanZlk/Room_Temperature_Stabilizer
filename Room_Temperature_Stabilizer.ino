/*
 Project        : ROOM TEMPERATURE STABILIZER
 Author         : Batuhan Zülkadiroğlu
 Number         : 151220202087
 --------------------------------------------------------------
 Purpose        : Keeping the room temperature at the ideal level.
 --------------------------------------------------------------
 System Work    : Room temperature is measured with DHT11. If this temperature value is above 24 degrees,
 the dc motor runs and the room temperature is lowered below 24 degrees again with the help of the propeller
 connected to the dc motor. At the same time, the values are displayed to the user via the LCD screen.
---------------------------------------------------------------          
*/


#include<LiquidCrystal_I2C.h> //I used I2C module with this library
#include <DHT.h> //I used DHT module with this library
#define motor 3 //Motor is connected to Digital pin 3
#define DHTPIN 5 //DHT is connected to Digital pin 5
#define DHTTYPE DHT11 //I specified the type of DHT module
DHT dht(DHTPIN,DHTTYPE); //I created an object named dht and specified that this object is the model and pin above

LiquidCrystal_I2C lcd(0x27 ,16, 2);
void setup() {
  pinMode(motor,OUTPUT);
  dht.begin();//DHT11 sensor is activated
  Serial.begin(9600);//I set the baud rate for serial data transmission
  lcd.init();//initialize the lcd
  lcd.backlight();//I turned on the blacklight of the lcd
  delay(500);//I wanted the value written on the screen to stay on the screen for 500 miliseconds.
}

void loop() {
  int temp=dht.readTemperature();//I read the data from the sensor
  
  Serial.print("Sicaklik:");
  Serial.println(temp);
  
  lcd.setCursor(0,0);//I specified the location where the sign will go
  lcd.print("Temperature=   C");
  
  lcd.setCursor(12,0);//I specified the location where the sign will go
  lcd.print(temp);

  
  if(temp>24){
    digitalWrite(motor,HIGH);//I gave the command to start the dc motor
    lcd.setCursor(0,1);//I specified the location where the sign will go
    lcd.print("FAN ON ");
  }
  else{
    digitalWrite(motor,LOW);//I gave the command to stop the dc motor
    lcd.setCursor(0,1);//I specified the location where the sign will go
    lcd.print("FAN OFF");
  }
}

#include "dht.h"
#include <LiquidCrystal.h>
#define dht_apin A1 // Analog Pin sensor is connected to

String InBytes; //incoming data from python script
float power; //conversion of data from string to float
int ipower; //conversion of float to int
int light = 0; // store the current light value
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 =3, d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
dht DHT;

//custom character for temp
byte customChar[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte customChar2[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};

byte customChar3[8] = {
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
};


void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); //configure serial to talk to computer

    // initialize LCD and set up the number of columns and rows:
    lcd.begin(16,2);
    lcd.createChar(0, customChar);
    lcd.createChar(1, customChar2);
    lcd.createChar(2, customChar3);

    //configure pins
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(A4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    
      DHT.read11(dht_apin);
      light = analogRead(A4); // read and save value from PR

      Serial.print(int(DHT.temperature));
      Serial.print("x");
      Serial.print(light);
      Serial.print("x");
      Serial.println(int(DHT.humidity));

      // SERIAL DATA
      //humidity
      /*Serial.print("Current humidity = ");
      Serial.print(DHT.humidity);
      Serial.println("%  ");
      //temperature      
      Serial.print("Temperature = ");
      Serial.print(DHT.temperature); 
      Serial.println("°C  ");
      //light
      Serial.print("Light = ");
      Serial.println(light); // print current light value
      */

      delay(1000);

    //clear display
    lcd.clear();

    //print temperature on top line
    lcd.setCursor(0,0);
    lcd.print(" T:");
    lcd.print(int(DHT.temperature));
    lcd.write(byte(0));
    lcd.print("C  ");
    lcd.print("H:");
    lcd.print(int(DHT.humidity));
    lcd.print("%");
  
    if (light > 833){
      //LED
        digitalWrite(10,HIGH);
        digitalWrite(9,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);      
    }
    else if (light > 667){
        //LED
        digitalWrite(10,LOW);
        digitalWrite(9,HIGH);
        digitalWrite(8,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
    }
    else if (light > 500){
        //LED
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
      
    }
    else if (light > 333){
        //LED
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        digitalWrite(7,HIGH);
        digitalWrite(6,HIGH);
    }
    else if (light > 166){
        //LED
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        digitalWrite(7,LOW);
        digitalWrite(6,HIGH);
    }
    else{
        //LED
        digitalWrite(10,LOW);
        digitalWrite(9,LOW);
        digitalWrite(8,LOW);
        digitalWrite(7,LOW);
        digitalWrite(6,LOW);
    }
    
    //set cursor on bottom line of lcd
    lcd.setCursor(0, 1);
    //power depending on temp, light and humidity
    //lcd.print("P:");
    if (Serial.available()>0){
      InBytes = Serial.readStringUntil('\n');
      power = InBytes.toFloat();
      if (power >= 16){
        power = 16;
      }else if (power<0){
        power = 0;
      }

      ipower = (int) (power);

      //lcd.print(ipower * 2.0);

      for(int x=0; x<ipower; x++){
          lcd.write(byte(2));        
      }

      if ((ipower*2+.5) < power){
        lcd.write(byte(1));
      }
      
    }
  

}
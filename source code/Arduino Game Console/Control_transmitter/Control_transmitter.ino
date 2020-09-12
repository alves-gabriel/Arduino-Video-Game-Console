#include <Wire.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

int Down=2;
int Up=3;
int Left=4;
int Right=5;
int Action1=6;
int Action2=7;

void setup()
{
    Serial.begin(9600);    // Debugging only

    // Initialise the IO and ISR

    if (!driver.init())
    Serial.println("init failed");
    
    pinMode(Down,  INPUT);
    pinMode(Up,  INPUT);
    pinMode(Left,  INPUT);
    pinMode(Right,  INPUT);
    pinMode(Action1,  INPUT);
    pinMode(Action2,  INPUT);
}

int cod_button;

void msg_send(const char *msg){
  
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    digitalWrite(13, true);
    delay(1);
    digitalWrite(13, false);
    delay(1);
}


void loop()
{
      const char *msg ;
  
      if(digitalRead(Down)==HIGH) {msg = "2"; msg_send(msg);Serial.println("2");}
      if(digitalRead(Up)==HIGH)  {msg = "3"; msg_send(msg);Serial.println("3");}
      if(digitalRead(Left)==HIGH) {msg = "4";msg_send(msg);Serial.println("4");}
      if(digitalRead(Right)==HIGH) {msg = "5";msg_send(msg);Serial.println("5");}
      if(digitalRead(Action1)==HIGH) {msg = "6";msg_send(msg);Serial.println("6");}
      if(digitalRead(Action2)==HIGH) {msg = "7";msg_send(msg);Serial.println("7");}
 
}

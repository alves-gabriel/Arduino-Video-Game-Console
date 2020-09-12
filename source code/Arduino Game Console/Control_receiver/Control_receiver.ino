#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Wire.h>

RH_ASK driver(2000,8);//change speed and RX pin

void setup()
{
    Serial.begin(9600); // Debugging only
    if (!driver.init())
        Serial.println("init failed");

    Wire.begin(); // join i2c bus (address optional for master)
    // Initialise the IO and ISR

}

/*void send_data(int x){
   Wire.beginTransmission(4); // transmit to device #4
   Wire.write(x);              // sends one byte  
   Wire.endTransmission();    // stop transmitting
}*/

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    char msg;
    
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
    	  int i;

        driver.printBuffer("", buf, buflen);

        Serial.println(msg);

        msg=buf[0];

        if(msg=='7') {Serial.write('7');delay(1);Serial.println(msg);}
        if(msg=='6') {Serial.write('6');delay(1);Serial.println(msg);}
        if(msg=='5') {Serial.write('5');delay(1);Serial.println(msg);}
        if(msg=='4') {Serial.write('4');delay(1);Serial.println(msg);}
        if(msg=='3') {Serial.write('3');delay(1);Serial.println(msg);}
        if(msg=='2') {Serial.write('2');delay(1);Serial.println(msg);}   
               
        /*if(msg=='7') {send_data(7);delay(1);}
        if(msg=='6') {send_data(6);delay(1);}
        if(msg=='5') {send_data(5);delay(1);}
        if(msg=='4') {send_data(4);delay(1);}
        if(msg=='3') {send_data(3);delay(1);}
        if(msg=='2') {send_data(2);delay(1);}   */
     }

     //send_data(0);
     
}

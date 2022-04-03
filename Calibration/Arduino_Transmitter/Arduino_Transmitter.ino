/*
 * Author: JP Meijers
 * 30 September 2016
 */

#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11);
enum DATARATE {DR0, DR1, DR2, DR3, DR4, DR5, DR6, DR7, DR8, DR9, DR10};

String str;
String str1;
String str2;
String str3;
int messageNbr = 7;
int reqMessageNbr = 7;
String message;
int dataRate = 0;
int currentDistance = 0;
int maxDistance = 900;

void setup() {
  //output LED pin
  pinMode(13, OUTPUT);
  led_off();
  
  // Open serial communications and wait for port to open:
  
  Serial.begin(57600);
  
  loraSerial.begin(9600);
  loraSerial.setTimeout(1000);
  lora_autobaud();
  
  led_on();
  delay(1000);
  led_off();

  Serial.println("Initing LoRa");
  
  loraSerial.listen();
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  loraSerial.println("sys get ver");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("mac pause");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
//  loraSerial.println("radio set bt 0.5");
//  wait_for_ok();
  
  loraSerial.println("radio set mod lora");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set freq 868100000");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set pwr 14");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set sf sf7");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set afcbw 41.7");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set rxbw 125");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
//  loraSerial.println("radio set bitrate 50000");
//  wait_for_ok();
  
//  loraSerial.println("radio set fdev 25000");
//  wait_for_ok();
  
  loraSerial.println("radio set prlen 8");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set crc on");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set iqi off");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set cr 4/5");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set wdt 60000"); //disable for continuous reception
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set sync 12");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set bw 125");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);

  Serial.println("starting loop");
}

/*
void loop() {
  led_on();
  messageNbr += 1;
  message = "radio tx " + String(messageNbr);
  loraSerial.println(message);
  str = loraSerial.readStringUntil('\n');
  Serial.println(str + " - " + String(messageNbr));
  //str = loraSerial.readStringUntil('\n');
  //Serial.println(str);
  led_off();
  delay(5000);
}
*/

void loop() {
  led_on();

  if(messageNbr == reqMessageNbr) {
    switch(dataRate){
      
      case DR0:
        if(currentDistance == maxDistance){
          Serial.println("Calibration finished.");
          led_off();
          while(1) {
            delay(1);
          }
        }else{
          currentDistance += 20;           
        }       
        
        loraSerial.println("radio set sf sf12");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR1:
        loraSerial.println("radio set sf sf11");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR2:
        loraSerial.println("radio set sf sf10");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

       case DR3:
        loraSerial.println("radio set sf sf9");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

       case DR4:
        loraSerial.println("radio set sf sf8");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR5:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR6:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 250");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR7:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 500");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/5");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR8:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/6");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR9:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      case DR10:
        loraSerial.println("radio set sf sf7");
        str = loraSerial.readStringUntil('\n');
        Serial.println("sf - " + str);
    
        loraSerial.println("radio set bw 125");
        str = loraSerial.readStringUntil('\n');
        Serial.println("bw - " + str);
    
        loraSerial.println("radio set cr 4/8");
        str = loraSerial.readStringUntil('\n');
        Serial.println("cr - " + str);
        break;

      default:
        Serial.println("Something went wrong...");
        led_off();
        while(1) {
          delay(1);
        }
        break;
    }
    loraSerial.println("radio get sf");
    str1 = loraSerial.readStringUntil('\n');
    loraSerial.println("radio get bw");
    str2 = loraSerial.readStringUntil('\n');
    loraSerial.println("radio get cr");
    str3 = loraSerial.readStringUntil('\n');
    Serial.println("sf: " + str1 + ", bw: " + str2 + ", cr: " + str3 + ".");
    
    messageNbr = 0;
    if(dataRate == 10){
      dataRate = 0;
      Serial.println("Move receiver! Waiting 20 seconds before proceeding with DR0...");
      delay(20000);
    }else{
      dataRate += 1;
      Serial.println("Waiting 3 seconds before continuing with the next datarate...");
      delay(3000);
    }
  }
  //message = "radio tx " + String(messageNbr);
  loraSerial.println("radio tx 0");
  loraSerial.readStringUntil('\n');
  str = loraSerial.readStringUntil('\n');
  Serial.println(str + " - " + String(messageNbr));
  messageNbr += 1;
  led_off();
  delay(100);
}

void lora_autobaud()
{
  String response = "";
  while (response=="")
  {
    delay(1000);
    loraSerial.write((byte)0x00);
    loraSerial.write(0x55);
    loraSerial.println();
    loraSerial.println("sys get ver");
    response = loraSerial.readStringUntil('\n');
  }
}

/*
 * This function blocks until the word "ok\n" is received on the UART,
 * or until a timeout of 3*5 seconds.
 */
int wait_for_ok()
{
  str = loraSerial.readStringUntil('\n');
  if ( str.indexOf("ok") == 0 ) {
    return 1;
  }
  else return 0;
}

void led_on()
{
  digitalWrite(13, 1);
}

void led_off()
{
  digitalWrite(13, 0);
}

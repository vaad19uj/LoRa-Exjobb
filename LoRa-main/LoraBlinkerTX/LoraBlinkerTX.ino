 #include <rn2xx3.h>

/*
 * Author: JP Meijers
 * 30 September 2016
 */

#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11);
rn2xx3 myLora(loraSerial);


enum DATARATE {DR0F868,DR0F433 ,DR1F868 ,DR1F433 ,DR2F868,DR2F433,DR3F868 ,DR3F433 ,DR4F868 ,DR4F433 ,DR5F868 , 
DR5F433,DR6F868 ,DR6F433 ,DR7F868 ,DR7F433 ,DR8F868 ,DR8F433 ,DR9F868,DR9F433 ,DR10F868 ,DR10F433 };

String str;

int outPin = 7; // mine
int inPin = 8;
int changeDR = 0;
int val = 0;

/****************************************************************************************************************************************************************/

void setup() {
  //output LED pin
  pinMode(13, OUTPUT);
  led_off();
  
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Start");
  
  loraSerial.begin(9600);
  loraSerial.setTimeout(1000);

// Output to tell current sensor when transittion is happening.
  pinMode(outPin,OUTPUT);
  digitalWrite(outPin,LOW);
// --------------------------------------------

// input from current sensor when changing DR automatically.
  pinMode(inPin,INPUT);
  digitalWrite(inPin, LOW);

//---------------------------------------------

// In kopierat---------------------------------
  pinMode(12, OUTPUT);    //reset RN2483
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);

  
  delay(100);             //wait for the RN2xx3's startup message
  loraSerial.flush();
// In kopierat---------------------------------

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

//  loraSerial.println("radio set freq 433100000");
//  str = loraSerial.readStringUntil('\n');
//  Serial.println(str);

  loraSerial.println("radio set pwr 10");
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  
  loraSerial.println("radio set sf sf12");
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

/****************************************************************************************************************************************************************/

void loop() {
  //led_on();

  changeDR = digitalRead(inPin); //Read from current sensor
  
  digitalWrite(outPin,HIGH);//Mine
  
  //loraSerial.println("radio tx 20");
  loraSerial.println("radio tx 48656c6C6F");
  
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  str = loraSerial.readStringUntil('\n');
  Serial.println(str);
  led_off();

  digitalWrite(outPin,LOW);//Mine
  //delay(1000);
  //delay(500);


  //autonomous change the DR when 500 samples has been made
  if(changeDR){
    val += 1;
    
  switch(val){

  case DR0F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf12");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;
 
  case DR0F433:

    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf12");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR1F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf11");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR1F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf11");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR2F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf10");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR2F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf10");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR3F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf9");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;


case DR3F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf9");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR4F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf8");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

    
  case DR4F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf8");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR5F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR5F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR6F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 250");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;


   case DR6F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 250");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;


  case DR7F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 500");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

    case DR7F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 500");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/5");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR8F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/6");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

    case DR8F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/6");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR9F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

    case DR9F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;


  case DR10F868:

    loraSerial.println("radio set freq 868100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/8");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;

  case DR10F433:
  
    loraSerial.println("radio set freq 433100000");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
  
    loraSerial.println("radio set sf sf7");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set bw 125");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);

    loraSerial.println("radio set cr 4/8");
    str = loraSerial.readStringUntil('\n');
    Serial.println(str);
    break;



  default:
//    loraSerial.println("radio set sf sf12");
//    str = loraSerial.readStringUntil('\n');
//    Serial.println(str);
//
//    loraSerial.println("radio set bw 125");
//    str = loraSerial.readStringUntil('\n');
//    Serial.println(str);
//
//    loraSerial.println("radio set cr 4/6");
//    str = loraSerial.readStringUntil('\n');
//    Serial.println(str);
    
    break;
  }



    changeDR = 0;
    delay(1000);
  }
  delay(100);
}

/****************************************************************************************************************************************************************/

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

//  // Try a maximum of 10 times with a 1 second delay
//  for (uint8_t i=0; i<10 && response==""; i++)
//  {
//    delay(1000);
//    loraSerial.write((byte)0x00);
//    loraSerial.write(0x55);
//    loraSerial.println();
//    // we could use sendRawCommand(F("sys get ver")); here
//    loraSerial.println("sys get ver");
//    response = loraSerial.readStringUntil('\n');
//  }
}

/****************************************************************************************************************************************************************/

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

/****************************************************************************************************************************************************************/

void led_on()
{
  digitalWrite(13, 1);
}

/****************************************************************************************************************************************************************/

void led_off()
{
  digitalWrite(13, 0);
}

/****************************************************************************************************************************************************************/




/****************************************************************************************************************************************************************/

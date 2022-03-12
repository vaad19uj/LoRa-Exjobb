#include <Adafruit_INA219.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <StopWatch.h>

#define ITERATIONS 1000;
#define AVERAGES 1000;
//define ITERATIONS 500;
//define AVERAGES 500;
//#define ITERATIONS 100;
//#define AVERAGES 100;
#define SKIP 150;

StopWatch stopWatch;

Adafruit_INA219 ina219;

float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;

float shuntvoltage_Test = 0;
float busvoltage_Test = 0;
float current_mA_Test = 0;
float loadvoltage_Test = 0;
float power_mW_Test = 0;
float time_ms_Test = 0;

float timeHour = 0;
float microWattHour = 0;
float milliWattHour = 0;
float wattHour = 0;

bool print = false;
bool run = true;
int counter = 1;
int iterations = 0;
int averageCounter = 0;
int inPin = 7;
int val = 0;
int outPinTx = 8;
int outPinRx = 6;
int currentDR = 0;


/****************************************************************************************************************************************************************/

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");

  pinMode(inPin,INPUT);// Input from LoRa transmitter
  digitalWrite(inPin,LOW);

  pinMode(outPinTx, OUTPUT);
  digitalWrite(inPin,LOW);

  pinMode(outPinRx, OUTPUT);
  digitalWrite(inPin,LOW);

  iterations = ITERATIONS;
}

/****************************************************************************************************************************************************************/

void loop(void) 
{
  if(run){
    // when transmitter starts a transmittion, we will start collecting data.
    val = digitalRead(inPin);
    if(val){ 
  
      // Timer start when transmittion starts
      if(!print)
        stopWatch.start();
    
      print = true;
      shuntvoltage += ina219.getShuntVoltage_mV();
      busvoltage += ina219.getBusVoltage_V();
      current_mA += ina219.getCurrent_mA();
      power_mW += ina219.getPower_mW();
      loadvoltage += busvoltage + (shuntvoltage / 1000);
    }
    else{
      // After every transmittion the data is saved and added toghether for every iteration.
      // When the set amount of iterations are done, the average data values will be calculated and printed. 
      if(print){
        if(counter <= iterations){
          //if(counter > 150){
            time_ms_Test += stopWatch.elapsed(); // Save elapsed time
            stopWatch.stop();
            stopWatch.reset();
            
            shuntvoltage_Test += shuntvoltage;
            busvoltage_Test += busvoltage;
            current_mA_Test += current_mA;
            loadvoltage_Test += loadvoltage;
            power_mW_Test += power_mW;
            //Serial.print("Iteration: "); Serial.print(counter); Serial.print("/");Serial.println(iterations);
            Serial.println(power_mW);
          //}
          counter++;
        }
        else{
          time_ms_Test = time_ms_Test/AVERAGES;
          shuntvoltage_Test = shuntvoltage_Test/AVERAGES;
          busvoltage_Test = busvoltage_Test/AVERAGES;
          current_mA_Test = current_mA_Test/AVERAGES;
          loadvoltage_Test = loadvoltage_Test/AVERAGES;
          power_mW_Test = power_mW_Test/AVERAGES;
          averageCounter++;
  
          // Converts test time to hours and then converts watt usage to watts per hour
          timeHour = time_ms_Test/3600000;
          microWattHour = (power_mW_Test*1000)*timeHour;
          milliWattHour = power_mW_Test*timeHour;
          wattHour = (power_mW_Test/1000)*timeHour;

          Serial.print("DATARATE: ");
          Serial.print(currentDR);
          Serial.println("");
          Serial.print("Average of packages sent -------------------------------------------------------\n");
          Serial.print("Average: ");Serial.println(averageCounter);
          Serial.print("Average Time:          "); Serial.print(time_ms_Test); Serial.println(" ms");
          Serial.print("Average Bus Voltage:   "); Serial.print(busvoltage_Test); Serial.println(" V");
          Serial.print("Average Shunt Voltage: "); Serial.print(shuntvoltage_Test); Serial.println(" mV");
          Serial.print("Average Load Voltage:  "); Serial.print(loadvoltage_Test); Serial.println(" V");
          Serial.print("Average Current:       "); Serial.print(current_mA_Test); Serial.println(" mA");
          Serial.print("Average Power:         "); Serial.print(power_mW_Test); Serial.println(" mW");
  
          Serial.print("Energy usage:          "); Serial.print(microWattHour); Serial.println(" uWh");
          Serial.print("Energy usage:          "); Serial.print(milliWattHour); Serial.println(" mWh");
          Serial.print("Energy usage:          "); Serial.print(wattHour); Serial.println(" Wh");
          Serial.println("");
          Serial.println("");
          Serial.println("");
          Serial.println("");
      
          shuntvoltage_Test = 0;
          busvoltage_Test = 0;
          current_mA_Test = 0;
          loadvoltage_Test = 0;
          power_mW_Test = 0;
          counter = 1;
          currentDR += 1;
          //run = false;

          //Changes the DR on the transceiver and transmitter.
          digitalWrite(outPinTx, HIGH);
          digitalWrite(outPinRx, HIGH);
          delay(100);
          digitalWrite(outPinTx, LOW);
          digitalWrite(outPinRx, LOW);
          
          if(currentDR>21){
            run = false;
            Serial.print("Test done!"); 
          }


          //if(currentDR>1){
            //run = false;
            //Serial.print("Test done!"); 
          //}
        }
      }
      // -----------------TEST--------------
      shuntvoltage = 0;
      busvoltage = 0;
      current_mA = 0;
      loadvoltage = 0;
      power_mW = 0;
      print = false;
      }
    }
  }

  /****************************************************************************************************************************************************************/
 

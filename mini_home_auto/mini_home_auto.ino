#include <Time.h>
#include <TimeLib.h>

/**
 * A small home automation project with a model house for a school project.
 * 
 * Functions:
 *        - Lights switches on if a motion is detected and the light intensity is low (below or equal to the pre-defined value)
 *        - Lights switches off if a motion is not detected for a pre-defined time or the light intensity is above the pre-defined value
 *        - Fan switches on if a motion is detected and the temperature is high (above the pre-defined value)
 *        - Fan switches off if a motion is not detected for a pre-defined time or the temperature is below or equal to the pre-defined value
 * 
 * Sensors:
 *        - PIR (Passive Infra Red): 
 *               - Detects motion in Hall: Connected to pin D11
 *               - Detects motion in room: Connected to pin D12
 *        - LDR (Light Dependent Resistor):
 *               - Detects intesity of light in Hall: Connected to pin A0
 *               - Detects intesity of light in Room: Connected to pin A1
 * Lights:
 *        - LED (Light Emitting Diode):
 *               - Lit the Hall: Connected to pin D9
 *               - Lit the Room: Connected to pin D10
 *               
 * Motor:
 *        - DC motor (Direct Current motor):
 *               - Aerates the Hall: Connected to pin ?
 */

int hall_ldr_pin = A0;
int hall_led_pin = 9;
int hall_ldr_value = 0;
int hall_pir_Pin = 11;    //the digital pin connected to the PIR sensor's output

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

void setup() {
  pinMode(hall_led_pin, OUTPUT);
  Serial.begin(9600);
  pinMode(hall_pir_Pin, INPUT);
  digitalWrite(hall_pir_Pin, LOW);
  digitalWrite(hall_led_pin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  
}

void loop() {
  if(digitalRead(hall_pir_Pin) == HIGH){
       switch_light();   //the led visualizes the sensors output pin state
       if(lockLow){  
         //make sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50);
         }         
         takeLowTime = true;
       }

     if(digitalRead(hall_pir_Pin) == LOW){       
      switch_light_off();  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       } 
}

void switch_light() {
  hall_ldr_value = analogRead(hall_ldr_pin);
  Serial.print("Hall LDR Value: ");
  Serial.println(hall_ldr_value);
  if (hall_ldr_value > 10)
    digitalWrite(hall_led_pin, HIGH);
  else 
    digitalWrite(hall_led_pin, LOW);
}

void switch_light_off() {
  digitalWrite(hall_led_pin, LOW);
}

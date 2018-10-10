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

void setup() {
  pinMode(hall_led_pin, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  hall_ldr_value = analogRead(hall_ldr_pin);
  Serial.print("Hall LDR Value: ");
  Serial.println(hall_ldr_value);
  if (hall_ldr_value > 10)
    digitalWrite(hall_led_pin, HIGH);
  else 
    digitalWrite(hall_led_pin, LOW);
  delay(1000);
}

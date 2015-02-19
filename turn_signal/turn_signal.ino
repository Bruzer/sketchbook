/*
   Copyright (C) 2014 Bruzer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * This program was written for the Arduino.  Wait for the right or left input
 * pins to be high and flash the corresponding LEDs until the same input is 
 * high again. 
 * 
 * Wiring setup:
 * Connect pin 2 to the annode of the left LEDs.
 * Connect pin 3 to the annode of the right LEDs.
 * Connect pin 4 to the resistor going to the left switch.
 * Connect pin 5 to the resistor going to the right switch.
 * Connect GND to the common ground rail.
 * Connect 3.3v to the common positive rail.
 */

const boolean debug = false;  // Flag to control printing debug information to the console.
const int leftPin = 2;  // The pin controlling the left side.
const int leftSwitch = 4;  // The pin with the left input switch.
const int rightPin = 3;  // The pin controlling the right side.
const int rightSwitch = 5;  // The pin with the right input switch.
const int duration = 100;  // The milliseconds to wait between blinks.

boolean blinkLeft = false;  // The variable for the left LEDs HIGH or LOW.
boolean blinkRight = false;  // The variable for the right LEDs HIGH or LOW.
int ledState = LOW;
int previousLeft = LOW;
int previousRight = LOW;
long timeLeft = 0;
long timeRight = 0;

/**
 * This function is called once when the sketch starts.
 */
void setup() {
  pinMode(leftPin, OUTPUT);
  pinMode(leftSwitch, INPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(rightSwitch, INPUT);
  if (debug) {
    Serial.begin(9600);
  }
}

/**
 * This function is called repeatedly after the setup() method is called.
 */
void loop() {
  
  int leftValue = digitalRead(leftSwitch);
  int rightValue = digitalRead(rightSwitch);
  long currentTime = millis();
  
  if (leftValue == HIGH && previousLeft == LOW && currentTime - timeLeft > duration * 2) {
    blinkLeft = !blinkLeft;
    timeLeft = millis();
  }
  previousLeft = leftValue;
  
  if (rightValue == HIGH && previousRight == LOW && currentTime - timeRight > duration * 2) {
    blinkRight = !blinkRight;
    timeRight = millis();
  }
  previousRight = rightValue;

  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  
  if (blinkLeft || ledState == LOW) {
    digitalWrite(leftPin, ledState);
  }
  if (blinkRight || ledState == LOW) {
    digitalWrite(rightPin, ledState);
  }
  
  delay(duration);

}

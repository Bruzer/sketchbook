
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
 * This is program 1 in the series of experiments trying to evaluate 
 * the accuracy of the arduino clock.  This program blinks an LED 
 * using the delay() function.
 */
const boolean debug = false;  // Flag controlling printing out debug information to serial console.
const int inputPin = 3;  // The pin that the switch is connected to.
const int ledPin = 4;  // The pin that the LED is connected to.

int ledState = LOW;  // Keep the led state in a variable.
boolean run = false;  // Makes the program wait for input from the user.
long interval = 500;  // The time to wait between changing states.

/**
 * This function is called when the sketch starts.
 */
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  if (debug) {
    // open the serial port at 9600 bps:
    Serial.begin(9600);
  }
}

/**
 * This function is called repeatedly after the setup() method is called.
 */
void loop() {
  // When not running wait for input pin to go high.
  if (!run) {
    int inputValue = digitalRead(inputPin);
    if (inputValue == HIGH) {
      if (debug) {
        Serial.println("inputValue was HIGH");
      }
      run = true;
    }
  }
  // When running simply blink.
  if (run) {
    // Swap the ledState.
    if ( ledState == LOW ) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // Write the new state to the ledpin.
    digitalWrite(ledPin, ledState);
    // Pause the program for a specific amount of milliseconds.
    delay(interval);
  }
}

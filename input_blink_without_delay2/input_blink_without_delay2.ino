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
 * This is program 3 in the series of experiments trying to evaluate the
 * accuracy of the arduino clock.  This program waits for the input pin to
 * be high and flash the LED once every 500 microseconds (half a second).
 * By setting debug to true the program will print off the drift value
 * to the serial console. 
 *
 * Wiring setup:
 * Connect pin 3 to the resistor going to the switch.
 * Connect pin 4 to the annode of the LED.
 * Connect pin 3.3v to the other end of the switch.
 * Connect pin GND to the common ground rail.
 * 
 */
const boolean debug = false;  // Print debug information to serial console.
const int inputPin = 3;  // The pin that the switch is connected to.
const int ledPin = 4;  // The pin that the LED is connected to.

unsigned long counter = 0;  // The number of times that have been blinked.
long interval = 500;  // The time to wait between changing states.
int ledState = LOW;  // Keep the led state in a variable.
boolean run = false;  // Makes the program wait for input from the user.
unsigned long startMilliseconds = 0;  // Store the milliseconds when the blinking started.

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
  if (!run) {
    int inputValue = digitalRead(inputPin);
    if (inputValue == HIGH) {
      if (debug) {
        Serial.println("inputValue was HIGH");
      }
      run = true;
      startMilliseconds = millis();
      if (debug) {
        Serial.print("Start time ");
        Serial.println(startMilliseconds);
      }
    }
  }
  if (run) {
    // Get the number of milliseconds since the Arduino began running.
    unsigned long currentMilliseconds = millis();
    unsigned long additionalMilliseconds = counter * interval;
    // Compute the elapsed milliseconds since the start time.
    long elapsedMilliseconds = currentMilliseconds - (startMilliseconds + additionalMilliseconds);
    // Is the elapsed milliseconds equal or more than the interval?
    if ( elapsedMilliseconds >= 0 ) {
      counter++;
      if (debug) {
        Serial.print("Off by ");
        Serial.println(elapsedMilliseconds);
        Serial.print("Counter ");
        Serial.println(counter);
      } 
      // Swap the ledState.
      if ( ledState == LOW ) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      // Write the new state to the ledpin.
      digitalWrite(ledPin, ledState);
    }
  }
}

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
 * This program blinks an LED with checking time rather than using delay().
 */
const boolean debug = true;  // Flag controlling printing out debug information to serial console.
const int ledPin = 13;


int ledState = LOW;  // Keep the led state in a variable.
long previousMilliseconds = 0;  // Store the last time the milliseconds were updated.
long interval = 500;  // The time to wait between changing states.

/**
 * This function is called when the sketch starts.
 */
void setup() {
  pinMode(ledPin, OUTPUT);
  if (debug) {
    // open the serial port at 9600 bps:
    Serial.begin(9600);
  }
}

/**
 * This function is called repeatedly after the setup() method is called.
 */
void loop() {
  // Get the number of milliseconds since the Arduino began running.
  unsigned long currentMilliseconds = millis();
  // Compute the elapsed milliseconds since the previous reading.
  long elapsedMilliseconds = currentMilliseconds - previousMilliseconds;
  // Is the elapsed milliseconds equal or more than the interval?
  if ( elapsedMilliseconds >= interval ) {
    previousMilliseconds = currentMilliseconds;
    if (debug) {
      Serial.println((elapsedMilliseconds - interval));
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

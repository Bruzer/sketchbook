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
 * This sketch is an example of the serial communication to an Arduino.
 */

// The 'character' type hold 1 byte of data, or 256 values.
// A char can be interpreted as a small number (0-255) or as a member of the
// ASCII set.

int ledPin = 13;   // select the pin for the LED

void setup() {
 pinMode(ledPin, OUTPUT);    // declare the LED's pin as output
 Serial.begin(9600);        // connect to the serial port
}
void loop () {
  if (Serial.available()) {
    // Read the first byte of available serial data or -1 if unavailable
    char bite = Serial.read();
    if (bite == 'b') {
      while (Serial.available() < 2) {
        Serial.println("waiting for available");
      }
      int times = Serial.read();
      int duration = Serial.read();
      blink(times, duration);
    } else if (bite == 'd') {
      while (Serial.available() < 5) {
        Serial.println("waiting for available");
      }
      int pos = Serial.read(); 
      int green = Serial.read(); 
      int red = Serial.read(); 
      int blue = Serial.read(); 
      
      String str = readString();
      displayString(str, pos, green, red, blue);
    } else {
      Serial.println(bite, HEX);
    }
  }
}

String readString() {
  String string = "";
  char c = ' ';
  while (c != '\n' && c != -1 && c != 0) {
    if (Serial.available() > 0) {
      c = Serial.read();
      string += c;
    } 
  }
  return string;
}
void blink(int times, int duration) {
  for (int a = 0; a < times; a++) {
    Serial.println("blink!");
    digitalWrite(ledPin, HIGH);
    delay(duration);
    digitalWrite(ledPin, LOW);
    delay(duration);
  }
}
void displayString(String str, int pos, int green, int red, int blue) {
  Serial.print("Position ");
  Serial.print(pos);
  Serial.print(" Green ");
  Serial.print(green);
  Serial.print(" Red ");
  Serial.print(red);
  Serial.print(" Blue ");
  Serial.println(blue);
  
  Serial.println(str);
}

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
// Below, 'character' types are defined:  They hold 1 byte of data, 256 values.
// A char can be interpreted as a small number (0-255) or as a member of the
// ASCII set (which is what we deal with below).  Characters expressed as
// ASCII are surrounded in single-quotes, like '5'.
// Thus each char has a corresponding numeric value can thus be tested against.
 
int ledPin = 13;   // select the pin for the LED
int val = 0;       // variable to store the data from the serial port
 
void setup() {
 pinMode(ledPin,OUTPUT);    // declare the LED's pin as output
 Serial.begin(9600);        // connect to the serial port
}
	 
void loop () {
  if (Serial.available()) {
    // For the below examples, let's pretend that the passed-in serial
    // value is character '5'.
    // Since the declared variable val is an int, it converts the char
    // value passed in into an int.
    // If char val = '5', the numeric representation is 53.
    val = Serial.read();      // read the serial port
 
    // If the stored value is a single-digit number, blink the LED
    // that number of times.
    // Here we compare the int value of val against the int values
    // of the string.
    // Characters '0' and '9' are equivalent to integer 48 and 57.
    if (val > '0' && val <= '9' ) {
      Serial.println(val);
      // Convert from char to int:
      // From above, int conversion of val, which is char '5', is 53.
      // int conversion of char '0' is 48.
      // 53-48 = 5  : blink that # of times
      val = val - '0'; 
      for(int i=0; i<val; i++) {
        Serial.println("blink!");
        digitalWrite(ledPin,HIGH);
        delay(150);
        digitalWrite(ledPin, LOW);
        delay(150);
      }
    }
  }
}

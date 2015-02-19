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
 * This program drives a single 7-segment LED from a 74HC595 shift register.
 * 
 * Wiring setup:
 * Connect arduino pin 8 to shift register pin 12 (ST_CP) on the 74HC595.
 * Connect arduino pin 11 to shift register pin 14 (DS) on the 74HC595.
 * Connect arduino pin 12 to shift register pin 11 (SH_CP) on the 74HC595.
 * Connect arduino pin 5v to shift register pin 16 (Vcc) on the 74HC595.
 * Connect arduino pin GND to shift register pin 8 (GND) on the 74HC595.
 * Connect shift register pins 1-7 (Q1-Q7) to the LED.
 * Connect shift register pin 15 (Q0) to the LED.
 * Connect shift register pin 10 (MR) to 5v rail.
 * Connect shift register pin 13 (OE) to GND rail.
 */
const boolean debug = true;  // Print information to the serial console.
const int clockPin = 12;  // Clock connected to SH_CP of 74HC595.
const int dataPin = 11;  // Data connected to DS of 74HC595.
const int latchPin = 8;  // Latch connected to ST_CP of 74HC595.

byte dataArray[10];  // The array for the test pattern.
byte digitArray[10];  // The array for number digits.
byte decimal = 0x80;  // The mask for a decimal point.

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  
  // Create a test pattern to determine the LED segments.
  dataArray[0] = 0x01;  // 0000 0001
  dataArray[1] = 0x02;  // 0000 0010
  dataArray[2] = 0x04;  // 0000 0100
  dataArray[3] = 0x08;  // 0000 1000
  dataArray[4] = 0x10;  // 0001 0000
  dataArray[5] = 0x20;  // 0010 0000
  dataArray[6] = 0x40;  // 0100 0000
  dataArray[7] = 0x80;  // 1000 0000
  dataArray[8] = 0xFF;  // 1111 1111
  dataArray[9] = 0x00;  // 0000 0000

  // Create the patterns to display each digit.
  digitArray[0] = 0x77;
  digitArray[1] = 0x41;
  digitArray[2] = 0x3B;
  digitArray[3] = 0x6B;
  digitArray[4] = 0x4D;
  digitArray[5] = 0x6E;
  digitArray[6] = 0x7E;
  digitArray[7] = 0x43;
  digitArray[8] = 0x7F;
  digitArray[9] = 0x6F;
  
  if (debug) {
    Serial.begin(9600);
  }
}

void loop() {
  for (int a = 0; a < 10; a++) {
    //int data = dataArray[a];
    int data = digitArray[a];
    if (debug) {
      Serial.print(a, DEC);
      Serial.print(" = 0x");
      Serial.println(data, HEX);
    }

    // Ground latchPin and hold low for the transmission.
    digitalWrite(latchPin, LOW);
    
    // Shift the data to the dataPin.
    shiftOut(dataPin, clockPin, LSBFIRST, data);
    // Most Significant Bit first (MSBFIRST) does not seem to work in this case.
    
    // Return the latch pin to high to signal chip that it no longer needs to listen.
    digitalWrite(latchPin, HIGH);
    delay(600);
  }
  delay(1000);
}



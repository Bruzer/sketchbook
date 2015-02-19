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
 * This program drives one 7-segment LED digit and one 7-segment LED 3 digit 
 * from two 74HC595 shift registers.
 * 
 * Wiring setup:
 * Connect arduino pin 8 to shift register #1 pin 12 (ST_CP) on the 74HC595.
 * Connect arduino pin 11 to shift register #1 pin 14 (DS) on the 74HC595.
 * Connect arduino pin 12 to shift register #1 pin 11 (SH_CP) on the 74HC595.
 * Connect arduino pin 5v to shift register #1 pin 16 (Vcc) on the 74HC595.
 * Connect arduino pin GND to shift register #1 pin 8 (GND) on the 74HC595.
 * Connect shift register #1 pins 1-7 (Q1-Q7) to LED segment #1.
 * Connect shift register #1 pin 15 (Q0) to LED segment #1.
 * Connect shift register #1 pin 10 (MR) to 5v rail.
 * Connect shift register #1 pin 13 (OE) to GND rail.
 * Connect shift register #2 to shift register #1
 * Connect shift register #2 pin 1-7 (Q1-Q7) to LED segment #2.
 * Connect shift register #2 pin 15 (Q0) to LED segment #2.
 * Connect shift register #2 pin 10 (MR) to 5v rail.
 * Connect shift register #2 pin 13 (OE) to GND rail.
 */
const boolean debug = true;  // Print information to the serial console.
const int clockPin = 12;  // Clock connected to SH_CP of 74HC595.
const int dataPin = 11;  // Data connected to DS of 74HC595.
const int latchPin = 8;  // Latch connected to ST_CP of 74HC595.
const int selectRightPin = 2;  // Select the right digit on the 3 digit LED.
const int selectMiddlePin = 3;  // Select the middle digit on the 3 digit LED.
const int selectLeftPin = 4;  // Select the left digit on the 3 digit LED.
const int displayTime = 10; 

byte dataArray[10];  // The array for the test pattern.
byte digitArray[10];  // The array for number digits.
byte decimal = 0x80;  // The mask for a decimal point.

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(selectRightPin, OUTPUT);
  pinMode(selectMiddlePin, OUTPUT);
  pinMode(selectLeftPin, OUTPUT);  
  
  // Create a test pattern to determine how the LED segments are mapped.
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
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  digitalWrite(latchPin, HIGH);
  digitalWrite(selectRightPin, HIGH);
  digitalWrite(selectMiddlePin, HIGH);
  digitalWrite(selectLeftPin, HIGH);
}

void writeNumber(int number) {
  int thousands = number / 1000;
  int hundreds = number / 100;
  int tens = number / 10;
  int ones = number % 10;
  
  // Select the left pin to display the hundreds number on the three segement LED.
  digitalWrite(selectLeftPin, LOW);
  // Write to the latch so the shift register waits for data.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[thousands % 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[hundreds % 10]);
  digitalWrite(latchPin, HIGH);
  // Delay to display the left number for a longer peroid of time.
  delay(displayTime);
  digitalWrite(selectLeftPin, HIGH);
  
  // Select the middle pin to display the tens number on the three segment LED.
  digitalWrite(selectMiddlePin, LOW);
  // Write to the latch pin so the shift register waits for data.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[thousands % 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[tens % 10]);
  digitalWrite(latchPin, HIGH);
  // Delay to display the middle number for a longer period of time.
  delay(displayTime);
  digitalWrite(selectMiddlePin, HIGH);
  
  // Select the right pin to display the ones number on the three segment LED.
  digitalWrite(selectRightPin, LOW);
  // Write to the latch pin so the shift register waits for data.
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[thousands % 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, digitArray[ones]);
  digitalWrite(latchPin, HIGH);
  // Delay to display the right number for a longer peroid of time. 
  delay(displayTime);
  digitalWrite(selectRightPin, HIGH);
}

void loop() {
  // Count from 0 to 9.
  for (int a = 0; a < 10000; a++) {
    writeNumber(a);
    //delay(displayTime);

    if (debug) {
      Serial.print(a, DEC);
    }

    writeNumber(a);
    delay(displayTime);
    
    if (debug) {
      Serial.print(" = 0x");
      Serial.println(digitArray[a], HEX);
    }
    writeNumber(a);
    delay(displayTime);
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  digitalWrite(latchPin, HIGH);
  delay(displayTime*5);
}



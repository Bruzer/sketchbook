/*
   Copyright (C) 2013 Bruzer

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
 * This sketch controls a servo with manual Pulse-Width Modulation (PWM)
 *
 * To wire this up:
 *   Attach 5v to the red servo wire.
 *   Attach GND to the black servo wire.
 *   Attach pin 9 to the white or yellow servo wire.
 *
 * Pulse with modulation (PWM) controls servos.  For normal servos the
 * HIGH part of the pulse lasts between 500, to 2500 MICRO seconds.
 * The LOW part of the pulse must be 15 to 25 milliseconds in length.
 * 
 * For this project I am used a Futaba FP-S148 and according to the specifications
 * 1.52 milliseconds is neutral.
 **/
int servoPin = 9;
int servoPosition = 0;
// Generally speaking the servo range is 500 microseconds to 2500 microseconds.
// I found the range on the servo was greater than 180 degrees.
// Use the position variables to find min and max range.
int position0 = 400;
int position90 = 1400;
int position180 = 2500;
int increment = 50;

void setup() {
  pinMode(servoPin, OUTPUT);
}

void loop() {
  
  // Rotate counter-clockwise to max limit.
  for (servoPosition = position0; servoPosition <= position180; servoPosition += increment) {
    pulseWidthModulation(servoPin, servoPosition);
  }
  delay(3000);
  
  // Rotate back to center.
  for (servoPosition = position180; servoPosition >= position90; servoPosition -= increment) {
    pulseWidthModulation(servoPin, servoPosition);
  }
  delay(3000);
  
  // Rotate clockwise to the min limit.
  for (servoPosition = position90; servoPosition >= position0; servoPosition -= increment) {
    pulseWidthModulation(servoPin, servoPosition);
  }
  delay(3000);
}

void pulseWidthModulation(int pin, int microseconds) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(microseconds);
  digitalWrite(servoPin, LOW);
  delay(22); // Delay 22 milliseconds to wait for servo to reach position.
}

// Something I noticed on this program was the servo went "limp" in the long 3 second dealys.
// Every 20 milliseconds (50 times per second) the HIGH pulse must be recieved again or the servo
// will de-energize and not hold its position.
    
 

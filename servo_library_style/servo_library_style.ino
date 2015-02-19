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
 * This sketch controls a servo with the Arduino Servo library.
 *
 * To wire this up:
 *   Attach 5v to the red servo wire.
 *   Attach GND to the black servo wire.
 *   Attach pin 9 to the white or yellow servo wire.
 *
 * For this project I am used a Futaba FP-S148 and according to the 
 * specifications 1.52 milliseconds is neutral.
 **/
 
 #include <Servo.h>
 
 Servo servo;  // Create a servo object to control a servo.
 
 // A maximum of 12 sero objects can be created for most Arduino boards.
 
 int servoPosition = 0;
 int increment = 10;
 
 void setup() {
   servo.attach(9);  // Attaches the servo on pin 9 to the servo object.
 }
 
 void loop() {
   // Rotate to 180 position.
   for (servoPosition = 0; servoPosition <= 180; servoPosition += increment) {
     servo.write(servoPosition);
     delay(22);  // Delay 22 milliseconds to wait for servo to reach position.
   }
   delay(3000);
   
   // Rotate to 90 position
   for (servoPosition = 180; servoPosition >= 90; servoPosition -= increment) {
     servo.write(servoPosition);
     delay(22);  // Delay 22 milliseconds to wait for servo to reach position.
   }
   delay(3000);
   
   // Rotate to 0 position.
   for (servoPosition = 90; servoPosition >= 0; servoPosition -= increment) {
     servo.write(servoPosition);
     delay(22);  // Delay 22 milliseconds to wait for servo to reach position.
   }
   delay(3000);
 }
 
 // Something I realized on this program was the servo was holding it's position during the 3 second delays.
 // So the Servo library is keeping the servo enegized for the duration of the delays.
 

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
// The SoftwareSerial library is used to talk to the Emic 2 module.
#include <SoftwareSerial.h>

#define rxPin 2    // Serial input (connects to Emic 2 SOUT).
#define txPin 3    // Serial output (connects to Emic 2 SIN).
#define aPin 4     // The pin for the A button.
#define bPin 5     // The pin for the B button.
#define cPin 6     // The pin for the C button.
#define dPin 7     //  The pin for the D button.
#define ledPin 13  // Most Arduino boards have an on-board LED on this pin.


// Create a new serial port to talk with the Emic 2 module.
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

String aString = "Apple";
String bString = "Banana";
String cString = "Coconut";
String dString = "Donut";

void setup()  // Set up code called once on start-up
{
  // define pin modes
  pinMode(rxPin, INPUT);   // Recieve is input.
  pinMode(txPin, OUTPUT);  // Transmit is output.
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // Set the data rate for the SoftwareSerial port.
  emicSerial.begin(9600);
  // Initialize the serial communication with the Arduino.
  Serial.begin(9600);

  digitalWrite(ledPin, LOW);  // turn LED off
  
  // The Emic2 takes about 3 seconds to initialize.
  // The Emic2 sends a ':' character to indicate it is ready to accept commands.
  // If the Emic2 is already initialized, a '\n' will make it send a ':'
  emicSerial.print('\n');
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer
  emicSerial.print("N1"); // Voice 0 to 8.
  emicSerial.print('\n');
  emicSerial.print("V5");  // Volume -48 to 18 db.
  emicSerial.print('\n');
  emicSerial.print("W100");  // Speaking rate, words per minute.
  emicSerial.print('\n');
  // Speak initialization text.
  speak("Ready for input.");
}

void loop()
{
  int a = digitalRead(aPin);
  int b = digitalRead(bPin);
  int c = digitalRead(cPin);
  int d = digitalRead(dPin);
  
  if (a == HIGH) {
    speak(aString);
    delay(25);
  } else if (b == HIGH) {
    speak(bString);
    delay(25);
  } else if (c == HIGH) {
    speak(cString);
    delay(25);
  } else if (d == HIGH) {
    speak(dString);
    delay(25);
  } else {
    if (Serial.available()) {
      int command = Serial.read();
      Serial.print("Read command: ");
      Serial.println(command);
      if (command == 's' || command == 'S') {
        String serialString = readSerialString();
        speak(serialString);
      }
    }
  }
}

void speak(String string) {
  digitalWrite(ledPin, HIGH);
  // If the Emic2 is already initialized, a '\n' will make it send a ':'
  emicSerial.print('\n');
  while (emicSerial.read() != ':');
  digitalWrite(ledPin, LOW);
  delay(10);
  emicSerial.print('S');    // Send S to make the emic speak.
  emicSerial.print(string);  // Send the string 
  emicSerial.print('\n');
  emicSerial.flush();
}

String readSerialString() {
  Serial.println("readSerialString");
  String string = "";
  boolean done = false;
  while (Serial.available() > 0 && !done) {
    char c = Serial.read();
    if (c == '\n') {
      done = true;
    } else {
      string += c;
    }
  }
  return string;
}
 

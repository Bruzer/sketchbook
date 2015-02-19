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
#include <LPD8806.h>
#include <SPI.h>

#define rxPin 2     // Serial input (connects to Emic 2 SOUT).
#define txPin 3     // Serial output (connects to Emic 2 SIN).
#define aPin 4      // The pin for the A button.
#define bPin 5      // The pin for the B button.
#define cPin 6      // The pin for the C button.
#define dPin 7      // The pin for the D button.
#define pingPin 8   // The pin that sends and receives pings.
#define dataPin 9   // Data pin for the light strip
#define clockPin 10 // Clock pin for the light strip.
#define ledPin 13   // Most Arduino boards have an on-board LED on this pin.

int numberOfLEDs = 40;
int mode = 0;
//String quotes [] = { 
  // Short Circuit
//  "Number 5 is alive!", "Malfunction! Need imput!", "No disassemble!", "Attractive. Nice software",
  // Lost in Space
//  "Danger, Will Robinson!", "Warning, warning!", "Danger, danger!", "Emergency protective circuits deactivated.",
  // 2001 Space Odyssey 
//  "I am completely operational, and all my circuts are functioning perfectly.", "The 9000 series is the most reliable computer ever made.",  "We are all, by any practical definition of the words, foolproof and incapable of error.", "my mind is going.  I can feel it. I can feel it.", "I'm sorry Dave, I'm afraid I can't do that", "This mission is too important for me to allow you to jeapordize it.",
//};

// Create a new serial port to talk with the Emic 2 module.
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);
// Arguments number of LEDs, dataPin, clockPin.
LPD8806 strip = LPD8806(numberOfLEDs, dataPin, clockPin);

void setup() {
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
  
  // initialize serial communication:
  Serial.begin(9600);
  
  digitalWrite(ledPin, LOW);  // turn LED off
  
  strip.begin();
  strip.show();
  colorChase(strip.Color(127, 127, 127), 50);
  // The Emic2 takes about 3 seconds to initialize.
  // The Emic2 sends a ':' character to indicate it is ready to accept commands.
  // If the Emic2 is already initialized, a '\n' will make it send a ':'
  emicSerial.print('\n');
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();
  emicSerial.print("N3"); // Voice 0 to 8.
  // 0: Perfect Paul (Paulo)
  // 1: Huge Harry (Francisco)
  // 2: Beautiful Betty
  // 3: Uppity Ursula
  // 4: Doctor Dennis (Enrique)
  // 5: Kit the Kid
  // 6: Frail Frank
  // 7: Rough Rita
  // 8: Whispering Wendy (Beatriz) 
  emicSerial.print('\n');
  emicSerial.print("V10");  // Volume -48 to 18 db.
  emicSerial.print('\n');
  emicSerial.print("W134");  // Speaking rate, words per minute.
  emicSerial.print('\n');
}

void loop() {

  int a = digitalRead(aPin);
  int b = digitalRead(bPin);
  int c = digitalRead(cPin);
  int d = digitalRead(dPin);
  
  if (a == HIGH) {
    mode = 1;
  } else if (b == HIGH) {
    mode = 2;
  } else if (c == HIGH) {
    mode = 3;
  } else if (d == HIGH) {
    mode = 4;
  }
  
  mode = react(mode);
  
  //mode = 0;
}

// Chase one dot down the full strip.
void colorChase(uint32_t color, uint8_t wait) {
  // Start by turning all pixels off:
  for (int a = 0; a < strip.numPixels(); a++) {
    strip.setPixelColor(a, 0);
  }

  // Then display one pixel at a time:
  for (int b = 0; b < strip.numPixels(); b++) {
    strip.setPixelColor(b, color); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(b, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

void lightPixels(uint32_t color, int ledsToLight) {
  for (int a = 0; a < numberOfLEDs; a++) {
    strip.setPixelColor(a, strip.Color(0, 0, 0));
  }
  for (int b = 0; b < ledsToLight; b++) {
    strip.setPixelColor(b, color);
  }
  strip.show();
}

// Set all the pixels one color.
void solidColor(uint32_t color) {
  for (int a = 0; a < strip.numPixels(); a++) {
    strip.setPixelColor(a, color);
  }
  strip.show();
}

int react(int personality) {
  if (personality > 0) {
    long inches = 0;
    inches = distanceInches();
    
    if (personality == 1) {
       Serial.println(inches);
       if (inches < 3) {
         solidColor(strip.Color(127, 0, 0));
         speak("You are too close!  Please back up to give me some space.");
         delay(400);
         solidColor(strip.Color(0, 0, 0));
       }
    } else if (personality == 2) {
      Serial.println(inches);
      if (inches > 25) {
        solidColor(strip.Color(0, 0, 127));
        speak("Hello?  Where did you go?  Come back!   I get lonely when you walk away.");
        delay(400);
        solidColor(strip.Color(0, 0, 0));
      }
    } else if (personality == 3) {
      // The maximum distance of the ping sensor is 145.
      float mutliplier = (float)numberOfLEDs / (float)145;
      Serial.print("Multiplier " );
      Serial.println(mutliplier);
      int ledsToLight = int(inches * mutliplier);
      Serial.print("LEDs to light ");
      Serial.println(ledsToLight);
      uint32_t color = strip.Color(0, 127, 0);
      lightPixels(color, ledsToLight);
      String distance = String(inches);
      speak("You are approximately");
      //delay(50);
      speak(distance);
      //delay(50);
      speak("inches away from me.");
      delay(400);
      //solidColor(strip.Color(0, 0, 0));
    } else if (personality == 4) {
      solidColor(strip.Color(127, 127, 127));
      delay(75);
      solidColor(strip.Color(0, 0, 0));
      delay(75);
      solidColor(strip.Color(127, 0, 0));
      speak("Danger, Will Robinson!");
      delay(75);
      speak("Activating protective circuits.");
      solidColor(strip.Color(127, 127, 127));
      delay(75);
      solidColor(strip.Color(0, 0, 0));
      delay(75);
      solidColor(strip.Color(127, 0, 0));
      delay(75);
      personality = 0;
      delay(400);
      solidColor(strip.Color(0, 0, 0));
    }
  }
  return personality;
}

long distanceInches() {
  long duration, inches;

  // Switch the pingPin to OUTPUT so the arduino can send the ping sensor a pulse.
  pinMode(pingPin, OUTPUT);
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  // The ping sensor is triggered by a HIGH pulse of 2 or more microseconds.
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the ping sensor switch it to INPUT.
  pinMode(pingPin, INPUT);
  // The ping sensor sends a HIGH pulse whose duration is the time (in microseconds) 
  // from the sending of the ping to the reception of its echo off of an object.
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  return inches;
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
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

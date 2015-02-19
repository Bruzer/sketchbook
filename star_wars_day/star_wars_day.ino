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
#include "LPD8806.h"
#include "SPI.h"

// This sketch uses the LPD8806 LED strip to simulate light sabers.

// Number of RGB LEDs in strand:
int numberOfLEDs = 40;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(numberOfLEDs, dataPin, clockPin);

void setup() {
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  colorUp(strip.Color(127,   0,   0), 30);  // Red = Darth Vader's lightsaber
  delay(1000);
  clearDown(50);
  delay(150);
  
  colorUp(strip.Color(0, 127,   0), 30);  // Green = Luke's lightsaber
  delay(1000);
  clearDown(50);
  delay(150);
  
  colorUp(strip.Color(  0,   0, 127), 30);  // Blue = Ben Kenobi's lightsaber
  delay(1000);
  clearDown(50);
  delay(150);
}



/** Light the pixels incrementally along the strip. */
void colorUp(uint32_t color, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(wait);
  }
}

/** Turn the pixels off decreasing to zero. */
void clearDown(uint8_t wait) {
  uint32_t off = strip.Color(0, 0, 0);
  for (int b = strip.numPixels() - 1; b >= 0; b--) {
    strip.setPixelColor(b, off);
    strip.show();
    delay(wait);
  }
}


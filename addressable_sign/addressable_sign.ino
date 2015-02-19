/**
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
#include <Adafruit_NeoPixel.h>
#include <Encabulator.h>
#include <Wire.h>


const String REDBULL = "REDBULL";
const String TURBULL = "TURBULL";
const String ENCABULATOR = "ENCABULATR";

// Test pattern 
byte block[] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F};

byte ascii[][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00}, //  
  {0x04, 0x00, 0x04, 0x04, 0x04}, // !
  {0x00, 0x00, 0x00, 0x0A, 0x0A}, // "
  {0x0A, 0x1F, 0x0A, 0x1F, 0x0A}, // #
  {0x04, 0x0E, 0x1F, 0x0E, 0x04}, // $
  {0x13, 0x0B, 0x04, 0x1A, 0x19}, // %
  {0x1F, 0x12, 0x0F, 0x0A, 0x0E}, // &
  {0x00, 0x00, 0x00, 0x04, 0x04}, // '
  {0x06, 0x08, 0x08, 0x08, 0x06}, // (
  {0x0C, 0x02, 0x02, 0x02, 0x0C}, // )
  {0x04, 0x15, 0x0E, 0x15, 0x04}, // *
  {0x04, 0x04, 0x1F, 0x04, 0x04}, // +
  {0x0C, 0x06, 0x0C, 0x00, 0x00}, // ,
  {0x00, 0x00, 0x1F, 0x00, 0x00}, // -
  {0x06, 0x06, 0x00, 0x00, 0x00}, // .
  {0x10, 0x08, 0x04, 0x02, 0x01}, // /
  {0x1F, 0x11, 0x11, 0x11, 0x1F}, // 0
  {0x0E, 0x04, 0x04, 0x0C, 0x04}, // 1
  {0x1F, 0x10, 0x0E, 0x01, 0x1E}, // 2
  {0x1F, 0x01, 0x07, 0x01, 0x1F}, // 3
  {0x01, 0x01, 0x1F, 0x11, 0x11}, // 4
  {0x1E, 0x01, 0x0E, 0x10, 0x1F}, // 5
  {0x1F, 0x11, 0x1F, 0x10, 0x1E}, // 6
  {0x08, 0x04, 0x02, 0x01, 0x1F}, // 7
  {0x1F, 0x11, 0x1F, 0x11, 0x1F}, // 8
  {0x0F, 0x01, 0x1F, 0x11, 0x1F}, // 9
  {0x00, 0x0C, 0x00, 0x0C, 0x00}, // :
  {0x08, 0x0C, 0x00, 0x0C, 0x00}, // ; 
  {0x01, 0x04, 0x10, 0x04, 0x01}, // <
  {0x00, 0x1F, 0x00, 0x1F, 0x00}, // =
  {0x10, 0x04, 0x01, 0x04, 0x10}, // >
  {0x04, 0x04, 0x02, 0x11, 0x0E}, // ?
  {0x0E, 0x1A, 0x1A, 0x13, 0x0E}, // @ 
  {0x11, 0x11, 0x0E, 0x0A, 0x04}, // A
  {0x1E, 0x11, 0x1E, 0x11, 0x1E}, // B
  {0x0E, 0x11, 0x10, 0x11, 0x0E}, // C
  {0x1C, 0x12, 0x11, 0x12, 0x1C}, // D
  {0x1F, 0x10, 0x1C, 0x10, 0x1F}, // E
  {0x10, 0x10, 0x1C, 0x10, 0x1F}, // F
  {0x0E, 0x11, 0x13, 0x10, 0x0F}, // G
  {0x11, 0x11, 0x1F, 0x11, 0x11}, // H
  {0x1F, 0x04, 0x04, 0x04, 0x1F}, // I
  {0x0E, 0x11, 0x01, 0x01, 0x03}, // J
  {0x11, 0x12, 0x1C, 0x12, 0x11}, // K
  {0x1F, 0x10, 0x10, 0x10, 0x10}, // L
  {0x11, 0x11, 0x15, 0x1B, 0x11}, // M
  {0x11, 0x13, 0x15, 0x19, 0x11}, // N
  {0x0E, 0x11, 0x11, 0x11, 0x0E}, // O
  {0x10, 0x10, 0x1E, 0x11, 0x1E}, // P
  {0x02, 0x0E, 0x15, 0x11, 0x0E}, // Q
  {0x11, 0x11, 0x1E, 0x11, 0x1E}, // R
  {0x1E, 0x01, 0x1F, 0x10, 0x0E}, // S
  {0x04, 0x04, 0x04, 0x04, 0x1F}, // T
  {0x1F, 0x11, 0x11, 0x11, 0x11}, // U
  {0x04, 0x0A, 0x0A, 0x11, 0x11}, // V
  {0x0A, 0x15, 0x15, 0x11, 0x11}, // W
  {0x11, 0x0A, 0x04, 0x0A, 0x11}, // X
  {0x04, 0x04, 0x0A, 0x11, 0x11}, // Y
  {0x1F, 0x08, 0x04, 0x02, 0x1F}  // Z
};

const int columns = 60;
const int strips = 5;
const int pixels = 300;
const int dataPin = 6;
int intensity = 25;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel addressable = Adafruit_NeoPixel(pixels, dataPin, NEO_RGB + NEO_KHZ800);

void setup() {
  pinMode(dataPin, OUTPUT);
  addressable.begin();
  addressable.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  drawString(REDBULL, 10, 0, intensity, 0);
  delay(2000);
  clearString(REDBULL, 10);
  drawString(TURBULL, 13, 0, 0, intensity);
  delay(2000);
  clearString(TURBULL, 13);
  drawString(ENCABULATOR, 0, intensity, intensity, intensity);
  delay(2000);
  clearString(ENCABULATOR, 0);
}

void loop() {
  //drawString("CLIMB ME!", 0, 0, intensity, intensity);
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'd') {
      while (Serial.available() < 5) {
        Serial.println("waiting for displayString parameters.");
      }
      int pos = Serial.read();
      int green = Serial.read();
      int red = Serial.read();
      int blue = Serial.read();
      String text = readString();
      clearString(text, pos);
      Serial.println(text);
      drawString(text, pos, green, red, blue);
    }
  } else if (command == 'c') {
    clearAll();
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

void raw(byte array[]) {
  int arrayLength = sizeof(array) / sizeof(array[0]);
  for (int a = 0; a < arrayLength; a++) {
    int index = a % (pixels - 1);
    addressable.setPixelColor(index, array[0], array[1], array[2]);
  }
  addressable.show();
}

void clearAll() {
  for (int a = 0; a < pixels; a++) {
    addressable.setPixelColor(0, 0, 0, 0);
  }
  addressable.show();
}

void clearPosition(int startPosition) {
  int currentPosition = startPosition;
  int increment = 0;
  for (int a = 0; a < strips; a++) {
    if (a % 2 == 0) {
      increment = 1;
      currentPosition = startPosition + (a * columns);
    } else {
      increment = -1;
      currentPosition = (a * columns) + columns - 1 - startPosition;
    }
    for (int b = 0; b < 5; b++) {
      int offset = b * increment;
      addressable.setPixelColor(currentPosition + offset, 0, 0, 0);
    }   
  }
  addressable.show();
}

void clearString(String string, int startPosition) {
  int stringLength = string.length();
  int currentPosition = startPosition;
  for (int a = 0; a < stringLength; a++) {
    clearPosition(currentPosition);
    currentPosition = currentPosition + 6;
  }
}

void drawString(String string, int startPosition, uint8_t green, uint8_t red, uint8_t blue) {
  int stringLength = string.length();
  int currentPosition = startPosition;
  for (int a = 0; a < stringLength; a++) {
    char c = string.charAt(a);
    int i = (int)c - 32;
    drawAscii(ascii[i], currentPosition, green, red, blue);
    currentPosition = currentPosition + 6;
  }
} 

void drawAscii(byte character[], int startPosition, uint8_t green, uint8_t red, uint8_t blue) {
  int currentPosition = startPosition;
  for (int strip = 0; strip < strips; strip++) {
    byte bChar = character[strip];
    if (strip % 2 == 0) {
      // The strip is even, increment position and boundaries are less than.
      // The upperbound is at the end of the current strip.
      int upperBound = ((strip + 1) * columns);
      int lowerBound = strip * columns;
      currentPosition = startPosition + (strip * columns);
      if (lowerBound <= currentPosition && currentPosition < upperBound) {
        if(bChar & 0x10) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition++;
      if (lowerBound <= currentPosition && currentPosition < upperBound) {
        if (bChar & 0x08) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition++;
      if (lowerBound <= currentPosition && currentPosition < upperBound) {
        if (bChar & 0x04) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition++;
      if (lowerBound <= currentPosition && currentPosition < upperBound) {
        if (bChar & 0x02) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition++;
      if (lowerBound <= currentPosition && currentPosition < upperBound) {
        if (bChar & 0x01) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
    } else {
      // The strip is odd, decrement position and boundaries are greater than or equal to.
      int lowerBound = (strip * columns);
      int upperBound = ((strip + 1) * columns);
      currentPosition = (strip * columns) + columns - 1 - startPosition;
      if (lowerBound <= currentPosition && currentPosition <= upperBound) {
         if(bChar & 0x10) {
           addressable.setPixelColor(currentPosition, green, red, blue);
         }
      }
      currentPosition--;
      if (lowerBound <= currentPosition && currentPosition <= upperBound) {
        if(bChar & 0x08) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition--;
      if (lowerBound <= currentPosition && currentPosition <= upperBound) {
        if (bChar & 0x04) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition--;
      if (lowerBound <= currentPosition && currentPosition <= upperBound) {
        if(bChar & 0x02) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
      currentPosition--;
      if (lowerBound <= currentPosition && currentPosition <= upperBound) {
        if (bChar & 0x01) {
          addressable.setPixelColor(currentPosition, green, red, blue);
        }
      }
    }
  }
  addressable.show();
}

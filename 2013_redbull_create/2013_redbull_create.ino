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
 * This program was written for the 2013 Red Bull Challenge. 
 * We wired an arduino to the Adafruit NeoPixel LED strips as a 
 * marque sign.
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

int red[] = {255,0,0};
int orange[] = {255,127,0};
int yellow[] = {255, 255, 0};
int lightgreen[] = {100,225, 0};
int green[] = {0,225, 0};
int blue[] = {0,0,225};
int indigo[] = {75,0,130};
int violet[] = {143,0,255};
int WR_B_digit = 0;
int AO2_BankB = 1;
int L1N_BankB = 2;
int L2Tur_BankB = 3;
int Dash1_BankA = 4;
int O1_BankA = 5;
int Dash2_BankA = 6;
int T_BankA = 7;
int colorloop = 0;

int letterdigits[] = {4,3,2,1,4,3,2,1};

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
  
  Encabulator.upUpDownDownLeftRightLeftRightBA();
  Encabulator.setVerbose(true);
  
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

int BlueTones(){

//colorloop = colorloop % 8;

  fadeAll2Off();
  for (int i=1; i<=255; i++) {
  delay(50);
  setOne2Color(letterdigits[WR_B_digit],'B',i,0,0);
  delay(50);
  setOne2Color(letterdigits[AO2_BankB],'B',0,i,0);
  delay(50);
  setOne2Color(letterdigits[L1N_BankB],'B',0,0,i);
  delay(50);
  setOne2Color(letterdigits[L2Tur_BankB],'B',(i+56)%255,0,0);
  delay(50);
  setOne2Color(letterdigits[Dash1_BankA],'A',0,(i+56)%255,0);
  delay(50);
  setOne2Color(letterdigits[O1_BankA],'A',0,0,(i+56)%255);
  delay(50);
  setOne2Color(letterdigits[Dash2_BankA],'A',0,(i+56)%255,indigo[2]);
  delay(50);
  setOne2Color(letterdigits[T_BankA],'A',(i+56)%255,violet[1],violet[2]);
  delay(50);
  colorloop++;
  }
}


int freakyrainbow(){
//colorloop = colorloop % 8;
  fadeAll2Off();
  delay(50);
  setOne2Color(letterdigits[(WR_B_digit+colorloop) % 8],'B',red[0],red[1],red[2]);
  delay(50);
  setOne2Color(letterdigits[(AO2_BankB+colorloop) % 8],'B',orange[0],orange[1],orange[2]);
  delay(50);
  setOne2Color(letterdigits[(L1N_BankB+colorloop) % 8],'B',yellow[0],yellow[1],yellow[2]);
  delay(50);
  setOne2Color(letterdigits[(L2Tur_BankB+colorloop) % 8],'B',lightgreen[0],lightgreen[1],lightgreen[2]);
  delay(50);
  setOne2Color(letterdigits[(Dash1_BankA+colorloop) % 8],'A',green[0],green[1],green[2]);
  delay(50);
  setOne2Color(letterdigits[(O1_BankA+colorloop) % 8],'A',blue[0],blue[1],blue[2]);
  delay(50);
  setOne2Color(letterdigits[(Dash2_BankA+colorloop) % 8],'A',indigo[0],indigo[1],indigo[2]);
  delay(50);
  setOne2Color(letterdigits[(T_BankA+colorloop) % 8],'A',violet[0],violet[1],violet[2]);
  delay(50);
  colorloop++;
}

int setAll2Color(int loopy, int R, int G, int B){ //pass in # times to loop, R, G, B
for (int i=1; i<=loopy; i++) {
 for (int j = 1; j<5; j++) {
    Encabulator.stripBankA.jumpHeaderToRGB(j,R,G,B);
    Encabulator.stripBankB.jumpHeaderToRGB(j,R,G,B);     
 }
 }
}

int setOne2Color (int Pos, char bank, int R, int G, int B) {
 if (bank == 'A') {
    Encabulator.stripBankA.jumpHeaderToRGB(Pos,R,G,B);
 } else {
    Encabulator.stripBankB.jumpHeaderToRGB(Pos,R,G,B);
 }
}

int fadeAll2Color (int R, int G, int B) {
for (int i = 1 ; i < 5 ; i++) {
     Encabulator.stripBankA.fadeHeaderToRGB(i,R,G,B,5);
     Encabulator.stripBankB.fadeHeaderToRGB(i,R,G,B,5);
 }
}

int fadeAll2Off () {
for (int i = 1 ; i < 5 ; i++) {
     Encabulator.stripBankA.fadeHeaderToRGB(i,0,0,0,5);
     Encabulator.stripBankB.fadeHeaderToRGB(i,0,0,0,5);
 }
return 0;
}

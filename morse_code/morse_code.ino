/*
 * This sketch blinks morse code.  
 * Connect the output pin to a speaker or a led.
 *
 * 1. The length of a dot is one unit.
 * 2. A dash is three units.
 * 3. The space between parts of the same letter is one unit.
 * 4. The space between letters is three units.
 * 5. The space between words is seven units.
 *
 * @author Matthew Bruzek
 */

int outputPin = 6;  // The pin to send output to.
int outputPin2 = 7; // The second pin to send output to.
int unit = 100;  // The unit of time in milliseconds.
//String message = "SOS";
//String message = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String message = "arduino";

void setup() {                
  // initialize the digital pin as an output.
  pinMode(outputPin, OUTPUT);  
}

void loop() {
  convertString(message);
  wordSpace();
  wordSpace();
  wordSpace();
}

void dot() {
  // The length of a dot is one unit.
  digitalWrite(outputPin, HIGH);
  digitalWrite(outputPin2, HIGH);
  delay(unit);
  digitalWrite(outputPin, LOW);
  digitalWrite(outputPin2, LOW);
}

void dash() {
  // The length of a dash is three units.
  digitalWrite(outputPin, HIGH);
  digitalWrite(outputPin2, HIGH);
  delay(unit * 3);
  digitalWrite(outputPin, LOW);
  digitalWrite(outputPin2, LOW);
}

void letterSpace() {
  // The space between letters is three units.
  delay(unit * 3);
}

void wordSpace() {
  // The space between words is seven units.
  delay(unit * 7);
}

void convertString(String string) {
  string.toUpperCase();
  for (int a = 0; a < string.length(); a++) {
    convertCharacter(string.charAt(a));
    letterSpace();
  }
}

void convertCharacter(char character) {
  // The space between parts of the same letter is one unit.
  switch (character) {
    case ' ':
      wordSpace();
      break;
    case 'A':
      dot(); delay(unit); dash();
      break;
    case 'B':
      dash(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case 'C':
      dash(); delay(unit); dot(); delay(unit); dash(); delay(unit); dot();
      break;
    case 'D':
      dash(); delay(unit); dot(); delay(unit); dot();
      break;
    case 'E':
      dot();
      break;
    case 'F':
      dot(); delay(unit); dot(); delay(unit); dash(); delay(unit); dot();
      break;
    case 'G':
      dash(); delay(unit); dash(); delay(unit); dot();
      break;
    case 'H':
      dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case 'I':
      dot(); delay(unit); dot();
      break;
    case 'J':
      dot(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash();
      break;
    case 'K':
      dash(); delay(unit); dot(); delay(unit); dash();
      break;
    case 'L':
      dot(); delay(unit); dash(); delay(unit); dot(); delay(unit); dot();
      break;
    case 'M':
      dash(); delay(unit); dash();
      break;
    case 'N':
      dash(); delay(unit); dot();
      break;
    case 'O':
      dash(); delay(unit); dash(); delay(unit); dash();
      break;
    case 'P':
      dot(); delay(unit); dash(); delay(unit); dash(); delay(unit); dot();
      break;
    case 'Q':
      dash(); delay(unit); dash(); delay(unit); dot(); delay(unit); dash();
      break;
    case 'R':
      dot(); delay(unit); dash(); delay(unit); dot();
      break;
    case 'S':
      dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case 'T':
      dash();
      break;
    case 'U':
      dot(); delay(unit); dot(); delay(unit); dash();
      break;
    case 'V':
      dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dash();
      break;
    case 'W':
      dot(); delay(unit); dash(); delay(unit); dash();
      break;
    case 'X':
      dash(); delay(unit); dot(); delay(unit); dot(); delay(unit); dash();
      break;
    case 'Y':
      dash(); delay(unit); dot(); delay(unit); dash(); delay(unit); dash();
      break;
    case 'Z':
      dash(); delay(unit); dash(); delay(unit); dot(); delay(unit); dot();
      break;
    case '1':
      dot(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash();
      break;
    case '2':
      dot(); delay(unit); dot(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash();
      break;
    case '3':
      dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dash(); delay(unit); dash();
      break;
    case '4':
      dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dash();
      break;
    case '5':
      dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case '6':
      dash(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case '7':
      dash(); delay(unit); dash(); delay(unit); dot(); delay(unit); dot(); delay(unit); dot();
      break;
    case '8':
      dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dot(); delay(unit); dot();
      break;
    case '9':
      dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dot();
      break;
    case '0':
      dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash(); delay(unit); dash();
      break;
    default:
      wordSpace();
      break;
  }
}



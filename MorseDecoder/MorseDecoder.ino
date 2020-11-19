/* Morse Decoder
 * -... .- -- --- .. ... -- -.-- .-.. .. - - .-.. . -... .- -... -.-- -... --- -.--
 * 
 * three buttons - dot, dash and enter
 * each time enter is pressed work out the character and display it
 * 
 * https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int dotPin = 1;
int dashPin = 2;
int enterPin = 3;
String character = "";
String letters = "";
String morse[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----" 
};
char alphabet[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};


void setup() {
  Serial.begin(9600);
  pinMode(dotPin, INPUT); 
  pinMode(dashPin, INPUT);
  pinMode(enterPin, INPUT);
  //while(!Serial) {} //Wait for the user to open the serial monitor
  lcd.begin(16, 2);
  lcd.clear();
  lcd.noBlink();
  lcd.print("Input morse code");
  lcd.setCursor(0, 1);
}

void loop() {
  receiveInput();
};

void receiveInput() {
  //get each button press: if dot or dash, add it to character, if enter, character is complete so processChar()
  if (digitalRead(dotPin) == LOW) {
    character += ".";
    //make a beep sound
  } else if (digitalRead(dashPin) == LOW) {
    character += "-";
    //make a beeeeep sound
  } else if (digitalRead(enterPin) == LOW) {
    processChar();
    //make some kind of beep sound
  }
};

void processChar() {
  //once the enter button is pressed:
  //convert the morse to english
  //display the morse
  
  for(int i = 0; i <= 36; i++) { //check if morse string is in the morse list
    if (morse[i] == character) {
      character = alphabet[i]; //set character to corresponding english letter
      letters += character;
      Serial.println(character);
      dispChar(); //display the character
    }
  };
  
  character = ""; //reset variable for next character input
};

void dispChar() {
  //https://www.arduino.cc/en/Tutorial/LibraryExamples/LiquidCrystalAutoscroll
  
  if (letters.length() >= 16) {
    lcd.autoscroll();
  };
  lcd.print(character);
};

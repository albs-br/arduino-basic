// https://wokwi.com/projects/354195150222812161

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


#define BACK_SPACE    8
#define SPACE         32
#define ENTER         13


const uint8_t KEYPAD_ROWS = 4;
const uint8_t KEYPAD_COLS = 4;

const byte keyboardRowsPins[KEYPAD_ROWS] = {2, 3, 4, 5};    // Pins connected to R1, R2, R3, R4



const char keysLeft[KEYPAD_ROWS][KEYPAD_COLS] = {
  { 'Q', 'W', 'E', 'R' },
  { 'A', 'S', 'D', 'F' },
  { 'Z', 'X', 'C', 'V' },
  { BACK_SPACE, '1', ',', '.' }
};
const byte keyboardColumnsPins_Left[KEYPAD_COLS] = {6, 7, 8, 9}; // Pins connected to C1, C2, C3, C4
Keypad keypadLeft = Keypad(makeKeymap(keysLeft), keyboardRowsPins, keyboardColumnsPins_Left, KEYPAD_ROWS, KEYPAD_COLS);



const char keysRight[KEYPAD_ROWS][KEYPAD_COLS] = {
  { 'T', 'Y', 'U', 'I' },
  { 'G', 'H', 'J', 'K' },
  { 'B', 'N', 'M', 'O' },
  { SPACE, 'P', 'L', ENTER }
};
const byte keyboardColumnsPins_Right[KEYPAD_COLS] = {10, 11, 12, 13}; // Pins connected to C1, C2, C3, C4
Keypad keypadRight = Keypad(makeKeymap(keysRight), keyboardRowsPins, keyboardColumnsPins_Right, KEYPAD_ROWS, KEYPAD_COLS);


const byte testButtonPins[] = { 10 };


#define I2C_ADDR    0x27
#define LCD_COLUMNS 20
#define LCD_LINES   4

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

//byte testButtonPressed;
byte  cursorX, cursorY;
String currentLine = "";

void setup() {
  Serial.begin(9600); // for debug purposes

  // docs: https://readthedocs.org/projects/arduinoliquidcrystal/downloads/pdf/latest/
  lcd.init();
  //lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();
  lcd.noAutoscroll();
  lcd.display();
  //lcd.autoscroll();
  lcd.cursor();
  lcd.blink();

  cursorX = 0; cursorY = 0;

  //lcd.setCursor(3, 0);
  //lcd.print("Hello, world!");
  //Serial.println("Hello, world!");

  // for (byte i = 0; i < 4; i++) {
  //   //pinMode(ledPins[i], OUTPUT);
  //   pinMode(testButtonPins[i], INPUT_PULLUP);
  // }
  //pinMode(testButtonPins[0], INPUT_PULLUP);

  //testButtonPressed = 0;
}


void loop() {

  lcd.setCursor(cursorX, cursorY);


  // read keyboard
  char key = keypadLeft.getKey();
  if (key == NO_KEY) key = keypadRight.getKey();

  if (key != NO_KEY) {
    if (key == BACK_SPACE) {
      if(cursorX > 0) cursorX--;
      lcd.setCursor(cursorX, cursorY);
      lcd.print(" ");
    }
    else if (key == ENTER) {
      cursorX = 0; cursorY++;
      lcd.setCursor(cursorX, cursorY);
      lcd.print("");
      
      Serial.println(currentLine);
      
      ExecuteLine(currentLine);
      currentLine = "";
    }
    else {
      if(cursorX < (LCD_COLUMNS - 1)) {
        cursorX++;
        lcd.print(key);
        //lcd.write(key);
        currentLine += key;
      }
    }

    //Serial.print(key);
  }


  //CheckTestButton();

  delay(10);
}

void ExecuteLine(String line) {
  // line = trim(line);
  if(line == "CLS") {
    lcd.clear();
    cursorX = 0; cursorY = 0;
  }
  else {
    //lcd.setCursr(1, 1);
    lcd.print("Syntax error");
    cursorY++;
  }
}

// void CheckTestButton() {
//   byte testButtonPin = testButtonPins[0];

//   if (testButtonPressed == 0 && digitalRead(testButtonPin) == LOW) {
//       testButtonPressed = 1;
//   }
//   // check button release
//   else if (testButtonPressed == 1 && digitalRead(testButtonPin) == HIGH) {
//       lcd.print("a");
//       testButtonPressed = 0;
//   }
// }
//#include <EEPROM.h>

#define WINDOWS 1
#define LINUX 2
#define OSX 3

#define LOCKED 1
#define UNLOCKED 2
#define PANIC 3

#define SPEAKER 4

byte lockState;
byte os;

void setup() {
  //  EEPROM.get(0x0, os);
  //  if (os = 0xFF) {
  os = LINUX;
  //  }
  lockState = 0;
  Serial.begin(9600);    // This might move to be pin activated
  delay(10);
  Keyboard.begin();
  delay(1000);

  //  pinMode(1, INPUT);
  //  pinMode(2, INPUT);
  //  pinMode(3, INPUT);

  //  digitalWrite(1, LOW);
  //  digitalWrite(2, LOW);
  //  digitalWrite(3, LOW);

  lock();
}

void lockSound() {
  for (float freq = 415.30; freq <= 440.0; freq += 1.0) {
    tone(SPEAKER, freq);
    delay(1);
  }
}

void lock() {
  // Regain Host OS focus in VMWareWorkstation
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  delay(100);
  Keyboard.releaseAll();
  delay(50);

  // Regain Host OS focus in Virtual Box
  Keyboard.press(KEY_RIGHT_CTRL);
  delay(100);
  Keyboard.releaseAll();
  delay(50);

  switch (os) {
    case WINDOWS:
      Keyboard.press(KEY_LEFT_GUI);  // Left Windows Key
      Keyboard.press('l');           // 'L' key
      Keyboard.releaseAll();
      break;
    case LINUX:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('l');
      break;
    case OSX:
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(0xB8);
      break;
    default:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('l');
      break;
  }
  delay(1000);
  Keyboard.releaseAll();
}

int menuPrompt(char prompt[], int lowerLimit, int upperLimit) {
  int input = 0;
  do {
    Serial.print(prompt);
    Serial.print(F("> "));
    while (Serial.available() <= 0);
    input = (int)Serial.parseInt();
  } while (input < lowerLimit || input > upperLimit);
  while(Serial.available()) {
    Serial.read();
  }
  Serial.println(input, DEC);
  return input;
}

void displayDashes() {
  Serial.println(F("----------------------------------------------------------------------"));
}

String printOS(byte input) {
  switch (input) {
    case WINDOWS:
      Serial.print(F("Windows Vista or higher"));
      break;
    case LINUX:
      Serial.print(F("Linux with GNOME/KDE/Cinnamon/Mate/Unity"));
      break;
    case OSX:
      Serial.print(F("Apple OS X"));
      break;
  }
}

void changeOS() {
  displayDashes();
  Serial.println("===[ Change OS ]===");
  Serial.println(" Current OS:");
  Serial.print(F("   ["));
  printOS(os);
  Serial.println(F(" ]"));
  Serial.print(F("  1) "));
  printOS(WINDOWS);
  Serial.println();
  Serial.print(F("  2) "));
  printOS(LINUX);
  Serial.println();
  Serial.print(F("  3) "));
  printOS(OSX);
  Serial.println();

  os = (byte)menuPrompt("ChangeOS", 1, 3);
//  EEPROM.update(0x0, os);
}

void changePassword() {
  Serial.println(F("===[ Change Password ]==="));
  Serial.println(F("....Place holder...."));
}

void mainMenu() {
  bool finished = false;
  while (!finished) {
    Serial.println(F("===[ USB Wireless Computer Locker configuration menu ]==="));
    displayDashes();
    Serial.println(F("Currently configured to lock/unlock a computer with the following OS:"));
    Serial.print("  [ ");
    printOS(os);
    Serial.println(" ]");
    displayDashes();
    Serial.println(F("  1) Change OS"));
    Serial.println(F("  2) Change password"));
    Serial.println(F("  3) Close serial connection"));
    switch (menuPrompt("MainMenu", 1, 3)) {
      case 1:
        changeOS();
        break;
      case 2:
        changePassword();
        break;
      case 3:
        finished = true;
        break;
    }
  }
  Serial.println(F("Serial session [ CLOSED ]"));
}

void loop() {
  //  byte newState;
  //
  //  if (digitalRead(1) == HIGH) {
  //    newState = 1;
  //  } else if (digitalRead(2) == HIGH) {
  //    newState = 2;
  //  } else if (digitalRead(3) == HIGH) {
  //    newState = 3;
  //  }
  //
  //  if (newState != lockState) {
  //    lockState = newState;
  //    switch (lockState) {
  //      case LOCKED:
  //        lock();
  //        break;
  //      case UNLOCKED:
  //        break;
  //      case PANIC:
  //        break;
  //    }
  //  }
  if (Serial.available() > 0) {
    while (Serial.read() != '\n');  // flush the buffer before outputting menu
    mainMenu();
  }
}

//#include <EEPROM.h>

#define WINDOWS 1
#define LINUX 2
#define OSX 3

#define LOCKED 1
#define UNLOCKED 2
#define PANIC 3

#define SPEAKER 4

byte lockState;
int os;

void setup() {
  //  EEPROM.get(0x0, os);
  //  if (os = 0xFF) {
  os = LINUX;
  //  }
  lockState = 0;
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
}

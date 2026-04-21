#include <LiquidCrystal_I2C.h>
#include <LedControl.h>
#include <EEPROM.h>
#include <ezBuzzer.h>
#include "melody.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
LedControl lc=LedControl(6,10,11,1);
ezBuzzer buzzer(8, BUZZER_TYPE_PASSIVE, HIGH); 

#define MY_LED 12

#define SW_PIN 2
#define X_PIN 1
#define Y_PIN 0

// Led state
long ledDelay = 500;

// Game state
int scoreCount = 0;
int highScore = 0;
long gameTimeOut = 60000;
long gameTimer = 0;
bool isRunning = true;
long pauseTimeOut = 11000;
long pauseTimer = 0;

// Shooter state
int shooterRow = 0;
int shooterCol = 0;
bool shooterLed = false;
long shooterDelay = 100;
long shooterTimer = 0;

// Stopper state
int stopperRow = 4;
int stopperCol = 7;
bool stopperLed = true;

// Joystick reader state
int stick = 0;

// Button reader state
bool button = false;

// Frozen state
bool isFrozen = false;
long gameFrozenOffset = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(MY_LED, OUTPUT);
  pinMode(SW_PIN, INPUT); 
  digitalWrite(SW_PIN, HIGH);
  Serial.begin(9600);

  // Initialize LCD
  printWelcome();

  // Initialize LED matrix
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  lc.setLed(0, 4, 7,true);

  checkHighScoreInit();
}

int i = 0;
// the loop function runs over and over again forever
int col = random (8);
void loop() {
  buzzer.loop();

  ledBlinker();

  buttonReader();

  if (!isFrozen) {
    if (isRunning) {
      joystickReader();
      shooter();
      stopper();
      checkGameOver();
    } else {
      checkPause();
    }
  }
}

void ledBlinker() {
  static long ledtimer = 0;
  static bool ledon = false;

  if ((millis() - ledtimer) > ledDelay) {
    ledtimer = millis();
    ledon = !ledon;
    if (ledon) {
      digitalWrite(MY_LED, HIGH);
      //lc.setLed(0,row,col,false);

      //row = random(8);
    } else {
     digitalWrite(MY_LED, LOW); 
    }
  }
}

void joystickReader() {
  int xval = 0;
  int yval = 0;

  static int prevStick = 0;

  xval = analogRead(X_PIN);
  yval = analogRead(Y_PIN);

  stick = 0;
  if (xval > 900) {
    stick = -1;
  }
  if (xval < 100) {
    stick = 1;
  }
  if (yval > 900) {
    stick = -2;
  }
  if (yval < 100) {
    stick = 2;
  }

  String stickLabel = "CENTER";

  if (stick != prevStick) {
    switch (stick) {
      case 1:
        stickLabel = "DOWN";
        break;
      case -1:
        stickLabel = "UP";
        break;
      case 2:
        stickLabel = "LEFT";
        break;
      case -2:
        stickLabel = "RIGHT";
        break;
      default:
        break;
    }

    if (stick != prevStick) {
      Serial.println(stickLabel);
      prevStick = stick;
    }
  }
}

void buttonReader() {
  const long BUTTON_DELAY = 100;

  static long buttonTime;
  static int prevButton = true;
  static bool  lastButton  = false;

  bool reading = !digitalRead(SW_PIN);
  if (reading !=  lastButton ) {
    buttonTime = millis();
  }
  if (millis() - buttonTime > BUTTON_DELAY) {
    if (reading != button) {
      button = reading;
      if (button) {
        isFrozen = !isFrozen;
        if (isFrozen) {
          ledDelay = 200;
          gameFrozenOffset = millis() - gameTimer;
        } else {
          ledDelay = 500;
          gameTimer = gameTimer + gameFrozenOffset;
        }
        Serial.println(isFrozen);
      }
    }
  }
   lastButton  = reading;
}

void shooter() {
  bool scored = false;

  if ((millis() - shooterTimer) > shooterDelay) {
    shooterTimer = millis();

    if (stopperRow == shooterRow && stopperCol == shooterCol ) {
      scored = true;
      //score = true;
    } else {
      if (shooterCol == 7) {
        buzzer.beep(100, 0, 80);
      }
    }
    if (shooterLed) {
      if (scored) {
        scoreCount++;
        if (shooterDelay > 30) {
          shooterDelay = shooterDelay - 5;
        }
        Serial.print("Score!!!!!!!!!!!!!!!!!!!!!!! ");
        Serial.print(" Delay ");
        Serial.print(shooterDelay);
        Serial.print(" Score ");
        Serial.println(scoreCount);
        buzzer.beep(100, 0, 1500);
        printScore();
        scored = false;
      } else {
        lc.setLed(0,shooterRow,shooterCol,false);
      }
      shooterCol++;
      if (shooterCol > 7) {
        shooterCol = 0;
        shooterRow = random(8);
      }
    } else {
      lc.setLed(0,shooterRow,shooterCol,true);
    }
    shooterLed = !shooterLed;
  }
}

void stopper() {
  long stopperDelay = 150;

  static long stopperTimer = 0;

  static int prevRow = 0;
  static int prevCol = 0;

  if ((millis() - stopperTimer) > stopperDelay) {
    stopperTimer = millis();
    if (stick == -1) {
      lc.setLed(0,stopperRow,stopperCol,false);
      stopperRow++;
      if (stopperRow > 7) stopperRow = 0;
      lc.setLed(0,stopperRow,stopperCol,true);
    }
    if (stick == 1) {
      lc.setLed(0,stopperRow,stopperCol,false);
      stopperRow--;
      if (stopperRow < 0) stopperRow = 7;
      lc.setLed(0,stopperRow,stopperCol,true);
    }
  }
}

void checkGameOver() {
  if ((millis() - gameTimer) > gameTimeOut) {
    gameTimer = millis();
    shooterDelay = 100;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YOUR SCORE: ");
    lcd.print(scoreCount);
    lcd.setCursor(0, 1);
    if (scoreCount > highScore) {
      int length = sizeof(winNoteDurations) / sizeof(int);
      buzzer.playMelody(winMelody, winNoteDurations, length);
      highScore = scoreCount;
      storeHighScore();
      lcd.print("NEW HIGH SCORE!!");

    } else {
      int length = sizeof(noteDurations) / sizeof(int);
      buzzer.playMelody(melody, noteDurations, length);
      lcd.print("HIGH SCORE: ");
      lcd.print(highScore);
    }

    scoreCount = 0;
    startPause();
  }
}

void startPause() {
  Serial.println("Enter pause");
  pauseTimer = millis();
  isRunning = false;
}

void checkPause() {
  if ((millis() - pauseTimer) > pauseTimeOut) {
    Serial.println("Exit pause");
    pauseTimer = millis();
    isRunning = true;
    buzzer.stop();
    printWelcome();
  }
}

void printScore() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your score: ");
  lcd.print(scoreCount);
  lcd.setCursor(0, 1);
  lcd.print("High score: ");
  lcd.print(highScore);
}

void printWelcome() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO:");
  lcd.setCursor(0, 1);
  lcd.print("BOUNCY SHIELD!!!");
}

bool checkHighScoreInit() {
  int addr_I = EEPROM.length() - 2;
  int addr_N = EEPROM.length() - 1;

  if (EEPROM.read(addr_I) == 'I' && EEPROM.read(addr_N) == 'N') {
    highScore = EEPROM.read(0);
    return false; 
  } else {
    highScore = 0;
    EEPROM.update(0, highScore);
    
    // Write the "IN" signature
    EEPROM.update(addr_I, 'I');
    EEPROM.update(addr_N, 'N');
    return true; 
  }
}

void storeHighScore() {
  EEPROM.update(0, highScore);
}
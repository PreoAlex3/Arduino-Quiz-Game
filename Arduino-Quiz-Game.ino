#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int greenLed = 10;
int redLed = 13;
int greenButton = 7;
int greenState = 0;
int greenStatePrev = 0;
int greenCounter = 0;
int redButton = 6;
int redState = 0;
int redStatePrev = 0;
int redCounter = 0;

enum State {
    initial,
    choice,
    right,
    wrong
};
State state = initial;

int buzzer = 9;
int first = 0;

// Frequencies for win and lose tones
const int winFrequencies[] = {261, 329, 392}; // C4, E4, G4 (a C major chord)
const int loseFrequencies[] = {440, 392, 349}; // A4, G4, F4 (a descending tone)

// Duration of each note (in milliseconds)
const int noteDuration = 200;

void setup() {
  lcd.begin(16, 2);
  pinMode(greenButton, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redButton, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void winSound() {
  for (int i = 0; i < 3; i++) {
    tone(buzzer, winFrequencies[i], noteDuration);
    delay(noteDuration);
  }
  noTone(buzzer); // Stop the buzzer
}

void loseSound() {
  for (int i = 0; i < 3; i++) {
    tone(buzzer, loseFrequencies[i], noteDuration);
    delay(noteDuration);
  }
  noTone(buzzer); // Stop the buzzer
}

void loop() {
  greenStatePrev = greenState;
  redStatePrev = redState;
  greenState = digitalRead(greenButton);
  redState = digitalRead(redButton);

  switch(state){
    case initial:
            if(first == 0)
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Press any button");
              lcd.setCursor(0, 1);
              lcd.print("to start");
              first = 1;
            }
            if((greenState == HIGH && greenStatePrev == LOW )|| (redState == HIGH && redStatePrev == LOW))
            {
              state = choice;
              first = 0;
            }
                 
            break;
    case choice:
            if(first == 0)
            {
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Earth is round?");
              lcd.setCursor(0, 1);
              lcd.print("YES");
              lcd.setCursor(5, 1);
              lcd.print("NO");
              first = 1;
            }
            if(greenState == HIGH && greenStatePrev == LOW )
            {
              state = right;
              first = 0;
            }
              
            if(redState == HIGH && redStatePrev == LOW)
            {
              state = wrong;
              first = 0;
            }
            
            break;
    case right:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("You chose yes");
            delay(2000);
            lcd.setCursor(0, 1);
            lcd.print("Right");
            digitalWrite(greenLed, HIGH);

            winSound();
            delay(3000);
            lcd.clear();
            digitalWrite(greenLed, LOW);

            state = initial;
            break;
    case wrong:
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("You chose no");
            delay(2000);
            lcd.setCursor(0, 1);
            lcd.print("Wrong");
            digitalWrite(redLed, HIGH);

            loseSound();
            delay(3000);
            lcd.clear();
            digitalWrite(redLed, LOW);

            state = initial;
            break;
    default:
            break;
  }
}
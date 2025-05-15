
#include <Keyboard.h>

#define DEBOUNCE 500

#define pinLedPlayer1_1 5//לד צהוב 
#define pinLedPlayer1_2 4//לד ירוק 
#define pinLedPlayer2_1 3//לד כחול 
#define pinLedPlayer2_2 2//לד אדום 
#define pinBtnPlayer1_1 9//כפתור צהוב 
#define pinBtnPlayer1_2 8//כפתור ירוק 
#define pinBtnPlayer2_1 6 //כפתור אדום
#define pinBtnPlayer2_2 7 //כפתור כחול

unsigned long LastOnTime;
bool gameStarted = false;
int OnPrd = 1000;
bool isLedOn;

int lastBtnValPlayer1_1;
int lastBtnValPlayer1_2;
int lastBtnValPlayer2_1;
int lastBtnValPlayer2_2;
unsigned long lastBtnPressTimePlayer1_1;
unsigned long lastBtnPressTimePlayer1_2;
unsigned long lastBtnPressTimePlayer2_1;
unsigned long lastBtnPressTimePlayer2_2;


unsigned long startTime = 0;  // משתנה לאחזור הזמן הנוכחי
unsigned long elapsedTime = 0;  // משתנה לאחזור זמן שחלף

int scorePlayer1 = -1;
int scorePlayer2 = 0;

void setup() {
  pinMode(pinLedPlayer1_1, OUTPUT);
  pinMode(pinLedPlayer1_2, OUTPUT);
  pinMode(pinLedPlayer2_1, OUTPUT);
  pinMode(pinLedPlayer2_2, OUTPUT);
  pinMode(pinBtnPlayer1_1, INPUT_PULLUP);
  pinMode(pinBtnPlayer1_2, INPUT_PULLUP);
  pinMode(pinBtnPlayer2_1, INPUT_PULLUP);
  pinMode(pinBtnPlayer2_2, INPUT_PULLUP);

  Serial.begin(9600);
  Keyboard.begin();
  randomSeed(analogRead(A1));
  // LedOff();  // Turn off all LEDs initially
  LastOnTime = millis();

  LedOn();
  //LastOnTime = millis();
  lastBtnValPlayer1_1 = digitalRead(pinBtnPlayer1_1);
  lastBtnPressTimePlayer1_1 = millis();
  lastBtnValPlayer1_2 = digitalRead(pinBtnPlayer1_2);
  lastBtnPressTimePlayer1_2 = millis();
  lastBtnValPlayer2_1 = digitalRead(pinBtnPlayer2_1);
  lastBtnPressTimePlayer2_1 = millis();
  lastBtnValPlayer2_2 = digitalRead(pinBtnPlayer2_2);
  lastBtnPressTimePlayer2_2 = millis();

  //startTime = millis();
}

void loop() {
  int btnValPlayer1_1 = digitalRead(pinBtnPlayer1_1);
  int btnValPlayer1_2 = digitalRead(pinBtnPlayer1_2);
  int btnValPlayer2_1 = digitalRead(pinBtnPlayer2_1);
  int btnValPlayer2_2 = digitalRead(pinBtnPlayer2_2);
 int start ;
  

  if (!gameStarted) {
    if ( btnValPlayer2_2 == LOW) {
      gameStarted = true;
      startTime = millis();
      

    }
  }
   elapsedTime = millis() - startTime;
  if (elapsedTime >= 60000 ){
    LedOff();
   // Serial.println("עברה דקה!");
    if( btnValPlayer2_2 == LOW){
      gameStarted = true;
      startTime = millis();
    }
  }
  else{
    
    
   if (gameStarted) {

  if ((btnValPlayer1_1 == LOW) && (lastBtnValPlayer1_1 == HIGH) && (millis() - lastBtnPressTimePlayer1_1 > DEBOUNCE)) {
    lastBtnPressTimePlayer1_1 = millis();
    scorePlayer1 += (isLedOn) ? 1 : -1;
       if(isLedOn){
         Keyboard.write('C');
         //Serial.print('C');

      }
      else {
      Keyboard.write('D');
      //Serial.print('D');
      }
    }
  if ((btnValPlayer1_2 == LOW) && (lastBtnValPlayer1_2 == HIGH) && (millis() - lastBtnPressTimePlayer1_2 > DEBOUNCE)) {
    lastBtnPressTimePlayer1_2 = millis();
    scorePlayer1 += (isLedOn) ? 1 : -1;
    if(isLedOn){
     Keyboard.write('C');
     //Serial.print('C');
    }
     else {
      Keyboard.write('D');
      //Serial.print('D');
    }
  }
  if ((btnValPlayer2_1 == LOW) && (lastBtnValPlayer2_1 == HIGH) && (millis() - lastBtnPressTimePlayer2_1 > DEBOUNCE)) {
    lastBtnPressTimePlayer2_1 = millis();
    scorePlayer2 += (isLedOn) ? 1 : -1;
    if(isLedOn){
     Keyboard.write('A');
     //Serial.print('A');
    }
     else {
      Keyboard.write('B');
     //Serial.print('B');
    }
  }
  if ((btnValPlayer2_2 == LOW) && (lastBtnValPlayer2_2 == HIGH) && (millis() - lastBtnPressTimePlayer2_2 > DEBOUNCE)) {
    lastBtnPressTimePlayer2_2 = millis();
    scorePlayer2 += (isLedOn) ? 1 : -1;
    if(isLedOn){
      Keyboard.write('A');
     //Serial.print('A');
    }
     else {
      Keyboard.write('B');
      //Serial.print('B');
    }
  }

  lastBtnValPlayer1_1 = btnValPlayer1_1;
  lastBtnValPlayer1_2 = btnValPlayer1_2;
  lastBtnValPlayer2_1 = btnValPlayer2_1;
  lastBtnValPlayer2_2 = btnValPlayer2_2;

   if (millis() - LastOnTime >= OnPrd) {
    toggleLed();
    OnPrd = chooseNewPrd();
   } 
  } 
  else {
    LedOff();  // Turn off all LEDs while waiting for the game to start
  }


  // Serial.print("Player 1 Score: ");
  // Serial.println(scorePlayer1);

  // Serial.print("Player 2 Score: ");
  // Serial.println(scorePlayer2);
  }
  
}

int chooseNewPrd() {
  int num = random(50,800);
  //Serial.println(num);
  return num;
}

void toggleLed() {
  LastOnTime = millis();
  if (isLedOn) {
    LedOff();
  } else {
    LedOn();
  }
}

void LedOn() {
  
  digitalWrite(pinLedPlayer1_1, random(2) ? HIGH : LOW);
  digitalWrite(pinLedPlayer1_2, random(2) ? HIGH : LOW);
  digitalWrite(pinLedPlayer2_1, random(2) ? HIGH : LOW);
  digitalWrite(pinLedPlayer2_2, random(2) ? HIGH : LOW);
  isLedOn = true;
}

void LedOff() {
  isLedOn = false;
  digitalWrite(pinLedPlayer1_1, LOW);
  digitalWrite(pinLedPlayer1_2, LOW);
  digitalWrite(pinLedPlayer2_1, LOW);
  digitalWrite(pinLedPlayer2_2, LOW);
}

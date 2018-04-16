#include <Arduino.h>
#include <EEPROM.h>

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4

#define FI_STATE_0 10
#define FI_STATE_A 11
#define FI_STATE_B 12
#define FI_STATE_C 13
#define FI_STATE_MAX 3

int FI_STATE = FI_STATE_0;

void setup()
{
  if(EEPROM.read(9) == 127){
    FI_STATE = EEPROM.read(10);
    if(FI_STATE >= FI_STATE_0 + FI_STATE_MAX){
      EEPROM.write(10, FI_STATE_0);
    }else{
      EEPROM.write(10, FI_STATE + 1);
    }
  }else{
    FI_STATE = FI_STATE_0;
    EEPROM.write(9, 127);
    EEPROM.write(10, FI_STATE);
  }

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

int zero[] = {0, 0, 0, 0, 0};
int i[] = {0, 17, 31, 17, 0};
int love[] = {12, 30, 15, 30, 12};
int u[] = {30, 1, 1, 30, 0};

void displayLED(int _line)
{
  if (_line>=16) {digitalWrite(LED1, HIGH); _line-=16;} else {digitalWrite(LED1, LOW);}
  if (_line>=8)  {digitalWrite(LED2, HIGH); _line-=8;}  else {digitalWrite(LED2, LOW);}
  if (_line>=4)  {digitalWrite(LED3, HIGH); _line-=4;}  else {digitalWrite(LED3, LOW);}
  if (_line>=2)  {digitalWrite(LED4, HIGH); _line-=2;}  else {digitalWrite(LED4, LOW);}
  if (_line>=1)  {digitalWrite(LED5, HIGH); _line-=1;}  else {digitalWrite(LED5, LOW);}
}

void loop()
{
  for (int led = 0; led <5; led++){
    if(FI_STATE == FI_STATE_0){
      displayLED(zero[led]);
    }else if(FI_STATE == FI_STATE_A){
      displayLED(i[led]);
    }else if(FI_STATE == FI_STATE_B){
      displayLED(love[led]);
    }else if(FI_STATE == FI_STATE_C){
      displayLED(u[led]);
    }
    delay(3);
  }
  displayLED(0);
  delay(30);
}

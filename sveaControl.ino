#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "menuItem.h"
#include "menuItemBoolean.h"
#include "menuItemManager.h"
#include "PCF8574.h"


#define LCD_RS 8
#define LCD_EN 9
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BL 10
#define KEY_PIN A0 // A0

#define BACKLIGHTSAVE 60
#define SCREENSAVE 600

#define ACC0 0 // Dont use, serial
#define ACC1 1 // Dont use, serial
#define GPS_RX 2
#define ACC3 3
#define ACC4 11
#define ACC5 12
#define ACC6 13
#define ACC7 18
#define ACC8 19



#define NUM_KEYS 3
int adcKeyVal[3] ={598,408,137};
int key=-1;
int oldkey=-1;
#define DOWN 0
#define UP 1
#define SELECT 2

long lastKeyPress=0;

byte AwithRing[8] = {
  B00100,
  B01010,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
};

byte AwithDots[8] = {
  B01010,
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
};
  
byte OwithDots[8] = {
  B01010,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
};
  
LiquidCrystal lcd(LCD_RS,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7);
PCF8574 PCF(0x20);


menuItemManager mim;
menuItem *curr;

menuItemBoolean first("Sovrumsfl\2kt", 1, 0);
menuItemBoolean second("V\2derfax", 2, 1);
menuItemBoolean third("Garderob", 3, 2);
menuItem backlight("Bakgrundsbelysn", 0, -1, 0, 100);

int state=0;


void setup() {
  lcd.begin(16, 2);
  pinMode(LCD_BL, OUTPUT);

  lcd.createChar(1, AwithRing);
  lcd.createChar(2, AwithDots);
  lcd.createChar(3, OwithDots);

  mim.addMenuItem(&first);
  mim.addMenuItem(&second);
  mim.addMenuItem(&third);
  mim.addMenuItem(&backlight);

  curr = mim.getFirst();
  do {
    updateRelay(curr);
    curr = curr->getNext();
  } while(curr != mim.getFirst());

  updateDisplay();
}

void loop() {
  key = getKey(analogRead(KEY_PIN));    // We get the button pressed

  if (key != oldkey)   // if keypress is detected
  {
    delay(50);  // Expected to avoid bouncing pulsations
    key = getKey(analogRead(KEY_PIN));    // We get the button pressed
    oldkey = key;

    if(millis() - lastKeyPress > 1000L*BACKLIGHTSAVE)  key = -1;
    
    lastKeyPress = millis();
    switch(key) {
      case UP:
        if(state == 0) curr = curr->getPrev();
        if(state == 1) curr->incValue();
        break;
      case DOWN:
        if(state == 0) curr = curr->getNext();
        if(state == 1) curr->decValue();
        break;
      case SELECT:
        if(state == 0) 
        {
          state=1;
        } 
          else
        {
          state=0;
        }
        break;
    }
    updateRelay(curr);
    updateDisplay();

  }

  if(millis() - lastKeyPress > 1000L*BACKLIGHTSAVE) {
    analogWrite(LCD_BL, 0);
  } else {
    analogWrite(LCD_BL, backlight.getInteger()*255/100);
  }

  if(SCREENSAVE != -1 && millis() - lastKeyPress > 1000L*SCREENSAVE) {
    lcd.noDisplay();
  } else {
    lcd.display();
  }
}

void updateDisplay()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(curr->getName());
  lcd.setCursor(0, 1);
  lcd.print(curr->getValue());
  if(state == 0) {
    lcd.noBlink();
  } else {
     lcd.blink();
  }

}

void updateRelay(menuItem *c)
{
  if(c->getRelay() != -1) {
    PCF.write(c->getRelay(), c->getInteger() == 0);
  }
}

int getKey(int input) {
  int k=-1;
  for (k = 0; k < NUM_KEYS; k++)  {
    if (input > adcKeyVal[k])    {
      return k;
    }
  }
  if (k >= NUM_KEYS) k = -1;  // Error in reading.
  return k;
}

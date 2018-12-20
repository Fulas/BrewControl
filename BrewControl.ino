#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Key A0  //Boton
#define TempWaterInput A1  //Temp Watter
#define TempOilInput A2  //Temp Oil

unsigned long sumWater = 0;
unsigned long sumOil = 0;
unsigned long start;
unsigned int counter;

float tempWater;
float tempOil;

float tempWaterSetpoint = 70;
float tempOilSetpoint = 100;

//lcd is a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  Serial.begin (9600); // 9600 bps
  lcd.begin(20, 4);
  Wire.begin();
  pinMode(TempWaterInput, INPUT);
  pinMode(TempOilInput, INPUT);
  pinMode(Key, INPUT);
  for (int i = 2; i <= 6; i++)//Auto1-Auto5
  {
    pinMode(i, INPUT);
  }
  for (int i = 7; i <= 11; i++)//Res1-Res5
  {
    pinMode(i, OUTPUT);
  }
  start = millis();
  counter = 0;
  lcd.setCursor(0, 0);
  lcd.print("AGUA  ACEITE");
}

void loop()
{
  sumWater += analogRead(TempWaterInput);
  sumOil += analogRead(TempWaterInput);
  counter++;

  if (millis() - start > 1000UL) { // 1000 milisegundos = 1seg
    Temp();
    Control();
    sumWater = 0;
    sumOil = 0;
    counter = 0;
    start = millis();
  }
  Menu();
}

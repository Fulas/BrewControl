#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Key A0  //Boton
#define TempWaterInput A1  //Temp Watter
#define TempOilInput A2  //Temp Oil

int adc_key_val [5] = {50, 200, 400, 600, 800};
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;

//lcd is a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3,POSITIVE);

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
}

void loop()
{
  float SetTemp;
  lcd.setCursor(0, 0);
  Temp();
  Menu();
  Control();
}

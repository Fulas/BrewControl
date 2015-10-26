#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EmonLib.h>  // Include Emon Library
EnergyMonitor emon1;  // Create an instance
#define TempWaterVoltInput A1  //Temp Watter
#define TempOilVoltInput A2  //Temp Oil
//lcd is a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x20, 20, 4);
//set the lcd address to 0x27 for real
//set the lcd address to 0x20 for simulation

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(TempWaterVoltInput, INPUT);
  pinMode(TempOilVoltInput, INPUT);
  emon1.current(1, 111.1); // Current: input pin, calibration.
}

void loop()
{
  lcd.setCursor(0, 0);
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  delay(500);
  temp();
  //lcd.print(Irms * 230.0); // Apparent power
  //lcd.println(Irms);  // Irms
}

void temp()
{
  float TemWaterVolt;
  float TempOilVolt;
  float TempWater;
  float TempOil;
  TemWaterVolt = analogRead(TempWaterVoltInput);
  TempOilVolt = analogRead(TempOilVoltInput);
  //Temp Water
  //T=50*V-100
  //0C-->2V-->409
  //150C-->5V-->1023
  lcd.setCursor(0, 0);
  if (TemWaterVolt < 410) {
    lcd.print("Error");
  }
  if (TemWaterVolt > 409) {
    TempWater = map(TemWaterVolt, 410, 1023, 0, 150);
    lcd.print(TempWater, 2);
  }
  //Temp Oil
  //T=100*V-100
  //0C-->1V-->204
  //400C-->5V-->1023
  lcd.setCursor(7, 0);
  if (TempOilVolt < 205) {
    lcd.print("Error");
  }
  if (TempOilVolt > 204) {
    TempOil = map(TempOilVolt, 205, 1023, 0, 400);
    lcd.print(TempOil, 2);
  }
}


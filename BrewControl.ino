#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EmonLib.h>  // Include Emon Library
EnergyMonitor emon1;  // Create an instance
#define Tinput A0
float Tvoltage;
float Temp;
//lcd is a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
//set the lcd address to 0x27 for real
//set the lcd address to 0x20 for simulation

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(Tinput, INPUT);
  emon1.current(1, 111.1); // Current: input pin, calibration.
}

void loop()
{
  lcd.setCursor(0, 0);
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  delay(500);
  Tvoltage = analogRead(Tinput);
  if (Tvoltage < 410) {
    lcd.clear();
    lcd.print("Error");
  }
  if (Tvoltage > 409) {
    Tvoltage = map(Tvoltage, 410, 1023, 0, 614);
    Temp = (150 * Tvoltage) / 614;
    lcd.clear();
    lcd.print(Temp, 2);
  }
  //lcd.print(Irms * 230.0); // Apparent power
  //lcd.println(Irms);  // Irms
}
//250ohm
//U=R*I        
//8mA-->0-->2V-->409            
//20mA-->150-->5V-->1023

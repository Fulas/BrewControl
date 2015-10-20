#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EmonLib.h>  // Include Emon Library
EnergyMonitor emon1;  // Create an instance
LiquidCrystal_I2C lcd(0x27,20,4); //set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
    lcd.init();
    lcd.backlight();
    emon1.current(1, 111.1); // Current: input pin, calibration.

}
void loop()
{
    lcd.setCursor(0, 0);
    double Irms = emon1.calcIrms(1480);  // Calculate Irms only

    lcd.print(Irms*230.0);  // Apparent power
    lcd.print(" ");
    lcd.println(Irms);  // Irms
    
    delay(100);
}

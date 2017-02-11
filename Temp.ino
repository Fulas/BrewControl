void Temp()//PRINT:Temp Watter Temp Oil
{
  float TempWater=0;
  float TempOil=0;
  for (int i=0; i <= 10; i++)
  {
    TempWater = TempWater+analogRead(TempWaterInput);
    TempOil = TempOil+analogRead(TempOilInput);
  }
  TempWater = TempWater/10;
  TempOil = TempOil/10;
  
  //Temp Water
  //250ohm
  //U=R*I
  //8mA-->0-->2V-->409
  //20mA-->150-->5V-->1023
  lcd.setCursor(0, 0);
  if (TempWater < 410) {
    lcd.print("Error");
  }
  if (TempWater > 409) {
    TempWater = map(TempWater, 410, 1023, 0, 614);
    TempWater = (150 * TempWater) / 614;
    lcd.print(TempWater, 2);
  }
  
  //Temp Oil
  //250ohm
  //U=R*I
  //4mA-->0-->1V-->205
  //20mA-->600-->5V-->1023
  lcd.setCursor(7, 0);
  if (TempOil < 205) {
    lcd.print("Error");
  }
  if (TempOil > 204) {
    TempOil = map(TempOil, 205, 1023, 0, 614);
    TempOil = (600 * TempOil) / 614;
    lcd.print(TempOil, 2);
  }
}

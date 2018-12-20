void Temp()//PRINT: tempWatter tempOil
{
  tempWater=sumWater/counter;
  tempOil=sumOil/counter;
  
  //Temp Water
  //250ohm
  //U=R*I
  //8mA-->0-->2V-->409
  //20mA-->150-->5V-->1023
  lcd.setCursor(0, 1);
  if (tempWater < 410) {
    lcd.print("Error");
  }
  if (tempWater > 409) {
    tempWater = map(tempWater, 410, 1023, 0, 614);
    tempWater = (150 * tempWater) / 614;
    lcd.print(tempWater, 2);
  }
  
  //Temp Oil
  //250ohm
  //U=R*I
  //4mA-->0-->1V-->205
  //20mA-->600-->5V-->1023
  lcd.setCursor(7, 1);
  if (tempOil < 205) {
    lcd.print("Error");
  }
  if (tempOil > 204) {
    tempOil = map(tempOil, 205, 1023, 0, 614);
    tempOil = (600 * tempOil) / 614;
    lcd.print(tempOil, 2);
  }
}

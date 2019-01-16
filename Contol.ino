void Control()//PRINT:PowerOn (0-5)
{
  int powerOn = 0;
  int hysteresis = 2;
  float x = 0.8;

  //OIL
  //Rising
  for (int i = 5; i >= 1; i--)
  {
    if (toPowerOn == i && tempOil > tempOilSetpoint * x)
    {
      toPowerOn = i - 1;
    }
    x += 0.05;
  }
  //Falling
  for (int i = 0; i <= 4; i++)
  {
    if (toPowerOn == i && tempOil < tempOilSetpoint * x - hysteresis)
    {
      toPowerOn = i + 1;
    }
    x -= 0.05;
  }

  lcd.setCursor(0, 3);
  lcd.print(toPowerOn);
  lcd.setCursor(2, 3);

  for (int i = 2; i <= 6 ; i++)//Auto1-Auto5
  {
    if (digitalRead(i) == true && powerOn < toPowerOn)
    {
      digitalWrite(i + 5, HIGH);//Res ON
      powerOn++;
      lcd.print("+ ");
    }
    else
    {
      digitalWrite(i + 5, LOW);//Res OFF
      lcd.print("- ");
    }
  }

  //WATER
  if (pump == "AUT" && tempWater < tempWaterSetpoint - hysteresis)
    digitalWrite(PumpOutput, HIGH);//Pump ON
  else if (pump == "MAN" || tempWater >= tempWaterSetpoint )
    digitalWrite(PumpOutput, LOW);//Pump OFF

}

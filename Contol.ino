void Control()//PRINT:PowerOn (0-5)
{
  int toPowerOn = 0;
  int powerOn = 0;
  int hysteresis = 2;
  int x = 1;

  //OIL
  for (int i = 1; i <= 5 ; i++)
  {
    if (tempOil < tempOilSetpoint * x - hysteresis && tempOil >= tempOilSetpoint * (x - 0.05))
    {
      toPowerOn = i;
    }
    x-=0.05;
  }

  lcd.setCursor(0, 4);
  lcd.print(toPowerOn);
  lcd.setCursor(3, 4);

  for (int i = 2; i <= 6 ; i++)//Auto1-Auto5
  {
    if (digitalRead(i) == true && powerOn < toPowerOn)
    {
      digitalWrite(i + 5, HIGH);//Res ON
      powerOn++;
      lcd.print(i - 1);
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

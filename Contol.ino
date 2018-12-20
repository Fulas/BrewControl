void Control()//PRINT:Num (Auto 1-5) PowerOn (Res 1-5)
{
  int PowerOn = 0, ToPowerOn = 0;
  int Num = Auto();

  for (int i = 2; i <= 6 ; i++) //Auto1-Auto5
  {
    if (digitalRead(i) == true && PowerOn < ToPowerOn)
    {
      if (2<=i<=3)
      {
        if (PowerOn+3 <= ToPowerOn)
        {
          digitalWrite(i + 5, HIGH);//Res1-Res5
          PowerOn=PowerOn+3;
          lcd.print(i-1);
        }
        else
          digitalWrite(i + 5, LOW);//Res1-Res5
      }
      else
      {
        digitalWrite(i + 5, HIGH);//Res1-Res5
        PowerOn++;
        lcd.print(i-1);
      }
    }
    else
      digitalWrite(i + 5, LOW);//Res1-Res5
  }
}

int Auto()
{
  int Num = 0;
  for (int i = 2; i <= 6; i++)//Auto1-Auto5
  {
    if (digitalRead(i) == true)
    {
      if(2<=i<=3)
      {
        Num=Num+2;
      }
      Num++;
    }
  }
  return Num;
}

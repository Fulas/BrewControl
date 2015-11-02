#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
#include <EmonLib.h>  // Include Emon Library
EnergyMonitor emon1;  // Create an instance
#define TempWaterInput A1  //Temp Watter
#define TempOilInput A2  //Temp Oil

//lcd is a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x20, 20, 4);
//set the lcd address to 0x27 for real
//set the lcd address to 0x20 for simulation

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp = 1, consKi = 0.05, consKd = 0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(TempWaterInput, INPUT);
  pinMode(TempOilInput, INPUT);
  for (int i = 2; i <= 6; i++)//Auto1-Auto6
  {
    pinMode(i, INPUT);
  }
  for (int i = 7; i <= 11; i++)//Res1-Res6
  {
    pinMode(i, OUTPUT);
  }
  emon1.current(1, 111.1); // Current: input pin, calibration.
  //initialize the variables we're linked to
  Input = analogRead(TempWaterInput);
  Setpoint = 700;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  float SetTemp;
  lcd.setCursor(0, 0);
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  delay(500);
  Temp();
  //Menu();
  Control();
  //Time();
  //Consumption();
  //delay(1000);
  //lcd.clear();
  //lcd.print(Irms * 230.0); // Apparent power
  //lcd.println(Irms);  // Irms
}

void Temp()
{
  float TempWater, TempOil;
  TempWater = analogRead(TempWaterInput);
  TempOil = analogRead(TempOilInput);
  //Temp Water
  //T=50*V-100
  //0C-->2V-->409
  //150C-->5V-->1023
  lcd.setCursor(0, 0);
  if (TempWater < 410) {
    lcd.print("Error");
  }
  if (TempWater > 409) {
    TempWater = map(TempWater, 410, 1023, 0, 150);
    lcd.print(TempWater, 2);
  }
  //Temp Oil
  //T=100*V-100
  //0C-->1V-->204
  //400C-->5V-->1023
  lcd.setCursor(7, 0);
  if (TempOil < 205) {
    lcd.print("Error");
  }
  if (TempOil > 204) {
    TempOil = map(TempOil, 205, 1023, 0, 400);
    lcd.print(TempOil, 2);
  }
}

int Auto()
{
  int Num = 0;
  for (int i = 2; i <= 6; i++)//Auto1-Auto6
  {
    if (digitalRead(i) == true)
    {
      Num++;
    }
  }
  return Num;
}

void Control()
{
  
  int PowerOn, ToPowerOn;
  double Num;
  double gap = abs(Setpoint - Input); //distance away from setpoint
  Num=Auto();
  myPID.SetOutputLimits(0,Num);
  Input = analogRead(TempWaterInput);
  if (gap < 10)
  { //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
    //we're far from setpoint, use aggressive tuning parameters
    myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute();
  lcd.setCursor(0, 1);
  lcd.print(Num);
  lcd.print(" ");
  lcd.print(Output);

  ToPowerOn=Output;

  for (int i = 2; i <= 6 ; i++) //Auto1-Auto6
  {
    if (digitalRead(i) == true && PowerOn < ToPowerOn)
    {
      digitalWrite(i + 5, HIGH);//Res1-Res6
      PowerOn++;
    }
    else
      digitalWrite(i + 5, LOW);//Res1-Res6
  }
}


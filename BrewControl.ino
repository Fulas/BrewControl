#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

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
//set the lcd address to 0x27 for real
//set the lcd address to 0x20 for simulation

//Define Variables we'll be connecting to
double Setpoint = 682, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp = 1, consKi = 0.05, consKd = 0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

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
  Input = analogRead(TempWaterInput);
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  float SetTemp;
  lcd.setCursor(0, 0);
  Temp();
  Menu();
  Control();
  //delay(1000);
  //lcd.clear();
}

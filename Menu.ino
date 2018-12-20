int adc_key_val [5] = {50, 200, 400, 600, 800};
int NUM_KEYS = 5;
int adc_key_in;
int key = -1;
int oldkey = -1;
String option="water";

void Menu()//PRINT: tempWaterSetpoint tempOilSetpoint
{
  adc_key_in = analogRead (Key); // read the value from the sensor
  key = get_key (adc_key_in); // convert into key press
  if (key != oldkey) // if keypress is detected
  {
    delay (50); // wait for debounce time
    adc_key_in = analogRead (Key); // read the value from the sensor
    key = get_key (adc_key_in); //  convert into key press
    if (key >= 0) {
      switch (key)
      {
        case 0: //Left
          if (option=="water")
            option = "oil";
          else if (option=="oil")
            option = "water";
          break;
        case 1: //Down
          if (option=="water")
            tempWaterSetpoint -= 0.5;
          else if (option=="oil")
            tempOilSetpoint -= 0.5;
          break;
        case 2: //Up
          if (option=="water")
            tempWaterSetpoint += 0.5;
          else if (option=="oil")
            tempOilSetpoint += 0.5;
          break;
        case 3: //Right
          if (option=="water")
            option = "oil";
          else if (option=="oil")
            option = "water";
          break;
        case 4: Serial.println ("S5 OK"); //Ok
          break;
      }
    }
  }
  lcd.setCursor(0, 3);
  lcd.print(tempWaterSetpoint, 1);
  lcd.setCursor(7, 3);
  lcd.print(tempOilSetpoint, 1);
}

int get_key (unsigned int input)
{
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val [k])
    {
      return k;
    }
  }
  if (k >= NUM_KEYS) k = -1; // No valid key pressed
  return k;
}

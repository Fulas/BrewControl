void Menu() //Print: TempSetpoint
{
  float TempSetpoint;
  TempSetpoint = (Setpoint * 150) / 1023;
  lcd.setCursor(0, 1);
  lcd.print(TempSetpoint, 2);
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
        case 0: Serial.println ("S1 OK");
          break;
        case 1: TempSetpoint = TempSetpoint - 0.5;
          break;
        case 2: TempSetpoint = TempSetpoint + 0.5;
          break;
        case 3: Serial.println ("S4 OK");
          break;
        case 4: Serial.println ("S5 OK");
          break;
      }
    }
  }
  Setpoint = (TempSetpoint * 1023) / 150;
  lcd.setCursor(0, 1);
  lcd.print(TempSetpoint, 1);
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

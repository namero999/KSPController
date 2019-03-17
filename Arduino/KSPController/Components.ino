KCC_LCD* LCD;
KCC_Serial* SER;
KCC_SAS* SAS;

static void initializeComponents() {

  LCD = new KCC_LCD(PIN_LCD_MODE_1, PIN_LCD_MODE_2);
  SER = new KCC_Serial();

  SAS = new KCC_SAS(PIN_SAS_LED, PIN_SAS_TOGGLE, PIN_SAS_DATA, PIN_SAS_CLOCK, PIN_SAS_RESET);

  //KCC_Joysticks attitudeJoy    = KCC_Joysticks(PIN_JOY_ATTITUDE_X, PIN_JOY_ATTITUDE_Y, PIN_JOY_ATTITUDE_Z);
  //KCC_Joysticks translationJoy = KCC_Joysticks(PIN_JOY_TRANSLATION_X, PIN_JOY_TRANSLATION_X, PIN_JOY_TRANSLATION_X);

  //KCC_Fuel solidFuel    = KCC_Fuel(PIN_FUEL_SOLID);
  //KCC_Fuel liquidFuel   = KCC_Fuel(PIN_FUEL_LIQUID);
  //KCC_Fuel oxidizerFuel = KCC_Fuel(PIN_FUEL_OXIDIZER);
  //KCC_Fuel monopropFuel = KCC_Fuel(PIN_FUEL_MONOPROP);
  //KCC_Fuel electroFuel  = KCC_Fuel(PIN_FUEL_ELECTRO);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

}

/*
   data gathering functions

*/

void gather_data() {
  uint16_t samples[ANALOGSAMPLES];
  uint16_t raw_watertemp = 0;
  uint16_t raw_oiltemp = 0;
  uint16_t raw_oilpress = 0;
  uint16_t raw_lambda = 0;
  uint16_t raw_voltage = 0;
  uint8_t runs;

  // do multiple samples
  for ( runs = 0 ; runs < ANALOGSAMPLES ; runs++ ) {
    raw_watertemp += analogRead(INPUT_WATERTEMP);
    raw_oiltemp += analogRead(INPUT_OILTEMP);
    raw_oilpress += analogRead(INPUT_OILPRESS);
    raw_lambda += analogRead(INPUT_LAMBDA);
    raw_voltage += analogRead(INPUT_VOLTAGE);
    delay(5);
  }

  // and even them out
  raw_watertemp = raw_watertemp / ANALOGSAMPLES;
  raw_oiltemp = raw_oiltemp / ANALOGSAMPLES;
  raw_oilpress = raw_oilpress / ANALOGSAMPLES;
  raw_lambda = raw_lambda / ANALOGSAMPLES;
  raw_voltage = raw_voltage / ANALOGSAMPLES;

  //do sensor data conversions

  //Outside temperature
  //digital 1-wire temperature sensor reading
  //outsideSensor.requestTemperatures();
  //outsidetemp = outsideSensor.getTempCByIndex(0);
  // really 1-wire?

  //Lambda sensor reading
  if ( LAMBDA_DIGITAL ) {
    // Lambda digital
  } else {
    // Lambda analog
    // 5V Input, 0V == 0.70 (raw 0), 5V == 1.30 (raw 1024)
    // 0 == value 70, 1024 == value 130
    lambda = (raw_lambda * 60 / 1024) + 70;
  }

  //Voltage reading
  // voltage divider 1:4 connected to Vbat, limited to 4,7V => max 18,8V
  // 1024 == 5V, 512 == 2.5V resp 10V Vbat resp voltage value 100.
  voltage = raw_voltage * 50 / 256;

  //Oil pressure, 5 bar VDO sensor 10-184 Ohm at 100 Ohm pullup.
  // 93 => 0 bar, 665 => 5 bar
  // raw > 802 => sensor not connected
  if ( raw_oilpress > 802 ) {
    oilpress = NODATA;
  } else if ( raw_oilpress < 94 ) {
    oilpress = 0;
  } else {
    oilpress = (((22 * raw_oilpress - 2048) * 2) / (1024 - raw_oilpress)) * 7;
  }

  //Oil temperature, Racimex temp sensor at 470 Ohm pullup
  // 100 => temp too high, > 802 => temp too low
  if ( raw_oiltemp > 802 ) {
    oiltemp = NODATA;
  } else if ( raw_oiltemp < 100 ) {
    oiltemp = TEMPTOOHIGH;
  } else {
    oiltemp = beta(raw_oiltemp, RACIMEXTEMP_T0, RACIMEXTEMP_R0, RACIMEXTEMP_B, OILTEMP_PULLUP);
  }

  //Water temperature, Mini GTR101 temp sensor, connected to instrument as pullup to 10V
  // 300 => temp too high, > 950 => temp too low
  if ( raw_watertemp > 950 ) {
    watertemp = NODATA;
  } else if ( raw_watertemp < 300 ) {
    watertemp = TEMPTOOHIGH;
  } else {
    watertemp = beta(raw_watertemp, MINITEMP_T0, MINITEMP_R0, MINITEMP_B, WATERTEMP_PULLUP);
  }

}

// beta equation - simplified from Steinhart–Hart equation
// https://en.wikipedia.org/wiki/Thermistor
uint16_t beta (uint16_t reading, float T0, float R0, float B, float pullup) {

  float r; //resistance
  float v; //temperature value

  r = pullup / ((1024 / (float)reading) - 1 );

  v = ((log(r / R0)) / B) + ( 1 / T0);
  v = 1.0 / v;             // Invert v
  v = v - 273.15;          // convert to celsius

  if ( v >= 0 ) {
    return int(v);
  } else {
    return 0;
  }
}

void check_warnings () {
  byte switchDisplayTo = 255;
  bool setWarningOutput = false;

  if ( outsidetemp < WARN_MIN_OUTSIDETEMP ) {
    if ( !warningOutsidetemp ) { // new warning
      switchDisplayTo = OUTSIDE;
      warningOutsidetemp = true;
    }
  } else {
    warningOutsidetemp = false; // reset warning
  }

  if ( (voltage < WARN_MIN_VOLTAGE) ||
       (voltage > WARN_MAX_VOLTAGE) ) {
    setWarningOutput = true;
    if ( !warningVoltage ) { // new warning
      switchDisplayTo = VOLT;
      warningVoltage = true;
    }
  } else {
    warningVoltage = false; // reset warning
  }

  if ( oiltemp != NODATA ) {
    if ( oiltemp > WARN_MAX_OILTEMP ) {
      setWarningOutput = true;
      if ( !warningOiltemp ) { // new warning
        switchDisplayTo = OIL_TEMP;
        warningOiltemp = true;
      }
    }
    else {
      warningOiltemp = false; // reset warning
    }
  }

  if ( watertemp != NODATA ) {
    if ( watertemp > WARN_MAX_WATERTEMP ) {
      setWarningOutput = true;
      if ( !warningWatertemp ) { // new warning
        switchDisplayTo = WATER_TEMP;
        warningWatertemp = true;
      }
    } else {
      warningWatertemp = false; // reset warning
    }
  }

  if ( oilpress < WARN_MIN_OILPRESS ) {
    setWarningOutput = true;
    if ( !warningOilpress ) { // new warning
      switchDisplayTo = OIL_PRESS;
      warningOilpress = true;
    }
  } else {
    warningOilpress = false;
  }

  if ( switchDisplayTo != 255 ) { // we found a new warning condition
    displayMode = switchDisplayTo; // switch to sensor with warning
  }
  digitalWrite(OUTPUT_WARN, setWarningOutput); // set warning lamp

}

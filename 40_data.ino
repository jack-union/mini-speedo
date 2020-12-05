/*
   data gathering functions

*/

void gather_data() {
  uint16_t raw_watertemp = analogRead(INPUT_WATERTEMP);
  uint16_t raw_oiltemp = analogRead(INPUT_OILTEMP);
  uint16_t raw_oilpress = analogRead(INPUT_OILPRESS);
  uint16_t raw_lambda = analogRead(INPUT_LAMBDA);
  uint16_t raw_voltage = analogRead(INPUT_VOLTAGE);

  //Demo
  watertemp = 93;
  oiltemp = 108;
  oilpress = 450;


  //do sensor data conversions

  //digital 1-wire temperature sensor reading
  outsideSensor.requestTemperatures();
  outsidetemp = outsideSensor.getTempCByIndex(0);


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
    oilpress = 3000;
  } else if ( raw_oilpress < 94 ) {
    oilpress = 0;
  } else {
    oilpress = (((22 * raw_oilpress - 2048) * 2) / (1024 - raw_oilpress)) * 7;
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

  if ( oiltemp > WARN_MAX_OILTEMP ) {
    setWarningOutput = true;
    if ( !warningOiltemp ) { // new warning
      switchDisplayTo = OIL_TEMP;
      warningOiltemp = true;
    }
  } else {
    warningOiltemp = false; // reset warning
  }

  if ( watertemp > WARN_MAX_WATERTEMP ) {
    setWarningOutput = true;
    if ( !warningWatertemp ) { // new warning
      switchDisplayTo = WATER_TEMP;
      warningWatertemp = true;
    }
  } else {
    warningWatertemp = false; // reset warning
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

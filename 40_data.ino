/*
   data gathering functions

*/

void gather_data() {
  uint16_t raw_watertemp = analogRead(INPUT_WATERTEMP);
  uint16_t raw_oiltemp = analogRead(INPUT_OILTEMP);
  uint16_t raw_oilpress = analogRead(INPUT_OILPRESS);
  uint16_t raw_lambda = analogRead(INPUT_LAMBDA);
  uint16_t raw_outsidetemp = analogRead(INPUT_OUTSIDETEMP);
  uint16_t raw_voltage = analogRead(INPUT_VOLTAGE);

  //Demo
  watertemp = 93;
  oiltemp = 122;
  oilpress = 450;
  //lambda = 97;
  raw_lambda = 375; // 0.92
  outsidetemp = 23;
  //voltage = 144;
  raw_voltage = 707; // 13.8V


  //do sensor data conversions

  if ( LAMBDA_DIGITAL ) {
    // Lambda digital
  } else {
    // Lambda analog
    // 5V Input, 0V == 0.70 (raw 0), 5V == 1.30 (raw 1024)
    // 0 == value 70, 1024 == value 130
    lambda = (raw_lambda * 60 / 1024) + 70;
  }

  // Voltage
  //voltage divider 1:4 connected to Vbat, limited to 4,7V => max 18,8V
  // 1024 == 5V, 512 == 2.5V resp 10V Vbat resp voltage value 100.
  voltage = raw_voltage * 50 / 256;

}

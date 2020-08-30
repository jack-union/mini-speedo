/*
 * data gathering functions
 * 
 */
 
void gather_data() {
  int raw_watertemp = analogRead(INPUT_WATERTEMP);
  int raw_oiltemp = analogRead(INPUT_OILTEMP);
  int raw_oilpress = analogRead(INPUT_OILPRESS);
  int raw_lambda = analogRead(INPUT_LAMBDA);
  int raw_outsidetemp = analogRead(INPUT_OUTSIDETEMP);
  int raw_voltage = analogRead(INPUT_VOLTAGE);

  //Demo
  watertemp = 93;
  oiltemp = 122;
  oilpress = 450;
  lambda = 97;
  outsidetemp = 23;
  voltage = 144;

  //do sensor data conversions

}

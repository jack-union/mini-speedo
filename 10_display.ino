/*
 * display functions
 * 
 */
 
void do_display() {
  if (displayMode != MINI) {
    if (displayChanged) {
      scroll_mode(displayNames[displayMode]);
      displayChanged = false;
    }
    draw_mode(displayNames[displayMode]);
  }

  switch (displayMode) {
    case ODO:
      draw_odo(total / 1000); //decimeters to 100m
      break;
    case TRIP:
      draw_trip(trip / 1000); //decimeters to 100m
      break;
    case SPEED:
      draw_speed(speed);
      break;
    case LAMBDA:
      draw_lambda(lambda);
      break;
    case OIL_TEMP:
      draw_oil_temp(oiltemp);
      break;
    case OIL_PRESS:
      draw_oil_press(oilpress);
      break;
    case VOLT:
      draw_voltage(voltage);
      break;
    case WATER_TEMP:
      draw_water_temp(watertemp);
      break;
    case OUTSIDE:
      draw_outside_temp(outsidetemp);
      break;
    case RPM:
      draw_rpm(rpm);
      break;
    case MINI:
      draw_logo();
      break;
  }
  display.display();
}

void increment_display () {
  if (displayMode < MODEMAX) {
    displayMode++;
  } else {
    displayMode = 0;
  }
}

void scroll_mode(String param) {
  int len;
  String prt;

  display.setTextColor(WHITE);
  display.setTextSize(2);

  for (int row = 55; row > X_OFFSET; row = row - 4 ) {
    display.clearDisplay();
    display.setCursor(row, 4);
    len = ((128 - row) / 10) - 2;
    prt = param;
    prt.remove(len);
    display.println(prt);
    display.display();
    delay(5);
  }
}

void draw_mode(String param) {
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.clearDisplay();
  display.setCursor(X_OFFSET, 4);
  display.println(param);
}

void draw_odo(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%07d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(7, 38);

  display.print(data[1]);
  display.print(data[2]);
  display.print(data[3]);
  display.print(data[4]);
  display.print(data[5]);

  display.drawLine(99, 36, 99, 62, WHITE);

  display.setCursor(105, 38);
  display.println(data[6]);
}

void draw_trip(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%7d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(7, 38);

  display.print(data[1]);
  display.print(data[2]);
  display.print(data[3]);
  display.print(data[4]);
  display.print(data[5]);

  display.drawLine(99, 36, 99, 62, WHITE);

  display.setCursor(105, 38);
  display.println(data[6]);
}

void draw_speed(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(4, 38);
  display.println(data);

  display.setTextSize(2);
  display.setCursor(75, 45);
  display.println("km/h");
}

void draw_lambda(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%03d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(2, 38);
  display.print(data[0]);
  display.print(".");
  display.print(data[1]);
  display.print(data[2]);

  display.setTextSize(2);
  display.setCursor(80, 45);
  if (readout < 100 ) {
    display.println("rich");
  } else {
    display.println("lean");
  }
}

void draw_oil_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(15, 38);
  display.println(data);

  display.setTextSize(1);
  display.setCursor(90, 45);
  display.println("O");

  display.setTextSize(2);
  display.setCursor(100, 45);
  display.println("C");
}

void draw_oil_press(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%03d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(12, 38);
  display.print(data[0]);
  display.print(".");
  display.print(data[1]);
  display.print(data[2]);

  display.setTextSize(2);
  display.setCursor(90, 45);
  display.println("bar");
}

void draw_voltage(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(2, 38);
  display.print(data[0]);
  display.print(data[1]);
  display.print(".");
  display.print(data[2]);

  display.setTextSize(2);
  display.setCursor(80, 45);
  display.println("volt");
}

void draw_water_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(15, 38);
  display.println(data);

  display.setTextSize(1);
  display.setCursor(90, 45);
  display.println("O");

  display.setTextSize(2);
  display.setCursor(100, 45);
  display.println("C");
}

void draw_outside_temp(int16_t readout) {
  char data[4] = "";
  sprintf(data, "% 3d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(15, 38);
  display.println(data);

  display.setTextSize(1);
  display.setCursor(80, 45);
  display.println("O");

  display.setTextSize(2);
  display.setCursor(90, 45);
  display.println("C");
}

void draw_rpm(uint16_t readout) {
  char data[5] = "";
  sprintf(data, "%4d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(15, 38);
  display.println(data);

  display.setTextSize(2);
  display.setCursor(90, 45);
  display.println("rpm");
}

void draw_logo() {
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
}

void draw_goodbye() {
  draw_logo();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(5, 5);
  display.println(F("Bye..."));

  display.display();
}

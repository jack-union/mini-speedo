/*
   display functions

*/
#define SMALL_FONT u8g2_font_logisoso18_tf
#define LARGE_FONT u8g2_font_logisoso24_tf

void do_display() {
  if (displayMode != MINI) {
    if (displayChanged) {
      scroll_mode(displayNames[displayMode]);
      displayChanged = false;
    }
  }

  check_warnings();

  display.firstPage();
  do {
    draw_mode(displayNames[displayMode]);
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
  } while ( display.nextPage() );
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

  display.setFont(SMALL_FONT);

  for (int row = 55; row > X_OFFSET; row = row - 6 ) {
    display.firstPage();
    do {
      display.setCursor(row, 20);
      len = ((128 - row) / 10) - 2;
      prt = param;
      prt.remove(len);
      display.print(prt);
    } while ( display.nextPage() );
    delay(1);
  }
}

void draw_mode(String param) {
  display.setFont(SMALL_FONT);
  display.setCursor(X_OFFSET, 20);
  display.print(param);
}

void draw_odo(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%07d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(3, 60);
  display.print(data[1]);
  display.setCursor(23, 60);
  display.print(data[2]);
  display.setCursor(43, 60);
  display.print(data[3]);
  display.setCursor(63, 60);
  display.print(data[4]);
  display.setCursor(83, 60);
  display.print(data[5]);

  display.drawLine(101, 34, 101, 63);

  display.setCursor(106, 60);
  display.println(data[6]);
}

void draw_trip(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%7d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(3, 60);
  display.print(data[1]);
  display.setCursor(23, 60);
  display.print(data[2]);
  display.setCursor(43, 60);
  display.print(data[3]);
  display.setCursor(63, 60);
  display.print(data[4]);
  display.setCursor(83, 60);
  display.print(data[5]);

  display.drawLine(101, 34, 101, 63);

  display.setCursor(106, 60);
  display.println(data[6]);
}

void draw_speed(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(20, 60);
  display.println(data);

  display.setFont(SMALL_FONT);
  display.setCursor(75, 60);
  display.println("km/h");
}

void draw_lambda(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%03d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(10, 60);
  display.print(data[0]);
  display.print(".");
  display.print(data[1]);
  display.print(data[2]);

  display.setFont(SMALL_FONT);
  display.setCursor(80, 60);
  if (readout < 100 ) {
    display.println("rich");
  } else {
    display.println("lean");
  }
}

void draw_oil_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(15, 60);

  if ( readout == NODATA ) {
    display.println(F("---"));
  } else if ( readout == TEMPTOOHIGH ) {
    display.println(F("HIGH"));
  } else {
    display.println(data);
  }

  display.setFont(SMALL_FONT);
  display.setCursor(85, 60);
  display.println(char(0xb0)); //ASCII "degrees" symbol
  display.println("C");

  if ( warningOiltemp ) {
    draw_warning();
  }
}

void draw_oil_press(uint16_t readout) {
  char data[4] = "";
  display.setFont(LARGE_FONT);
  display.setCursor(15, 60);

  if ( readout == NODATA ) {
    display.print("-.--");
  } else {
    sprintf(data, "%03d", readout);

    display.print(data[0]);
    display.print(".");
    display.print(data[1]);
    display.print(data[2]);
  }

  display.setFont(SMALL_FONT);
  display.setCursor(85, 60);
  display.println("bar");

  if ( warningOilpress ) {
    draw_warning();
  }
}

void draw_voltage(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(10, 60);
  display.print(data[0]);
  display.print(data[1]);
  display.print(".");
  display.print(data[2]);

  display.setFont(SMALL_FONT);
  display.setCursor(80, 60);
  display.println("volt");

  if ( warningVoltage ) {
    draw_warning();
  }
}

void draw_water_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(15, 60);

  if ( readout == NODATA ) {
    display.println(F("---"));
  } else if ( readout == TEMPTOOHIGH ) {
    display.println(F("HIGH"));
  } else {
    display.println(data);
  }

  display.setFont(SMALL_FONT);
  display.setCursor(85, 60);
  display.println(char(0xb0)); //ASCII "degrees" symbol
  display.println("C");

  if ( warningWatertemp ) {
    draw_warning();
  }
}

void draw_outside_temp(int16_t readout) {
  char data[4] = "";
  sprintf(data, "% 3d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(15, 60);
  display.println(data);

  display.setFont(SMALL_FONT);
  display.setCursor(85, 60);
  display.println(char(0xb0)); //ASCII "degrees" symbol
  display.println("C");
  if ( warningOutsidetemp ) {
    draw_warning();
  }
}

void draw_rpm(uint16_t readout) {
  char data[5] = "";
  sprintf(data, "%4d", readout);

  display.setFont(LARGE_FONT);
  display.setCursor(10, 60);
  display.print(data);
  display.setFont(SMALL_FONT);
  display.setCursor(85, 60);
  display.println("rpm");
}

void draw_logo() {
  display.drawXBMP(
    (SCREEN_WIDTH - LOGO_WIDTH ) / 2,
    (SCREEN_HEIGHT - LOGO_HEIGHT) / 2,
    LOGO_WIDTH, LOGO_HEIGHT,
    logo_bmp);
}

void draw_warning() {
  display.drawXBMP(
    WARNING_X_POS,
    WARNING_Y_POS,
    WARNING_WIDTH, WARNING_HEIGHT,
    warning_bmp);
}

void draw_goodbye() {
  display.setFont(SMALL_FONT);
  display.setCursor(48, 36);
  display.println(F("Bye."));
}

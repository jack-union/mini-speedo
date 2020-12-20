/*
   display functions

*/
#define SMALL_FONT u8g2_font_logisoso18_tf
#define LARGE_FONT u8g2_font_logisoso24_tn

void initDisplays() {
  //bigDisplay.setI2CAddress(0x78); //0x3c * 2, default
  bigDisplay.setI2CAddress(0x7a); //0x3d * 2
  bigDisplay.begin();
  bigDisplay.setDrawColor(1);
  bigDisplay.setFontMode(0);
  smallDisplay.setI2CAddress(0x78); //0x3c * 2, default
  //smallDisplay.setI2CAddress(0x7a); //0x3d * 2
  smallDisplay.begin();
  smallDisplay.setDrawColor(1);
  smallDisplay.setFontMode(0);

  bigDisplay.firstPage();
  do {
    draw_logo();
  } while ( bigDisplay.nextPage() );

  smallDisplay.firstPage();
  do {
    smallDisplay.setFont(SMALL_FONT);
    smallDisplay.setCursor(0, 60);
    smallDisplay.println(F(MINI_SPEEDO_VERSION));
  } while ( smallDisplay.nextPage() );
}

void do_display() {
  if (displayMode != MINI) {
    if (displayChanged) {
      scroll_mode(displayNames[displayMode]);
      displayChanged = false;
    }
  }

  bigDisplay.firstPage();
  do {
    draw_mode(displayNames[displayMode]);
    switch (displayMode) {
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
  } while ( bigDisplay.nextPage() );

  smallDisplay.firstPage();
  do {
    draw_odo(total / 1000); //decimeters to 100m
  } while ( smallDisplay.nextPage() );
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

  bigDisplay.setFont(SMALL_FONT);

  for (int row = 55; row > X_OFFSET; row = row - 6 ) {
    bigDisplay.firstPage();
    do {
      bigDisplay.setCursor(row, 20);
      len = ((128 - row) / 10) - 2;
      prt = param;
      prt.remove(len);
      bigDisplay.print(prt);
    } while ( bigDisplay.nextPage() );
    delay(1);
  }
}

void draw_mode(String param) {
  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(X_OFFSET, 20);
  bigDisplay.print(param);
}

void draw_odo(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%07d", readout);

  smallDisplay.setFont(LARGE_FONT);
  smallDisplay.setCursor(3, 60);
  smallDisplay.print(data[1]);
  smallDisplay.setCursor(23, 60);
  smallDisplay.print(data[2]);
  smallDisplay.setCursor(43, 60);
  smallDisplay.print(data[3]);
  smallDisplay.setCursor(63, 60);
  smallDisplay.print(data[4]);
  smallDisplay.setCursor(83, 60);
  smallDisplay.print(data[5]);

  smallDisplay.drawLine(101, 34, 101, 63);

  smallDisplay.setCursor(106, 60);
  smallDisplay.println(data[6]);
}

void draw_trip(uint32_t readout) {
  char data[8] = "";
  sprintf(data, "%7d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(3, 60);
  bigDisplay.print(data[1]);
  bigDisplay.setCursor(23, 60);
  bigDisplay.print(data[2]);
  bigDisplay.setCursor(43, 60);
  bigDisplay.print(data[3]);
  bigDisplay.setCursor(63, 60);
  bigDisplay.print(data[4]);
  bigDisplay.setCursor(83, 60);
  bigDisplay.print(data[5]);

  bigDisplay.drawLine(101, 34, 101, 63);

  bigDisplay.setCursor(106, 60);
  bigDisplay.println(data[6]);
}

void draw_speed(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(20, 60);
  bigDisplay.println(data);

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(75, 60);
  bigDisplay.println(F("km/h"));
}

void draw_lambda(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%03d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(10, 60);
  bigDisplay.print(data[0]);
  bigDisplay.print(".");
  bigDisplay.print(data[1]);
  bigDisplay.print(data[2]);

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(80, 60);
  if (readout < 100 ) {
    bigDisplay.println(F("rich"));
  } else {
    bigDisplay.println(F("lean"));
  }
}

void draw_oil_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(15, 60);

  if ( readout == NODATA ) {
    bigDisplay.println(F("---"));
  } else if ( readout == TEMPTOOHIGH ) {
    bigDisplay.println(F("+++"));
  } else {
    bigDisplay.println(data);
  }

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(85, 60);
  bigDisplay.println(char(0xb0)); //ASCII "degrees" symbol
  bigDisplay.println(F("C"));

  if ( warningOiltemp ) {
    draw_warning();
  }
}

void draw_oil_press(uint16_t readout) {
  char data[4] = "";
  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(15, 60);

  if ( readout == NODATA ) {
    bigDisplay.print("-.--");
  } else {
    sprintf(data, "%03d", readout);

    bigDisplay.print(data[0]);
    bigDisplay.print(".");
    bigDisplay.print(data[1]);
    bigDisplay.print(data[2]);
  }

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(85, 60);
  bigDisplay.println(F("bar"));

  if ( warningOilpress ) {
    draw_warning();
  }
}

void draw_voltage(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(10, 60);
  bigDisplay.print(data[0]);
  bigDisplay.print(data[1]);
  bigDisplay.print(".");
  bigDisplay.print(data[2]);

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(80, 60);
  bigDisplay.println(F("volt"));

  if ( warningVoltage ) {
    draw_warning();
  }
}

void draw_water_temp(uint16_t readout) {
  char data[4] = "";
  sprintf(data, "%3d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(15, 60);

  if ( readout == NODATA ) {
    bigDisplay.println(F("---"));
  } else if ( readout == TEMPTOOHIGH ) {
    bigDisplay.println(F("+++"));
  } else {
    bigDisplay.println(data);
  }

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(85, 60);
  bigDisplay.println(char(0xb0)); //ASCII "degrees" symbol
  bigDisplay.println(F("C"));

  if ( warningWatertemp ) {
    draw_warning();
  }
}

void draw_outside_temp(int16_t readout) {
  char data[5] = "";
  sprintf(data, "% 4d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(10, 60);
  bigDisplay.print(data[0]);
  bigDisplay.print(data[1]);
  bigDisplay.print(data[2]);
  bigDisplay.print(".");
  bigDisplay.print(data[3]);

  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(85, 60);
  bigDisplay.println(char(0xb0)); //ASCII "degrees" symbol
  bigDisplay.println(F("C"));
  if ( warningOutsidetemp ) {
    draw_warning();
  }
}

void draw_rpm(uint16_t readout) {
  char data[5] = "";
  sprintf(data, "%4d", readout);

  bigDisplay.setFont(LARGE_FONT);
  bigDisplay.setCursor(10, 60);
  bigDisplay.print(data);
  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(85, 60);
  bigDisplay.println(F("rpm"));
}

void draw_logo() {
  bigDisplay.drawXBMP(
    (SCREEN_WIDTH - LOGO_WIDTH ) / 2,
    (SCREEN_HEIGHT - LOGO_HEIGHT) / 2,
    LOGO_WIDTH, LOGO_HEIGHT,
    logo_bmp);
}

void draw_warning() {
  bigDisplay.drawXBMP(
    WARNING_X_POS,
    WARNING_Y_POS,
    WARNING_WIDTH, WARNING_HEIGHT,
    warning_bmp);
}

void draw_goodbye() {
  bigDisplay.setFont(SMALL_FONT);
  bigDisplay.setCursor(48, 36);
  bigDisplay.println(F("Bye."));
}

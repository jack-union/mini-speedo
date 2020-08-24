/*
  Speedo with multifunction display
*/

//----Libraries to Include--------
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SwitecX25.h"
#include <EEPROM.h>
//----End Libraries--------------

//----Define OLED Display Settings----
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//-----End OLED Display Settings------

//----Define Stepper motor library variables and pin outs-------------------------------------------
const double StepsPerDegree = 3.0;  // Motor step is 1/3 of a degree of rotation
const unsigned int MaxMotorRotation = 315; // 315 max degrees of movement
const unsigned int MaxMotorSteps = MaxMotorRotation * StepsPerDegree;
//SwitecX25 stepper(MaxMotorSteps, 4, 5, 6, 7); // Create the motor object with the maximum steps allowed
//----Define Stepper motor library variables and pin outs-------------------------------------------

//----Define Display positions----
#define X_OFFSET 18
//----End Define Display positions----

//----Define PIN Settings----------
const byte INPUT_BUTTON = 8; //brake light test button
const byte INPUT_SPEED = 2; //Interruptable PIN on Nano
const byte INPUT_TACHO = 3; //Interruptable PIN on Nano
//----End Define PIN Settings------

//----Define other constants-------
const byte speed_imp_per_rev = 6;
const byte ign_imp_per_rev = 2;
//----End Define other constants---

//----Display modes----
#define ODO 0
#define TRIP 1
#define SPEED 2
#define LAMBDA 3
#define OIL_TEMP 4
#define OIL_PRESS 5
#define VOLT 6
#define WATER_TEMP 7
#define OUTSIDE 8
#define RPM 9
#define MINI 10

#define MODEMAX 10
//----End Display modes----

//----Display mode names----
const char *displayNames[] = {
  "total",
  "trip",
  "speed",
  "lambda",
  "oil temp",
  "oil press",
  "volt",
  "water",
  "outside",
  "rpm",
  "mini"
};
//----End Display mode names----


//----Define Logo-------
#define LOGO_HEIGHT   48
#define LOGO_WIDTH    80
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,

  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000111, B11111111, B11111111, B11111111, B11000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00001111, B11111111, B11111111, B11111111, B11110000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00011100, B00000000, B00000000, B00000000, B00111000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00111000, B00000000, B00000000, B00000000, B00011100, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00110000, B00000000, B00000000, B00000000, B00001110, B00000000, B00000000,

  B00000000, B00000000, B00000000, B01110000, B00000000, B00000000, B00000000, B00000111, B00000000, B00000000,
  B00000000, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000011, B00000000, B00000000,
  B00000000, B00000000, B00000000, B11000000, B00000000, B00000000, B00000000, B00000011, B10000000, B00000000,
  B00000000, B00000000, B00000001, B10000000, B00000000, B00000000, B00000000, B00000001, B11000000, B00000000,
  B00000000, B00000000, B00000111, B10000000, B00000000, B00000000, B00000000, B00000000, B11000000, B00000000,
  B00000000, B01111111, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B01100000, B00000000,
  B00000001, B11111111, B11111000, B00000000, B00000000, B00000000, B00000000, B00000000, B01110000, B00000000,
  B00000011, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111000, B00000000,

  B00000111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011100, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001100, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000110, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000110, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B00000000,
  B00000011, B00001111, B00000000, B00000000, B00000000, B00000000, B00000000, B00111110, B00000011, B00000000,
  B00000011, B00111001, B11000000, B00000000, B00000000, B00000000, B00000000, B01110111, B00000011, B00000000,
  B00000011, B01100000, B01100000, B00000000, B00000000, B00000000, B00000000, B11000001, B10000011, B00000000,

  B00000011, B01000000, B00100000, B00000000, B00000000, B00000000, B00000001, B10000000, B11000110, B00000000,
  B00000011, B11000000, B00110000, B00000000, B00000000, B00000000, B00000001, B00000000, B01000110, B00000000,
  B00000011, B10000000, B00010000, B00000000, B00000000, B00000000, B00000011, B00000000, B01101110, B00000000,
  B00000001, B10000000, B00011111, B11111111, B11111111, B11111111, B11111111, B00000000, B01111000, B00000000,
  B00000001, B11000000, B00111111, B11111111, B11111111, B11111111, B11111111, B00000000, B01110000, B00000000,
  B00000000, B11000000, B00100000, B00000000, B00000000, B00000000, B00000001, B10000000, B11000000, B00000000,
  B00000000, B01100000, B01100000, B00000000, B00000000, B00000000, B00000000, B11000000, B10000000, B00000000,
  B00000000, B00110000, B11000000, B00000000, B00000000, B00000000, B00000000, B01100011, B10000000, B00000000,

  B00000000, B00011111, B10000000, B00000000, B00000000, B00000000, B00000000, B00111110, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
//----End Define Logo-------

//-----Variables----------------------
const int updateInterval = 100;  // 100 milliseconds speedo update rate

uint32_t total = 0;
uint32_t trip = 0;
uint16_t speed = 0;
uint16_t lambda = 0;
uint16_t oiltemp = 0;
uint16_t oilpress = 0;
uint16_t voltage = 0;
uint16_t watertemp = 0;
uint16_t outsidetemp = 0;
uint16_t rpm = 0;

byte displayMode = ODO; // Startup setting
bool buttonState = HIGH;
bool buttonBeforeState = HIGH;
unsigned long timePressed = 0;
unsigned long displayUpdatedAt = 0;
bool displayChanged = false;

//----End Variables-------------------

//-----Start-up code run once---------
void setup(void)
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  pinMode(INPUT_SPEED, INPUT_PULLUP);
  pinMode(INPUT_TACHO, INPUT_PULLUP);
  pinMode(INPUT_BUTTON, INPUT_PULLUP);

  draw_logo();
  display.display();
  delay(1500);
  //  reset_stepper();

  total = 22357;
  trip = 1457;
  speed = 124;
  lambda = 93;
  oiltemp = 87;
  oilpress = 450;
  voltage = 144;
  watertemp = 88;
  outsidetemp = 23;
  rpm = 3120;

  Serial.println(F("Setup done."));
}
//------End Start-up code-------------

//------Start of Loop-----------------
void loop() {

  do_button();
  gather_data();
  do_display();

}
//-------End of Loop------------------


//-------Start of Functions-----------

/*
  void reset_stepper() {
  stepper.zero(); //Initialize stepper at 0 location
  stepper.setPosition(744);
  stepper.updateBlocking();
  delay (500);
  stepper.setPosition(0);  //0MPH
  stepper.updateBlocking();
  delay (500);
  }
*/

void do_button() {
  buttonState = digitalRead(INPUT_BUTTON);
  if (buttonState == LOW) {
    if (buttonBeforeState == HIGH) { //press started
      timePressed = millis();
      buttonBeforeState = LOW;
    } else { //still holding LOW
      if (millis() - timePressed > 1000) { //one second hold
        if (displayMode == TRIP) {
          trip = 0; //reset trip
        }
      }
    }
  } else { //buttonState HIGH
    if (buttonBeforeState == LOW) { //just released
      if ((millis() - timePressed > 50) and (millis() - timePressed < 1000))  { //short press ended
        incrementDisplay();
        displayChanged = true;
      }
      buttonBeforeState = HIGH;
    }
  }
}

void gather_data() {

}

void do_display() {
  //display refresh every (updateInterval) milliseconds
  if ( (millis() - displayUpdatedAt) > updateInterval ) {

    if (displayMode != MINI) {
      if (displayChanged) {
        scroll_mode(displayNames[displayMode]);
        displayChanged = false;
      } else {
        draw_mode(displayNames[displayMode]);
      }
    }

    switch (displayMode) {
      case ODO:
        draw_odo(total);
        break;
      case TRIP:
        draw_trip(trip);
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

    displayUpdatedAt = millis();
  }
}

void incrementDisplay () {
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
  sprintf(data, "%07d", readout);

  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(7, 38);

  if (readout < 100000) {
    display.print(" ");
  } else {
    display.print(data[1]);
  }
  if (readout < 10000) {
    display.print(" ");
  } else {
    display.print(data[2]);
  }
  if (readout < 1000) {
    display.print(" ");
  } else {
    display.print(data[3]);
  }
  if (readout < 100) {
    display.print(" ");
  } else {
    display.print(data[4]);
  }
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

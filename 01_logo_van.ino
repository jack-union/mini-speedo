/*
 * Logo definition
 * 
 */

/*
//----Define Logo-------
#define LOGO_HEIGHT   48
#define LOGO_WIDTH    88
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,

  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11111111, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00001111, B11111111, B11111111, B11111111, B11111111, B11111111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00011100, B00000000, B00000000, B00000000, B00000000, B00000001, B11000000, B00000000,
  B00000000, B00000000, B00000000, B00111000, B00000000, B00000000, B00000000, B00000000, B00000000, B11000000, B00000000,
  B00000000, B00000000, B00000000, B00110000, B00000000, B00000000, B00000000, B00000000, B00000000, B11000000, B00000000,

  B00000000, B00000000, B00000000, B01110000, B00000000, B00000000, B00000000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00000000, B00000000, B01100000, B00000000, B00000000, B00000000, B00000000, B00000000, B01100000, B00000000,
  B00000000, B00000000, B00000000, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01110000, B00000000,
  B00000000, B00000000, B00000001, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00110000, B00000000,
  B00000000, B00000000, B00000111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111000, B00000000,
  B00000000, B01111111, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011000, B00000000,
  B00000001, B11111111, B11111000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011100, B00000000,
  B00000011, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001100, B00000000,

  B00000111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001110, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000110, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B00000000,
  B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B10000000,
  B00000011, B00001111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111110, B00000001, B10000000,
  B00000011, B00111001, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01110111, B00000001, B10000000,
  B00000011, B01100000, B01100000, B00000000, B00000000, B00000000, B00000000, B00000001, B11000001, B10000001, B10000000,

  B00000011, B01000000, B00100000, B00000000, B00000000, B00000000, B00000000, B00000001, B10000000, B11000001, B10000000,
  B00000011, B11000000, B00110000, B00000000, B00000000, B00000000, B00000000, B00000001, B00000000, B01000001, B10000000,
  B00000011, B10000000, B00010000, B00000000, B00000000, B00000000, B00000000, B00000001, B00000000, B01100001, B10000000,
  B00000001, B10000000, B00011111, B11111111, B11111111, B11111111, B11111111, B11111111, B00000000, B00111111, B00000000,
  B00000001, B11000000, B00111111, B11111111, B11111111, B11111111, B11111111, B11111111, B10000000, B00111110, B00000000,
  B00000000, B11000000, B00100000, B00000000, B00000000, B00000000, B00000000, B00000000, B10000000, B01100000, B00000000,
  B00000000, B01100000, B01100000, B00000000, B00000000, B00000000, B00000000, B00000000, B11000000, B11000000, B00000000,
  B00000000, B00110000, B11000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01100001, B10000000, B00000000,

  B00000000, B00011111, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111111, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
//----End Define Logo-------
*/

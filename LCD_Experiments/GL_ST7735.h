// Graphics library by ladyada/adafruit 
// MIT license

#define swap(a, b) { uint16_t t = a; a = b; b = t; }


#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#define ST7735_NOP 0x0
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN  0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON  0x12
#define ST7735_NORON  0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36


#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_RDID1 0xDA
#define ST7735_RDID2 0xDB
#define ST7735_RDID3 0xDC
#define ST7735_RDID4 0xDD

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

//
// Set DEBUG to 1 to debug drawing of conic sections.
//
#define DEBUG 0
//
// if DEBUG is set to a non-zero value, then the SPEED must
// be set to a bit rate appropriate for the Serial port.
//
#define SPEED 115200



class GL_ST7735 {
 public:
  GL_ST7735(uint8_t CS, uint8_t RS, uint8_t SID, 
	 uint8_t SCLK, uint8_t RST);
  GL_ST7735(uint8_t CS, uint8_t RS, uint8_t RST);
  void initB(void);
  void initR(void);

  // drawing primitives!
  void pushColor(uint16_t color);
  void drawPixel(uint8_t x, uint8_t y, uint16_t color);
  void drawLine(int16_t x, int16_t y, int16_t x1, int16_t y1, uint16_t color);
  void fillScreen(uint16_t color);
  void drawVerticalLine(uint8_t x0, uint8_t y0, 
			uint8_t length, uint16_t color);
  void drawHorizontalLine(uint8_t x0, uint8_t y0, 
			  uint8_t length, uint16_t color);
  void drawFastLine(uint8_t x0, uint8_t y0, uint8_t l, 
		    uint16_t color, uint8_t flag);
  void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint16_t color);
  void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
		uint16_t color);
  void drawCircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint16_t color);
  void fillCircle(uint8_t x0, uint8_t y0, uint8_t r, 
		  uint16_t color);

  void drawString(uint8_t x, uint8_t y, char *c, 
		  uint16_t color, uint8_t size=1);
  void drawChar(uint8_t x, uint8_t y, char c, 
		      uint16_t color, uint8_t size=1);

  static const uint8_t width = 128;
  static const uint8_t height = 160;

  void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void setRotation(uint8_t);
  uint8_t getRotation(void);

  void dummyclock(void);
  void writecommand(uint8_t);
  void writedata(uint8_t);
  //
  // For ellipses and other conic sections.
  //
  // (xs, ys) is the starting point - must be exactly ON the conic section.
  // (xe, ye) is the   ending point - must be exactly ON the conic section.
  //
  // NOTE: drawConic changes A, B, C, D, E, and F !!!
  //
  void drawConic(int xs, int ys, int xe, int ye, int color) ;
  void assign(int A_, int B_, int C_, int D_, int E_, int F_) ;
  void assignf(double scale,
                             double A_,
                             double B_,
                             double C_,
                             double D_,
                             double E_,
                             double F_) ;

  /*
  // these are not for use, 8-bit protocol only!
  uint8_t readdata(void);
  uint8_t readcommand8(uint8_t);
  uint16_t readcommand16(uint8_t);
  uint32_t readcommand32(uint8_t);
  */

 private:
  void spiwrite(uint8_t);
  //uint8_t spiread(void);

  uint8_t _cs, _rs, _rst, _sid, _sclk;
  uint8_t csport, rsport, sidport, sclkport;
  uint8_t cspin, rspin, sidpin, sclkpin;

  uint8_t madctl;
  //
  // Parameters for ellipses and other conic sections.
  //
  // A xx + B xy + C yy + D x + E y + F = 0

  int A;
  int B;
  int C;
  int D;
  int E;
  int F;

//  const static int DIAGx[] ;
//  const static int DIAGy[] ;
//  const static int SIDEx[] ;
//  const static int SIDEy[] ;

  //
  // Private methods for ellipses and other conic sections.
  inline int rnd(double x) ;
  inline int odd(int n) ;
  int getOctant(int gx, int gy) ;

};

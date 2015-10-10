// Do not remove the include below
#include "LCD_Experiments.h"

/*

SainSmart ST7735 LCD/microSD module
www.sainsmart.com


Signal Definition TFT LCD):
•	GND 	        : Power Ground
•	VCC 	        : 5V power input (3.3V might work)
•	CS  	        : Chipselect for LCD, (use pin 10)
•	SDA 	        : LCD Data for SPI (use MOSI, pin 11)
•	SCL 	        : SCLK for TFT Clock (use SCLK, pin 13)
•	RS/DC 	        : Command/Data Selection (use pin 9)
•	RESET 	        : LCD controller reset, active low (use pin 8)
Signal Definition micro-SD):
•	CS (SD-CS) 	    : Chipselect for TF Card,
•	CLK (SD-Clock)	: SPI Clock
•	MOSI (SD-DI) 	: SPI Master out Slave in
•	MISO (SD-DO) 	: SPI Master in Slave out

Methods that may be called:

Create an instance:
  ST7735(uint8_t CS, uint8_t RS, uint8_t SID,
	 uint8_t SCLK, uint8_t RST);
  ST7735(uint8_t CS, uint8_t RS, uint8_t RST);

  Description

  The base class for drawing to the ST7735. Use this to create a named
  instance of the ST7735 class to refer to in your sketch.

  Syntax

  ST7735(cs, dc, rst); for using hardware SPI
  ST7735(cs, dc, mosi, sclk, rst); for use on any pins

  Parameters

  cs   : int, pin for chip select
  dc   : int, pin used for data/command
  rst  : int, pin used for reset
  mosi : int, pin used for MOSI communication when not using hardware SPI
  sclk : int, pin used for the shared clock, when not using hardware SPI

  Returns

  none


  The screen can be configured for use in two ways. One is to use an Arduino's
  hardware SPI interface. The other is to declare all the pins manually. There
  is no difference in the functionality of the screen between the two methods,
  but using hardware SPI is significantly faster.

  If you plan on using the SD card on the TFT module, you must use hardware SPI.
  All examples in the library are written for hardware SPI use.

  If using hardware SPI with the Uno, you only need to declare the
  CS, DC, and RESET pins,
  as MOSI (pin 11) and SCLK (pin 13) are already defined.

  #define CS   10
  #define DC    9
  #define RESET 8

  ST7735 myScreen = ST7735(CS, DC, RESET);


Initialize an ST7735B:
  void initB(void);

Initialize an ST7735R:
  void initR(void);

 Drawing primitives:
  void pushColor(uint16_t color);
  void drawPixel(uint8_t x, uint8_t y, uint16_t color);
  void drawLine(int16_t x, int16_t y, int16_t x1, int16_t y1, uint16_t color);
  void fillScreen(uint16_t color);
  void drawVerticalLine(uint8_t x0, uint8_t y0,
			uint8_t length, uint16_t color);
  void drawHorizontalLine(uint8_t x0, uint8_t y0,
			  uint8_t length, uint16_t color);
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

Low level:
  void setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
  void writecommand(uint8_t);
  void writedata(uint8_t);
  void setRotation(uint8_t);
  uint8_t getRotation(void);
  void drawFastLine(uint8_t x0, uint8_t y0, uint8_t l,
		    uint16_t color, uint8_t flag);

Commented out:
  void dummyclock(void);


 */

#include <ST7735.h>

const byte CS    = 10 ;
const byte DC    =  9 ;
const byte RESET =  8 ;

// NOTE:  R = 5 bits, G = 6 bits, B = 5 bits

const unsigned int BLACK = 0x0000 ;
const unsigned int RED   = 0xF800 ;
const unsigned int GREEN = 0x07E0 ;
const unsigned int BLUE  = 0x001F ;
const unsigned int WHITE = 0xFFFF ;

ST7735 lcd = ST7735(CS, DC, RESET);


//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	unsigned int color = RED ;
	lcd.initR() ;
	delay(2000) ;
	lcd.fillRect(0, 0, lcd.width, lcd.height, BLACK) ;
	delay(2000) ;
	for (unsigned int i=0; i<=lcd.height; i++) {
		lcd.drawHorizontalLine(0, i, lcd.width, color) ;
		switch (color) {
		case RED:
				color = GREEN ;
				break ;
		case GREEN:
				color = BLUE ;
				break ;
		case BLUE:
				color = RED ;
				break ;
			default:
				color = RED ;
				break ;
		}
		delay(100) ;
	}
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
}

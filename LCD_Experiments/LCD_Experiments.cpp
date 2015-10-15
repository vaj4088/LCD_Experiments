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

  x starts on the left and increases to the right.
  x goes from 0 to .width - 1

  y starts at the top and increases downward.
  y goes from 0 to .height - 1

  strings are drawn with the stated position being the upper left corner.
  circles are drawn with the stated position being the center of the circle.


 */

const byte CS    = 10 ;
const byte DC    =  9 ;
const byte RESET =  8 ;

ST7735 lcd = ST7735(CS, DC, RESET);
GLBall ball=GLBall(&lcd) ;

const unsigned int xBouncesToRepeat = 33 ;
unsigned int xBouncesRemaining = xBouncesToRepeat ;

//
//  This program displays a test pattern on the LCD screen,
//  waits two seconds,
//  then clears the screen and displays a "ball" that bounces around
//  the LCD screen.  The ball leaves a trail as it goes.
//

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	enum States {
		red1, red2, red3,
		green1, green2, green3,
		blue1, blue2, blue3
	} ;
	States state = red1 ;
	char strResult[17] ;
	int offset = 0 ;
	unsigned int color = RED ;
	lcd.initR() ;
	clearScreen(lcd) ;  //  Clear screen.
	Serial.begin(115200) ;
	for (unsigned int i=1; i<=lcd.height; i++) {
		const int size = 1 ; // size may be 1, 2, 3, 4, 5, 6, or 7.
		                     // size of 1 is smallest, size of 7 is largest.
		//
		//  Clear space for new data.
		//  Provides space for 3 digits.
		//
		lcd.fillRect(  10, 51, 18*size, 8*size, BLACK) ;
		//
		//  Write line number.
		//
		lcd.drawString(10, 51, itoa(i, strResult, 10), WHITE, size) ;
		//
		//  Draw the line.
		//
		lcd.drawHorizontalLine(offset, i-1, lcd.width-offset, color) ;
//		delay(10) ;
		if (i<lcd.width) {
			offset++ ;
		} else {
			offset-- ;
		}
		//
		//  Prepare for the next line.
		//
		switch (state) {
		case red1:
			state = red2 ;
			break ;
		case red2:
			state = red3 ;
			break ;
		case red3:
			state = green1 ;
			color = GREEN ;
			break ;
		case green1:
			state = green2 ;
			break ;
		case green2:
			state = green3 ;
			break ;
		case green3:
			state = blue1 ;
			color = BLUE ;
			break ;
		case blue1:
			state = blue2 ;
			break ;
		case blue2:
			state = blue3 ;
			break ;
		case blue3:
			state = red1 ;
			color = RED ;
			break ;
			default:
				state = red1 ;
				color = RED ;
				break ;
		}
	}
	delay(2000) ;
	clearScreen(lcd) ;
	//
	// Set up ball parameters
	//
	ball.setBallColor(CYAN)
	    .setTrailColor(YELLOW)
	    .begin() ;
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	//
	// Knowing when it is time to switch trail colors
	//
	int xVelPrevious = ball.getXVel() ;
	if (ball.update()) {
		int xVelCurrent = ball.getXVel() ;
		if (xVelCurrent == -xVelPrevious) {
			xBouncesRemaining-- ;
		}
		if (xBouncesRemaining==0) {
			ball.setTrailColor(~ball.getTrailColor()) ;
			ball.setBallColor(~ball.getBallColor())   ;
			xBouncesRemaining=xBouncesToRepeat ;
		}
	}
}

void clearScreen(ST7735 obj) {
	obj.fillRect(0, 0, lcd.width, lcd.height, BLACK); //  Clear screen.
}


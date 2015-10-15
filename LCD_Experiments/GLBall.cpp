/*
 * GLBall.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: Ian Shef
 */

#include "GLBall.h"

GLBall::GLBall(ST7735 *st7735)
	: frameTime (10)
	, radius (4)
	, xCurrent (radius)
	, yCurrent (radius)
	, ballColor (0xFFFF)
	, trailColor (ballColor)
	, xVel (1)
	, yVel (xVel)
	, lcd (st7735)
  {}

void        GLBall::begin() {
	this->previousTime = millis() ;
}

boolean        GLBall::update() {
	boolean returnValue = false ;
	currentTime = millis() ;
	if ( (currentTime - previousTime) >= frameTime) {
		returnValue = true ;
		previousTime = currentTime ;
		xPrevious = xCurrent ;
		yPrevious = yCurrent ;
		xCurrent += xVel ;
		yCurrent += yVel ;
		if (xVel>0) {
			if ((xCurrent+radius)>=lcd->width) {
				xVel = -xVel ;
				xCurrent += xVel ;
			}
		} else if (xVel<0) {
			if ((xCurrent-radius) <=0) {
				xVel = -xVel ;
				xCurrent += xVel ;
			}
		}
		if (yVel>0) {
			if ((yCurrent+radius)>=lcd->height) {
				yVel = -yVel ;
				yCurrent += yVel ;
			}
		} else if (yVel<0) {
			if ((yCurrent-radius) <=0) {
				yVel = -yVel ;
				yCurrent += yVel ;
			}
		}
		lcd->fillCircle(xPrevious, yPrevious, radius, trailColor) ;
		lcd->fillCircle(xCurrent, yCurrent, radius, ballColor) ;
	}
	return returnValue ;
}

unsigned int  GLBall::getBallColor() const {return ballColor;}
unsigned long GLBall::getFrameTime() const {return frameTime;}
unsigned int  GLBall::getRadius()    const {return radius;}
unsigned int  GLBall::getTrailColor()const {return trailColor;}
unsigned int  GLBall::getXCurrent()  const {return xCurrent;}
unsigned int  GLBall::getXPrevious() const {return xPrevious;}
         int  GLBall::getXVel()      const {return xVel;}
unsigned int  GLBall::getYCurrent()  const {return yCurrent;}
unsigned int  GLBall::getYPrevious() const {return yPrevious;}
         int  GLBall::getYVel()      const {return yVel;}
GLBall& GLBall::setBallColor(unsigned int ballColor) {
	this->ballColor = ballColor;
	return *this ;
}
GLBall& GLBall::setFrameTime(unsigned long frameTime = 10) {
	this->frameTime = frameTime;
	return *this ;
}
GLBall& GLBall::setRadius(int radius = 4) {
	this->radius = radius;
	return *this ;
}
GLBall& GLBall::setTrailColor(unsigned int trailColor) {
	this->trailColor = trailColor;
	return *this ;
}
GLBall& GLBall::setXCurrent(int current = 4) {
	xCurrent = current;
	return *this ;
}
GLBall& GLBall::setXPrevious(int previous) {
	xPrevious = previous;
	return *this ;
}
GLBall& GLBall::setXVel(int vel = 1) {
	xVel = vel;
	return *this ;
}
GLBall& GLBall::setYCurrent(int current = 4) {
	yCurrent = current;
	return *this ;
}
GLBall& GLBall::setYPrevious(int previous) {
	yPrevious = previous;
	return *this ;
}
GLBall& GLBall::setYVel(int vel = 1) {
	yVel = vel;
	return *this ;
}



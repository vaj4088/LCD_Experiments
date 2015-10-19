// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef LCD_Experiments_H_
#define LCD_Experiments_H_
#include "Arduino.h"
//add your includes for the project LCD_Experiments here

//#include <GL_ST7735.h>
#include <GLBall.h>

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project LCD_Experiments here

void clearScreen(GL_ST7735 obj) ;


//Do not add code below this line
#endif /* LCD_Experiments_H_ */

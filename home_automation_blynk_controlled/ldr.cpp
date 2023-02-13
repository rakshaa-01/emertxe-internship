#include "ldr.h"
#include "Arduino.h"
#include "main.h"

void init_ldr(void)
{
   pinMode(GARDEN_LIGHT, OUTPUT);
   
}
unsigned int inputVal = 0;
void brightness_control(void)
{
  //read the LDR values
  inputVal = analogRead(LDR_SENSOR);
  
  //reverse map from 0 - 1023 to 255 - 0
  inputVal = (1023 - inputVal)/4;

  //write values to led
  analogWrite(GARDEN_LIGHT, inputVal);
  delay(100);
}

/*************************************************************
Title         :   Home automation using blynk
Description   :   To control light's brigntness with brightness,monitor temperature , monitor water level in the tank through blynk app
Pheripherals  :   Arduino UNO , Temperature system, LED, LDR module, Serial Tank, Blynk cloud, Blynk App.
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLcOG3IrJj"
#define BLYNK_DEVICE_NAME "Home automation"
#define BLYNK_AUTH_TOKEN "rK02z3ShzrhHAiUu2oKRmjPdL4bAnmhe"


// Comment this out to disable prints 
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "main.h"
#include "temperature_system.h"
#include "ldr.h"
#include "serial_tank.h"

char auth[] = BLYNK_AUTH_TOKEN;
bool heater_sw,inlet_sw,outlet_sw;
unsigned int tank_volume;

BlynkTimer timer;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// This function is called every time the Virtual Pin 0 state changes
/*To turn ON and OFF cooler based virtual PIN value*/

BLYNK_WRITE(COOLER_V_PIN)
{
  int value = param.asInt();
  //If cooler button is ON in blynk, turn on cooler
  if (value)
  {
    cooler_control(ON);
    lcd.setCursor(7,0);
    lcd.print("CO_LR ON  ");
  }
  else
  {
    cooler_control(OFF);
    lcd.setCursor(7,0);
    lcd.print("CO_LR OFF ");
  }
}
/*To turn ON and OFF heater based virtual PIN value*/
BLYNK_WRITE(HEATER_V_PIN )
{
  heater_sw = param.asInt();
  //If heater button is ON in blynk, turn on heater
  if (heater_sw)
  {
    heater_control(ON);
    lcd.setCursor(7,0);
    lcd.print("HT_R ON  ");
  }
  else
  {
    heater_control(OFF);
    lcd.setCursor(7,0);
    lcd.print("HT_R OFF ");
  }
}
/*To turn ON and OFF inlet vale based virtual PIN value*/
BLYNK_WRITE(INLET_V_PIN)
{
  inlet_sw = param.asInt();
  if(inlet_sw)
  {
    enable_inlet();
    lcd.setCursor(7,1);
    lcd.print("IN_FL_ON ");
  }
  else
  {
    disable_inlet();
    lcd.setCursor(7,1);
    lcd.print("IN_FL_OFF");
  }
}

/*To turn ON and OFF outlet value based virtual switch value*/
BLYNK_WRITE(OUTLET_V_PIN)
{
  outlet_sw = param.asInt();
  if(outlet_sw)
  {
    enable_outlet();
    lcd.setCursor(7,1);
    lcd.print("OT_FL_ON ");
  }
  else
  {
    disable_outlet();
    lcd.setCursor(7,1);
    lcd.print("OT_FL_OFF");
  }
}
/* To display temperature and water volume as gauge on the Blynk App*/  
void update_temperature_reading()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(TEMPERATURE_GAUGE, read_temperature());
  Blynk.virtualWrite(WATER_VOL_GAUGE, volume());
}

/*To turn off the heater if the temperature raises above 35 deg C*/
void handle_temp(void)
{
  //compare temperature with 35 deg and check if heater is ON
  if((read_temperature() > float(35)) && (heater_sw))
  {
    heater_sw = 0;
    heater_control(OFF);

    lcd.setCursor(7,0);
    lcd.print("HT_R OFF ");

    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Temperature is above 35°C \n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Turning OFF the heater \n");

    //To reflect OFF on the heater button
    Blynk.virtualWrite(HEATER_V_PIN, OFF);
  }    
}

/*To control water volume above 2000ltrs*/
void handle_tank(void)
{
  if(( tank_volume<2000) && (inlet_sw == OFF))
  {
    enable_inlet();
    lcd.setCursor(7,1);
    lcd.print("IN_FL_ON ");
    inlet_sw = ON;

    //To reflect ON on inlet virtual pin
    Blynk.virtualWrite(INLET_V_PIN, ON);

    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Water volume is < 2000 litres \n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Turning ON the inlet valve \n");
  }
  
  //Checking if tank volume is full, then turn OFF the inlet valve
  if(( tank_volume==3000) && (inlet_sw == ON))
  {
    disable_inlet();
    lcd.setCursor(7,1);
    lcd.print("IN_FL_OFF");
    inlet_sw = OFF;

    //To reflect ON on inlet virtual pin
    Blynk.virtualWrite(INLET_V_PIN, OFF);

    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Water volume is FULL \n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN, "Turning OFF the inlet valve \n");
  }

}

void setup(void)
{
  //initialise LCD
  lcd.init();
  //turn backlight
  lcd.backlight();
  //clear clcd
  lcd.clear();
  //point cursor to home
  lcd.home();

  //initialising garden lights as output pin
  init_ldr();

  //initialising temp system
  init_temperature_system();

  lcd.setCursor(0, 0);
  lcd.print("T=");


  //Set cursor to 2nd line
  lcd.setCursor(0, 1);
  lcd.print("V=");
  init_serial_tank();


  //For updating the timer on Blynk app for every 0.5 sec
  timer.setInterval(500L, update_temperature_reading);

  //connecting arduino to blynk server
  Blynk.begin(auth);
}

void loop(void) 
{
  //control brightness of garden lights using LDR sensor
  brightness_control();

  lcd.setCursor(2,0);

  String temp;
  temp = String (read_temperature(), 2);

  //For displaying the temperature on CLCD
  lcd.print(temp);

  tank_volume = volume();
  lcd.setCursor(2,1);
  lcd.print(tank_volume);

  //To check threshold temp and controlling heater
  handle_temp(); 
  
  //To monitor the volume of water, turn ON the inlet valve if V < 2000 ltrs
  handle_tank();

  timer.run();
  //To run the Blynk application
  Blynk.run();
}

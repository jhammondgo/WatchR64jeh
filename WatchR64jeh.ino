 /* Arduino Watch
 By Matthew Garten
 Sept 24, 2012
 Rev 64 
 Modified November 7, 2015 to allow uOLED-96-G2 display by
 John Hammond
 
 Copyright (C) 2010  Matthew Garten
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 */


//Start libraries for DS1307 RTC
#include <Wire.h>
#include "RTClib.h"  //adafruit RTC library

RTC_DS1307 RTC;
//End libraries for DS1307 RTC


//Start OneWire libraries for external sensors
#include <OneWire.h>   //Arduino playground library
#include <DallasTemperature.h>  //Arduino playground library

#define ONE_WIRE_BUS 10  // Data wire is plugged into pin 2 on the Arduino
OneWire oneWire(ONE_WIRE_BUS);  // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature temper_sensors(&oneWire);  // Pass our oneWire reference to Dallas Temperature.
//End OneWire libraries for external sensors

//Start library for the OLED display

//next 10 lines added 11/21/2015 jeh

  #define DisplaySerial Serial
#ifdef LOG_MESSAGES
  #define HWLOGGING Serial
#else  
  #define HWLOGGING if (1) {} else Serial
#endif
    
#include "Goldelox_Serial_4DLib.h"
#include "GoldeloxBigDemo.h"
#include "Goldelox_Const4D.h"
Goldelox_Serial_4DLib Display(&DisplaySerial);
 
 
#include <uOLED.h>  //Custom uOLED library plan to switch to http://embeddedcomputing.weebly.com/serial-lcd.html to have a more general library
uOLED uoled;  

int display_reset_pin = 4;  // select the pin used to connect the display's reset pin
//End library for the OLED display

// Start general variables
int mode = 0; //select which mode the watch is in
int lastmode = 0; // last mode the watch was in, used for knowing when modes switch
int modechange = 0; // for passing the mode switch into the functions 
int n=0;
#define screen_pixels_x 95  // size of the screen in pixels - 1, i.e. 128 pixel screen is 127 for the 0-127 index
#define screen_pixels_y 63  // size of the screen in pixels - 1, i.e. 128 pixel screen is 127 for the 0-127 index
#define screen_adjust_x 16  // move to center programs written for the the 96x64 pixels screen
#define screen_adjust_y 32  // move to center programs written for the the 96x64 pixels screen
// End general variables

//Start time variables
int year = 9999;  // these get reset to the compile date and time
int month = 0;
int day = 0;
int hour = 0;
int minute = 0;
int sec = 0;

char hour_str[3];
char minute_str[3];
char sec_str[3];
char day_str[3];   
char month_str[4];
char year_str[5];
char time_str[9];
char date_str[13];
//End time variables

//Start set_time variables
int time_x = 1;
int time_y = 1;
//End set_time variables


//Start color scheme variables
unsigned int color = 63488;  
unsigned int fast_color = 65504;
unsigned int med_color = 150;
unsigned int slow_color = 63488;
unsigned int background_color = 0;
//End color scheme variables

//Start trackball variables
int x_pos = 40;  //start near center of screen
int y_pos = 30;  //start near center of screen
int xy_empty = 0;   //use when you only want to change x or y and need to pass a variable

int rightpin = 9;
int leftpin = 8;
int uppin = 7;
int downpin = 6;

int buttonpin = 3;

int rightstate = 0;
int leftstate = 0;
int upstate = 0;
int downstate = 0;

int buttonstate = 0;
int buttonlaststate = 0;

int powerpin = 2;  
int powerpin2 = 12;  

//End trackball variables

int groundpin = 13;

//Start Paint variables
byte painttoggle = 0;
int color_x = 0;  
int color_y = 0;
//End Paint variables

//Start Temper variables
int temper_num = 0;  // number of temperature sensors

//End Temper variables

//Start MaxSonar variables
int sonarpin = 11;
int sonar_in;
int sonar_cm;
//End MaxSonar variables

//Start menu variables
#define item_size_x 50
#define item_size_y 12
#define item1_corner_x 20
#define item1_corner_y 80  
#define item2_corner_x 70
#define item2_corner_y 5
#define item3_corner_x 5
#define item3_corner_y 5
#define item4_corner_x 5
#define item4_corner_y 30
#define item5_corner_x 70
#define item5_corner_y 30
#define item6_corner_x 70
#define item6_corner_y 55
//End menu variables


void setup() 
{
  uoled.begin(display_reset_pin, 256000, &Serial);// with the reset line connected to pin 3 and a serial speed of 256000 

  attachInterrupt(1, click, FALLING);

  //Start Time setup
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));  //set to time of compile year, month, day, hour, min, sec
  //End Time setup

  //Start Trackball setup
  pinMode(rightpin, INPUT);
  pinMode(leftpin, INPUT);
  pinMode(uppin, INPUT);
  pinMode(downpin, INPUT);
  pinMode(buttonpin, INPUT);

  digitalWrite(rightpin, LOW);
  digitalWrite(leftpin, LOW);
  digitalWrite(uppin, LOW);
  digitalWrite(downpin, LOW);
  digitalWrite(buttonpin, LOW);

  pinMode(powerpin, OUTPUT);
  digitalWrite(powerpin, HIGH);
  //End Trackball setup

  pinMode(powerpin2, OUTPUT);
  digitalWrite(powerpin2, HIGH);

  pinMode(groundpin, OUTPUT);
  digitalWrite(groundpin, LOW);

  //Start Paint setup
  uoled.AddBMPChar(1, 0xff, 0xc3, 0xa5, 0x99, 0x99, 0xa5, 0xc3, 0xff); // exit X box
  //uoled.AddBMPChar(2, 0x0f, 0x13, 0x25, 0x49, 0xf2, 0x94, 0xf8, 0x00); // erase icon
  uoled.AddBMPChar(2, 0x7e, 0x40, 0x40, 0x40, 0x78, 0x40, 0x40, 0x7e); // new erase icon, letter E
  uoled.AddBMPChar(3, 0x00, 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x18, 0x00); // paint color, a dot
  uoled.AddBMPChar(4, 0xff, 0x99, 0x99, 0x99, 0xff, 0xbd, 0x99, 0xff); // down arrow or save icon
  uoled.AddBMPChar(5, 0xff, 0x99, 0xbd, 0xff, 0x99, 0x99, 0x99, 0xff); // up arrow or load icon
  //End Paint setup

  //Start Breakout setup
  uoled.AddBMPChar(6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff); // solid icon for clearing the spot
  uoled.AddBMPChar(7, 0x00, 0x00, 0xff, 0x81, 0x81, 0xff, 0x00, 0x00); // empty block
  uoled.AddBMPChar(8, 0x00, 0x00, 0xff, 0xd4, 0xab, 0xff, 0x00, 0x00); // checker block
  uoled.AddBMPChar(9, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00); // solid block
  uoled.AddBMPChar(10, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xaa, 0x44); // spiked block
  // End Breakout setup

  //Start temper setup
  temper_sensors.begin();
  temper_num = temper_sensors.getDeviceCount(); // get the number of sensors and store in temper_num
  // End temper setup

  //Start MaxSonar setup
  pinMode(sonarpin, INPUT);

}

void loop() 
{
  if(lastmode != mode) // if the mode switches clear the screen and set the modechange variable for apps to use
  {
    uoled.Cls();
    modechange = 1;
  }
  lastmode = mode;
  switch(mode)
  {
  case 0:
    time_jeh();
    uoled.Text(4,4, 2, 75, time_str,1);
    uoled.Text(2,5, 2, 75, date_str,1);
    break;

  case 1:
    time_jeh();
    clockbinary();
    break;

  case 2:
    time_jeh();    
    clockanalog();
    break;

  case 3:
    menu();
    break;

  case 4:
    mode = 0; // reset to beginning of clocks, programs accessed through the menu
    break;

  case 5:
    paint();
    break;

  case 6:
    breakout();
    break;

  case 7:
    temper();
    break;

  case 8:
    range();
    break;

  case 9:
    set_time();
    break;

  }



  //  y = (x >> n) & 1;    // n=0..15.  stores nth bit of x in y.  y becomes 0 or 1.
  /*
  n++;
   
   //delay(1000);
   if(n == 900)
   {
   uoled.SetPowerState(0);
   delay(4000);
   uoled.SetPowerState(1);
   n=0;
   }
   */
}




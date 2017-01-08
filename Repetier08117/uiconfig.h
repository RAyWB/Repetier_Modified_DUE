/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

/* ===================== IMPORTANT ========================

The LCD and Key support is new. I tested everything as good as possible,
but some combinations may not work as supposed.
The I2C methods rely on a stable I2C connection. Noise may cause wrong signals
which can cause the firmware to freeze.

The ui adds quite some code, so AVRs with 64kB ram (Sanguino, Gen6) can not handle all features
of the firmware at the same time. You have to disable some features to gain the
ram needed. What should work:
- No sd card - the sd card code is quite large.
- No keys attached - The longest part is the menu handling.
- EEPROM_MODE 0 .

Currently supported hardware:

*** Displays ***

- direct connected lcd with 4 data lines
- connected via i2c

*** Keys ***

- rotary encoder
- push button
- key matrix up to 4x4
- rotary encoder via i2c (only slow turns are captured correct)
- push button via i2c

*** Buzzer ***

- directly connected, high = on
- connected via i2c, low = on

==============================================================*/

#ifndef _ui_config_h
#define _ui_config_h


//####RAyWB playground :-)

#include"RAyWB_macro.h"


#ifdef FEATURE_I2C_MACROS
#define COMPILE_I2C_DRIVER 

#define MCP_IN_ADDRESS 0x40
#define MCP_OUT_ADDRESS 0x48

// registers
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14


#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

#define MCP23017_INT_ERR 255

#define MCP23017_KEYS_I2C_BUTTON_LOW(pin,action_) if((keymask1 & pin)==0) action=action_;
#endif

//########################

/** While the ascii chars are all the same, the driver have different charsets
for special chars used in different countries. The charset allows to fix for
this problem. If characters look wrong, try a different charset. If nothing
works, use the ascii charset 0 as fallback. Not the nicest for everything but working!

0 = ASCII fallback
1 = Default works on most displays. This has some japanese chars in charset
2 = Alternative charset with more european chars

*/
#define UI_DISPLAY_CHARSET 2

/** Select type of beeper
0 = none
1 = Piezo connected to pin
2 = Piezo connected to a pin over I2C
*/
#ifndef BEEPER_TYPE
#define BEEPER_TYPE 2
#define BEEPER_TYPE_INVERTING false
#endif

#if BEEPER_TYPE==1 && !defined(BEEPER_PIN)
#define BEEPER_PIN ORIG_BEEPER_PIN
#endif
#if BEEPER_TYPE==2
#define BEEPER_ADDRESS 0x4e // I2C address of the chip with the beeper pin
#define BEEPER_PIN _BV(7)  // Bit value for pin 8
#define COMPILE_I2C_DRIVER  // We need the I2C driver as we are using i2c
#endif


/**
What display type do you use?
0 = No display - do not use here. Set FEATURE_CONTROLLER 0 instead
1 = LCD Display with 4 bit data bus
2 = LCD Display with 8 bit data bus (currently not implemented, fallback to 1)
3 = LCD Display with I2C connection, 4 bit mode
4 = Use the slower LiquiedCrystal library bundled with arduino.
    IMPORTANT: You need to uncomment the LiquidCrystal include in Repetier.pde for it to work.
               If you have Sanguino and want to use the library, you need to have Arduino 023 or older. (13.04.2012)
5 = U8G supported display
*/
#define UI_DISPLAY_TYPE 5

#if UI_DISPLAY_TYPE == DISPLAY_U8G // Special case for graphic displays

// You need to define which controller you use and set pins accodringly

// For software spi assign these definitions
// SCK Pin:  UI_DISPLAY_D4_PIN
// Mosi Pin: UI_DISPLAY_ENABLE_PIN
// CD Pin:   UI_DISPLAY_RS_PIN

// ST7920 with software SPI
#define U8GLIB_ST7920
// SSD1306 with software SPI
//#define U8GLIB_SSD1306_SW_SPI
// SH1106 with software SPI
// U8GLIB_SH1106_SW_SPI
// SSD1306 over I2C using hardware I2C pins
//#define U8GLIB_SSD1306_I2C
// For the 8 bit ks0108 display you need to set these pins
// UI_DISPLAY_D0_PIN,UI_DISPLAY_D1_PIN,UI_DISPLAY_D2_PIN,UI_DISPLAY_D3_PIN,UI_DISPLAY_D4_PIN,UI_DISPLAY_D5_PIN,UI_DISPLAY_D6_PIN,UI_DISPLAY_D7_PIN
// UI_DISPLAY_ENABLE_PIN,UI_DISPLAY_CS1,UI_DISPLAY_CS2,
// UI_DISPLAY_DI,UI_DISPLAY_RW_PIN,UI_DISPLAY_RESET_PIN
//#define U8GLIB_KS0108
//#define U8GLIB_KS0108_FAST
// UI_DISPLAY_RS_PIN = CS
// UI_DISPLAY_D5_PIN = A0
//#define U8GLIB_ST7565_NHD_C2832_HW_SPI

#define UI_LCD_WIDTH 128
#define UI_LCD_HEIGHT 64

//select font size
#define UI_FONT_6X10 //default font
#ifdef UI_FONT_6X10
#define UI_FONT_WIDTH 6
#define UI_FONT_HEIGHT 10
#define UI_FONT_SMALL_HEIGHT 7
#define UI_FONT_DEFAULT repetier_6x10
#define UI_FONT_SMALL repetier_5x7
#define UI_FONT_SMALL_WIDTH 5 //smaller font for status display
#endif

//calculate rows and cols available with current font
#define UI_COLS (UI_LCD_WIDTH/UI_FONT_WIDTH)
#define UI_ROWS (UI_LCD_HEIGHT/UI_FONT_HEIGHT)
#define UI_DISPLAY_CHARSET 3
#else
/** Number of columns per row
Typical values are 16 and 20
*/
#define UI_COLS 20
/**
Rows of your display. 2 or 4
*/
#define UI_ROWS 4
#endif // UI_DISPLAY_TYPE

/* What type of chip is used for I2C communication
0 : PCF8574 or PCF8574A or compatible chips.
1 : MCP23017
*/
#define UI_DISPLAY_I2C_CHIPTYPE 0
// 0x40 till 0x4e for PCF8574, 0x40 for the adafruid RGB shield, 0x40 - 0x4e for MCP23017
// Official addresses have a value half as high!
#define UI_DISPLAY_I2C_ADDRESS 0x4e
// For MCP 23017 define which pins should be output
#define UI_DISPLAY_I2C_OUTPUT_PINS 65504
// Set the output mask that is or'd over the output data. This is needed to activate
// a backlight switched over the I2C.
// The adafruit RGB shields enables a light if the bit is not set. Bits 6-8 are used for backlight.
#define UI_DISPLAY_I2C_OUTPUT_START_MASK 0
// For MCP which inputs are with pullup. 31 = pins 0-4 for adafruid rgb shield buttons
#define UI_DISPLAY_I2C_PULLUP 31
/* How fast should the I2C clock go. The PCF8574 work only with the lowest setting 100000.
A MCP23017 can run also with 400000 Hz */
#define UI_I2C_CLOCKSPEED 100000L
/**
Define the pin
*/
#if UI_DISPLAY_TYPE == DISPLAY_I2C // I2C Pin configuration
#define UI_DISPLAY_RS_PIN _BV(4)
#define UI_DISPLAY_RW_PIN _BV(5)
#define UI_DISPLAY_ENABLE_PIN _BV(6)
#define UI_DISPLAY_D0_PIN _BV(0)
#define UI_DISPLAY_D1_PIN _BV(1)
#define UI_DISPLAY_D2_PIN _BV(2)
#define UI_DISPLAY_D3_PIN _BV(3)
#define UI_DISPLAY_D4_PIN _BV(0)
#define UI_DISPLAY_D5_PIN _BV(1)
#define UI_DISPLAY_D6_PIN _BV(2)
#define UI_DISPLAY_D7_PIN _BV(3)

// uncomment if your using led to indicated the bed is hot
//#define UI_I2C_HEATBED_LED    _BV(8)

// uncomment if your using led to indicated the extruder is hot
//#define UI_I2C_HOTEND_LED     _BV(7)

// uncomment if your using led to indicated the FAN is on
//#define UI_I2C_FAN_LED        _BV(6)

// Pins for adafruid RGB shield
/*#define UI_DISPLAY_RS_PIN _BV(15)
#define UI_DISPLAY_RW_PIN _BV(14)
#define UI_DISPLAY_ENABLE_PIN _BV(13)
#define UI_DISPLAY_D0_PIN _BV(12)
#define UI_DISPLAY_D1_PIN _BV(11)
#define UI_DISPLAY_D2_PIN _BV(10)
#define UI_DISPLAY_D3_PIN _BV(9)
#define UI_DISPLAY_D4_PIN _BV(12)
#define UI_DISPLAY_D5_PIN _BV(11)
#define UI_DISPLAY_D6_PIN _BV(10)
#define UI_DISPLAY_D7_PIN _BV(9)*/


#else // Direct display connections
#define UI_DISPLAY_RS_PIN     UI_Display_CS   // 44 CS 
#define UI_DISPLAY_ENABLE_PIN UI_Display_Data // 43 Data 
#define UI_DISPLAY_RW_PIN -1
#define UI_DISPLAY_D0_PIN -1    
#define UI_DISPLAY_D1_PIN -1    
#define UI_DISPLAY_D2_PIN -1    
#define UI_DISPLAY_D3_PIN -1    
#define UI_DISPLAY_D4_PIN     UI_Display_CK   // 45 clk 
#define UI_DISPLAY_D5_PIN -1    
#define UI_DISPLAY_D6_PIN -1    
#define UI_DISPLAY_D7_PIN -1    
#define UI_DELAYPERCHAR      50

// Special pins for some u8g driven display

#define UI_DISPLAY_CS1 -1
#define UI_DISPLAY_CS2 -1
#define UI_DISPLAY_DI  -1
#define UI_DISPLAY_RW_PIN -1
#define UI_DISPLAY_RESET_PIN -1
#endif


/** \brief Are some keys connected?

0 = No keys attached - disables also menu
1 = Some keys attached
*/
#define UI_HAS_KEYS 1


/** \brief Is a back key present.

If you have menus enabled, you need a method to leave it. If you have a back key, you can always go one level higher.
Without a back key, you need to navigate to the back entry in the menu. Setting this value to 1 removes the back entry.
*/
#define UI_HAS_BACK_KEY 0

/* Then you have the next/previous keys more like up/down keys, it may be more intuitive to change the direction you skip through the menus.
If you set it to true, next will go to previous menu instead of the next menu.

*/
#define UI_INVERT_MENU_DIRECTION 0

/** Uncomment this, if you have keys connected via i2c to a PCF8574 chip. */
//#define UI_HAS_I2C_KEYS

// Do you have a I2C connected encoder?
#define UI_HAS_I2C_ENCODER 0

// Under which address can the key status requested. This is the address of your PCF8574 where the keys are connected.
// If you use a MCP23017 the address from display is used also for keys.
#define UI_I2C_KEY_ADDRESS 0x4e


#ifdef UI_MAIN
/* #######################################################################
                      Key definitions

The firmware is very flexible regarding your input methods. You can use one
or more of the predefined key macros, to define a mapper. If no matching mapper
is available, you can add you c-code for mapping directly into the keyboard
routines. The predefined macros do the same, just hiding the code behind it.

For each key, two seperate parts must be defined. The first is the initialization
which must be added inside uiInitKeys() and the second ist a testing routine.
These come into uiCheckKeys() or uiCheckSlowKeys() depending on the time needed
for testing. If you are in doubt, put it in uiCheckSlowKeys().
uiInitKeys() is called from an interrupt controlling the extruder, so only
fast tests should be put there.
The detect methods need an action identifier. A list of supported ids is found
at the beginning of ui.h It's best to use the symbol name, in case the value changes.

1. Simple push button connected to gnd if closed on a free arduino pin
    init -> UI_KEYS_INIT_BUTTON_LOW(pinNumber);
    detect -> UI_KEYS_BUTTON_LOW(pinNumber,action);

2. Simple push button connected to 5v if closed on a free arduino pin
    init -> UI_KEYS_INIT_BUTTON_HIGH(pinNumber);
    detect -> UI_KEYS_BUTTON_HIGH(pinNumber,action);

3. Click encoder, A/B connected to gnd if closed.
    init -> UI_KEYS_INIT_CLICKENCODER_LOW(pinA,pinB);
    detect -> UI_KEYS_CLICKENCODER_LOW(pinA,pinB);
         or   UI_KEYS_CLICKENCODER_LOW_REV(pinA,pinB); // reverse direction
    If you can move the menu cursor without a click, just be adding some force in one direction,
    toggle the _REV with non _REV and toggle pins.
    If the direction is wrong, toggle _REV with non _REV version.
    For the push button of the encoder use 1.

4. Click encoder, A/B connected to 5V if closed.
    init -> UI_KEYS_INIT_CLICKENCODER_HIGH(pinA,pinB);
    detect -> UI_KEYS_CLICKENCODER_HIGH(pinA,pinB);
         or   UI_KEYS_CLICKENCODER_HIGH_REV(pinA,pinB); // reverse direction
    If you can move the menu cursor without a click, just be adding some force in one direction,
    toggle the _REV with non _REV and toggle pins.
    If the direction is wrong, toggle _REV with non _REV version.
    For the push button of the encoder use 2.

5. Maxtrix keyboard with 1-4 rows and 1-4 columns.
    init -> UI_KEYS_INIT_MATRIX(r1,r2,r3,r4,c1,c2,c3,c4);
    detect -> UI_KEYS_MATRIX(r1,r2,r3,r4,c1,c2,c3,c4);
    In addition you have to set UI_MATRIX_ACTIONS to match your desired actions.

------- Keys connected via I2C -------------

All keys and the buzzer if present must be on a connected to a single PCF8574 chip!
As all I2C request take time, they belong all in uiCheckSlowKeys.
Dont use the pin ids but instead _BV(pinNumber0_7) as pin id. 0 = First pin

6. Click encoder, A/B connected to gnd if closed.
    init -> not needed, but make sure UI_HAS_I2C_KEY is not commented out.
    detect -> UI_KEYS_I2C_CLICKENCODER_LOW(pinA,pinB);
         or   UI_KEYS_I2C_CLICKENCODER_LOW_REV(pinA,pinB); // reverse direction
    If you can move the menu cursor without a click, just be adding some force in one direction,
    toggle the _REV with non _REV and toggle pins.
    If the direction is wrong, toggle _REV with non _REV version.
    For the push button of the encoder use 7.
    NOTICE: The polling frequency is limited, so only slow turns are captured correct!

7. Simple push button connected to gnd if closed via I2C on a PCF8574
    init -> not needed, but make sure UI_HAS_I2C_KEY is not commented out.
    detect -> UI_KEYS_I2C_BUTTON_LOW(pinNumber,action);

-------- Some notes on actions -------------

There are three kinds of actions.

Type 1: Immediate actions - these are execute and forget actions like home/pre-heat
Type 2: Parameter change action - these change the mode for next/previous keys. They are valid
        until a new change action is initiated or the action is finished with ok button.
Type 3: Show menu action. These actions have a _MENU_ in their name. If they are executed, a new
        menu is pushed on the menu stack and you see the menu. If you assign these actions directly
        to a key, you might not want this pushing behaviour. In this case add UI_ACTION_TOPMENU to the
        action, like UI_ACTION_TOPMENU+UI_ACTION_MENU_XPOSFAST. That will show the menu as top-menu
        closing all othe submenus that were open.

   ####################################################################### */

// Use these codes for key detect. The main menu will show the pressed action in the lcd display.
// after that assign the desired codes.
//#define UI_MATRIX_ACTIONS {2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015}
// Define your matrix actions
#define UI_MATRIX_ACTIONS {UI_ACTION_HOME_ALL, UI_ACTION_TOP_MENU,       UI_ACTION_SET_ORIGIN,      UI_ACTION_NEXT,\
                           UI_ACTION_HOME_Z,   UI_ACTION_MENU_ZPOS,      UI_ACTION_COOLDOWN,        UI_ACTION_OK,\
                           UI_ACTION_HOME_Y,   UI_ACTION_MENU_YPOSFAST,  UI_ACTION_PREHEAT_ABS,     UI_ACTION_PREVIOUS,\
                           UI_ACTION_HOME_X,   UI_ACTION_MENU_XPOSFAST,  UI_ACTION_DISABLE_STEPPER, UI_ACTION_BACK}
#ifdef UI_MATRIX_ACTIONS
const int matrixActions[] PROGMEM = UI_MATRIX_ACTIONS;
#endif

void uiInitKeys() {
#if UI_HAS_KEYS!=0
  UI_KEYS_INIT_CLICKENCODER_LOW(ENC_A,ENC_B); // click encoder on pins 43 and 45. Phase is connected with gnd for signals.
  UI_KEYS_INIT_BUTTON_LOW(OK_BUTTON); // push button, connects gnd to pin
  UI_KEYS_INIT_BUTTON_LOW(UI1_BUTTON); // push button, connects gnd to pin
  UI_KEYS_INIT_BUTTON_LOW(UI2_BUTTON); // push button, connects gnd to pin
  UI_KEYS_INIT_BUTTON_LOW(HOME_BUTTON); // push button, connects gnd to pin

#endif
}
void uiCheckKeys(uint16_t &action) {
#if UI_HAS_KEYS!=0
  UI_KEYS_CLICKENCODER_LOW_REV(ENC_A,ENC_B); // click encoder on pins 43 and 45. Phase is connected with gnd for signals.
  
if(OK_BUTTON!=M6_ACK_PIN) //prevent double use of OK button
  UI_KEYS_BUTTON_LOW(OK_BUTTON,UI_ACTION_OK); // push button, connects gnd to pin
  
  UI_KEYS_BUTTON_LOW(UI2_BUTTON,UI_ACTION_X_ZERO);
  UI_KEYS_BUTTON_LOW(UI2_BUTTON,UI_ACTION_Y_ZERO);
  UI_KEYS_BUTTON_LOW(HOME_BUTTON,UI_ACTION_HOME_ALL);

#endif
}// End Check keys

//#####RAyWB ### Feature Joystick i like it ,works not too bad
//               i just use a hacked Gamepad
void uiCheckJoystick(uint16_t &action) // assigned to slow action
{
//button assignment x-axis

struct {uint16_t min;uint16_t max;uint16_t action;}
    keys_x[] = {
               {   0,   800, UI_ACTION_X_DOWN10       },    // down 10 mm steps
               {   810,   1200, UI_ACTION_X_DOWN1     },    // down 1 mm steps
               {   1210,   1700, UI_ACTION_X_DOWN01   },    // down 0.1 mm steps
               {   1710,  2000, UI_ACTION_X_DOWN001   },    // down 0.01 mm steps
    
               {  2200,  2350, UI_ACTION_X_UP001       },    // up 0.01mm steps
               {  2370,  2500, UI_ACTION_X_UP01        },    // up 0.1 mm steps
               {  2510,  2650, UI_ACTION_X_UP1         },    // up 1mm steps
               {  2660,  2750, UI_ACTION_X_UP10        },    // up 10 mm steps
           
               };
     const uint8_t numOfKeys_x = sizeof(keys_x) / sizeof(keys_x[0]);
     extern volatile uint16_t osAnalogInputValues[ANALOG_INPUTS];
     uint16_t adc_x = osAnalogInputValues[KEYPAD_ANALOG_INDEX] >> (ANALOG_REDUCE_BITS);

  if (adc_x<3800)//((adc_x<2000)|| ((adc_x>2000)&&(adc_x<3000))||(adc_x>3600)) 
    {
    for (int8_t ix = 0; ix < numOfKeys_x; ++ix) 
      {
      if ((adc_x > keys_x[ix].min) && (adc_x< keys_x[ix].max)) 
       {
        action = keys_x[ix].action;
        return ;
        }
     }
   }


//button assignment y-axis

struct {uint16_t min;uint16_t max;uint16_t action;} 
    keys_y[] = {
               {   0,   800, UI_ACTION_Y_UP10        },    // Up 10 mm Steps
               {   810, 1200, UI_ACTION_Y_UP1        },    // Up 1mm Steps
               {   1210,1800, UI_ACTION_Y_UP01       },    // Up 0.1 mm Steps
               {   1810,2000, UI_ACTION_Y_UP001      },    // Up 0.01 mm steps
    
               {  2200,  2350, UI_ACTION_Y_DOWN001   },    // Down 0.01mm Steps
               {  2370,  2500, UI_ACTION_Y_DOWN01    },    // Down 0.1mm Steps
               {  2510,  2650, UI_ACTION_Y_DOWN1     },    // Down 1mm Steps
               {  2660,  3000, UI_ACTION_Y_DOWN10    },    // Down 10 mm Steps
        
               };
                
       const uint8_t numOfKeys2 = sizeof(keys_y) / sizeof(keys_y[0]);
       uint16_t adc_y = osAnalogInputValues[KEYPAD2_ANALOG_INDEX] >> (ANALOG_REDUCE_BITS);
  
  if (adc_y<3800) //((adc_y<2000)|| ((adc_y>2000)&&(adc_y<3000))||(adc_y>3600))
    {
    for (int8_t iy = 0; iy < numOfKeys2; ++iy)
      {
      if ((adc_y > keys_y[iy].min) && (adc_y < keys_y[iy].max)) 
        {
        action = keys_y[iy].action;
        return ;
        }
      }
    }

// Button assignment Z-Axis
  
struct {uint16_t min;uint16_t max;uint16_t action;} 
    keys_z[] = {
               {   810, 1200, UI_ACTION_Z_UP1        },    // Up 1mm steps
               {   1210,1800, UI_ACTION_Z_UP01       },    // Up 0.1 mm steps
               {   1810,2000, UI_ACTION_Z_UP001      },    // Up 0.01 mm steps
         
               {  2200,  2350, UI_ACTION_Z_DOWN001   },    //Down 0.01 mm steps 
               {  2370,  2500, UI_ACTION_Z_DOWN01    },    //Down 0.1 mm steps
               {  2510,  2650, UI_ACTION_Z_DOWN1     },    // Down 1mm steps
               };
                
          const uint8_t numOfKeysz = sizeof(keys_z) / sizeof(keys_z[0]);
          uint16_t adc_z = osAnalogInputValues[KEYPAD3_ANALOG_INDEX] >> (ANALOG_REDUCE_BITS);
  
  if (adc_z<3800)//((adc_z<2000)|| ((adc_z>2000)&&(adc_z<3000))||(adc_z>3600))
    {
    for (int8_t iz = 0; iz < numOfKeysz; ++iz) 
      {
      if ((adc_z > keys_z[iz].min) && (adc_z < keys_z[iz].max)) 
       {
       action = keys_z[iz].action;
       return ; // no need for that  
       }
     }
    }

}

//############# end joystick

inline void uiCheckSlowEncoder() {
#if defined(UI_HAS_I2C_KEYS) && UI_HAS_KEYS!=0
#if UI_DISPLAY_I2C_CHIPTYPE==0
  HAL::i2cStartWait(UI_I2C_KEY_ADDRESS+I2C_READ);
  uint8_t keymask = HAL::i2cReadNak(); // Read current key mask
#endif
#if UI_DISPLAY_I2C_CHIPTYPE==1
    HAL::i2cStartWait(UI_DISPLAY_I2C_ADDRESS+I2C_WRITE);
    HAL::i2cWrite(0x12); // GIOA
    HAL::i2cStop();
    HAL::i2cStartWait(UI_DISPLAY_I2C_ADDRESS+I2C_READ);
    uint16_t keymask = HAL::i2cReadAck();
    keymask = keymask + (HAL::i2cReadNak()<<8);
#endif
  HAL::i2cStop();
  // Add I2C click encoder tests here, all other i2c tests and a copy of the encoder test belog in uiCheckSlowKeys
  UI_KEYS_I2C_CLICKENCODER_LOW_REV(_BV(2),_BV(0)); // click encoder on pins 0 and 2. Phase is connected with gnd for signals.
#endif
}



void uiCheckSlowKeys(uint16_t &action) {


//##### just some "weird" playing around on I2C ;-)

#if defined( FEATURE_I2C_MACROS) && FEATURE_I2C_MACROS !=0
{
   // initialize MCP23017
    HAL::i2cStartWait(MCP_IN_ADDRESS + I2C_WRITE);
    HAL::i2cWrite(0x00);//IODIRA
    HAL::i2cWrite(0xFF);
    HAL::i2cWrite(0xFF);
    HAL::i2cStop(); 
    HAL::i2cStartWait(MCP_IN_ADDRESS + I2C_WRITE);
    HAL::i2cWrite(0x12);//IODIRA
    HAL::i2cStop(); 
   
    HAL::i2cStartWait(MCP_IN_ADDRESS + I2C_READ);
    uint16_t keymask1 = (HAL::i2cReadAck()<<8);
    keymask1 += HAL::i2cReadNak();
    HAL::i2cStop();
       
switch (keymask1) {
      case 0xFFFE://1
                   //  GCode::executeFString(PSTR("M117 moveXY + manual")); 
                     HAL::delayMilliseconds(100);
                   //GCode::executeFString(PSTR("G91\n G1 X1 Y1 F300 \n G90\n")); 
                    
            break;
            
    /*  case 0xFFFD://2
                     GCode::executeFString(PSTR("M117 moveZ+ manual")); 
                     HAL::delayMilliseconds(100);
                     GCode::executeFString(PSTR("G91\n G1 Z0.001 F20 \n G90\n")); 
            break;
   
      case 0xFFFC://3
                  
                    action = UI_ACTION_Z_UP1 ;
            break;
               
      case 0xFFFB://4
                    GCode::executeFString(PSTR("M117 set FFF Mode")); 
                    GCode::executeFString(PSTR("M451")); 
                    HAL::delayMilliseconds(200);
                    GCode::executeFString(PSTR("M117")); 
            break;        
      
      case 0xFFFA://5
                    action = UI_ACTION_Z_DOWN01 ;
            break;  
                  
      case 0xFFF9://6
                    action = UI_ACTION_Z_DOWN1 ;
            break;        
      
      case 0xFFF8://7
                    action = UI_ACTION_Y_UP001 ;
            break;
            
      case 0xFFF7://8
                    GCode::executeFString(PSTR("M117 set LASER Mode")); 
                    GCode::executeFString(PSTR("M452")); 
                    HAL::delayMilliseconds(200);
                    GCode::executeFString(PSTR("M117")); 
            break;
           
       
      case 0xFFF6://9
                   action = UI_ACTION_Y_UP1 ;
            break;

      case 0xFFF5://10
                  action = UI_ACTION_Y_UP1 ;
            break;
     
      
      case 0xFFF4://11
                   action = UI_ACTION_Y_DOWN001 ;
            break;        
      
      case 0xFFF3://12
                  action = UI_ACTION_Y_DOWN01 ;
            break;  
                  
      case 0xFFF2://13
                   action = UI_ACTION_Y_DOWN1 ;
            break;        
    
      case 0xFFF1://14
                  action = UI_ACTION_Y_DOWN10 ;
            break;

     case 0xFFF0://15
                  action = UI_ACTION_Y_DOWN10 ;
            break;
            
    case 0xFFEF://16
                    GCode::executeFString(PSTR("M117 set CNC Mode")); 
                    GCode::executeFString(PSTR("M453")); 
                    HAL::delayMilliseconds(200);
                   // GCode::executeFString(PSTR("M117")); 
                    //GCode::executeMacro(HomeX);  //macro 
     */       break;
     
     default: 
       break;
   }
   //write keymask output just for playing with some LEDs
   // to indicate which button is pressed 
    HAL::i2cStartWait(MCP_OUT_ADDRESS + I2C_WRITE);
    HAL::i2cWrite(0x00);//IODIRA
    HAL::i2cWrite(0x0);
    HAL::i2cWrite(0x0);
    HAL::i2cStop(); 
  
    HAL::i2cStartWait(MCP_OUT_ADDRESS + I2C_WRITE);
    HAL::i2cWrite(0x12);//IODIRA
    HAL::i2cWrite(keymask1>>8);
    HAL::i2cWrite(keymask1);
    HAL::i2cStop(); 
}
#endif //macros

  
#if defined(UI_HAS_I2C_KEYS) && UI_HAS_KEYS!=0

#if UI_DISPLAY_I2C_CHIPTYPE==0
    HAL::i2cStartWait(UI_I2C_KEY_ADDRESS+I2C_READ);
    uint8_t keymask = HAL::i2cReadNak(); // Read current key mask
#endif //chiptype 0

#if UI_DISPLAY_I2C_CHIPTYPE==1
    HAL::i2cStartWait(UI_DISPLAY_I2C_ADDRESS+I2C_WRITE);
    HAL::i2cWrite(0x12); // GPIOA
    HAL::i2cStop();
    HAL::i2cStartWait(UI_DISPLAY_I2C_ADDRESS+I2C_READ);
    uint16_t keymask = HAL::i2cReadAck();
    keymask = keymask + (HAL::i2cReadNak()<<8);
#endif //chiptype 1

    HAL::i2cStop();
    // Add I2C key tests here
    UI_KEYS_I2C_CLICKENCODER_LOW_REV(_BV(2),_BV(0)); // click encoder on pins 0 and 2. Phase is connected with gnd for signals.
    UI_KEYS_I2C_BUTTON_LOW(_BV(1),UI_ACTION_OK); // push button, connects gnd to pin
    UI_KEYS_I2C_BUTTON_LOW(_BV(3),UI_ACTION_BACK); // push button, connects gnd to pin
    UI_KEYS_I2C_BUTTON_LOW(_BV(4),UI_ACTION_MENU_QUICKSETTINGS+UI_ACTION_TOPMENU); // push button, connects gnd to pin
    UI_KEYS_I2C_BUTTON_LOW(_BV(5),UI_ACTION_MENU_EXTRUDER+UI_ACTION_TOPMENU); // push button, connects gnd to pin
    UI_KEYS_I2C_BUTTON_LOW(_BV(6),UI_ACTION_MENU_POSITIONS+UI_ACTION_TOPMENU); // push button, connects gnd to pin
/*
  // Button handling for the Adafruit RGB shild
    UI_KEYS_I2C_BUTTON_LOW(4,UI_ACTION_PREVIOUS); // Up button
    UI_KEYS_I2C_BUTTON_LOW(8,UI_ACTION_NEXT); // down button
    UI_KEYS_I2C_BUTTON_LOW(16,UI_ACTION_BACK); // left button
    UI_KEYS_I2C_BUTTON_LOW(2,UI_ACTION_OK); // right button
    UI_KEYS_I2C_BUTTON_LOW(1,UI_ACTION_MENU_QUICKSETTINGS);  //Select button
  // ----- End RGB shield ----------
  */


   /* MCP23017_KEYS_I2C_BUTTON_LOW(_BV(1),UI_ACTION_OK); // push button, connects gnd to pin
    MCP23017_KEYS_I2C_BUTTON_LOW(_BV(3),UI_ACTION_BACK); // push button, connects gnd to pin
    MCP23017_KEYS_I2C_BUTTON_LOW(_BV(8),UI_ACTION_MENU_QUICKSETTINGS+UI_ACTION_TOPMENU); // push button, connects gnd to pin
    MCP23017_KEYS_I2C_BUTTON_LOW(_BV(15),UI_ACTION_MENU_EXTRUDER+UI_ACTION_TOPMENU); // push button, connects gnd to pin
    MCP23017_KEYS_I2C_BUTTON_LOW(_BV(6),UI_ACTION_MENU_POSITIONS+UI_ACTION_TOPMENU); // push button, connects gnd to pin
*/

 
#endif
}//end check slow keys
 

#endif
#endif





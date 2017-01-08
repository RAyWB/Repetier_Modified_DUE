#ifndef USERPINS_H
#define USERPINS_H

/*
 * PINOUT GIOVANNI_SHIELD 29_06_2016
 */
 
#if MOTHERBOARD == 999



#ifndef __SAM3X8E__
#error Oops!  Make sure you have 'Arduino Due' selected from the 'Tools -> Boards' menu.
#endif

#define KNOWN_BOARD
#define CPU_ARCH ARCH_ARM
/*****************************************************************
* Arduino Due Pin Assignments
******************************************************************/

#define ORIG_X_STEP_PIN     23
#define ORIG_X_DIR_PIN      24
#define ORIG_X_ENABLE_PIN   22   

#define ORIG_Y_STEP_PIN     25 
#define ORIG_Y_DIR_PIN      26
#define ORIG_Y_ENABLE_PIN   22

#define ORIG_Z_STEP_PIN     28
#define ORIG_Z_DIR_PIN      29
#define ORIG_Z_ENABLE_PIN   27

#define ORIG_E0_STEP_PIN    31
#define ORIG_E0_DIR_PIN     32
#define ORIG_E0_ENABLE_PIN  30


#define ORIG_E1_STEP_PIN    34
#define ORIG_E1_DIR_PIN     35
#define ORIG_E1_ENABLE_PIN  33

#define ORIG_E2_STEP_PIN    37
#define ORIG_E2_DIR_PIN     38
#define ORIG_E2_ENABLE_PIN  36


#define TEMP_BED_PIN     7     //AD7 Due A0
#define TEMP_1_PIN       6     //AD6 Due A1
#define TEMP_2_PIN       5     //AD5 Due A2
#define TEMP_3_PIN       4     //AD4 Due A3
#define TEMP_4_PIN       -1//3 
#define TEMP_5_PIN       -1//2 
#define TEMP_6_PIN       -1//1 
#define TEMP_7_PIN       -1//0 

#define ORIG_ADC_KEYPAD_PIN  3  //AD2 Due A5
#define ORIG_ADC_KEYPAD2_PIN 2  //AD1 Due A6
#define ORIG_ADC_KEYPAD3_PIN 1  //AD0 Due A7


#define ORIG_X_MIN_PIN      62  //62 bis 69 Analogpin als digital
#define ORIG_X_MAX_PIN      -1

#define ORIG_Y_MIN_PIN      63
#define ORIG_Y_MAX_PIN      -1

#define ORIG_Z_MIN_PIN      -1
#define ORIG_Z_MAX_PIN      64

#define ORIG_Z_PROBE_PIN    65  


// PWM Outputs 2 bis 13

#define HEATER_BED_PIN       2     //PWM
#define HEATER_1_PIN         3
#define HEATER_2_PIN         4
#define HEATER_3_PIN         5
#define EXT0_FAN_PIN         6
#define EXT1_FAN_PIN         7
#define EXT2_FAN_PIN         8
// frei                      9
#define ORIG_LASER_PIN       10
#define ORIG_FAN_PIN         11 
#define ORIG_FAN2_PIN        12 
#define ORIG_FAN_BOARD_PIN   13  

//0n/0ff   14...17

#define ORIG_CNC_ENABLE_PIN  14
#define ORIG_CNC_DIR_PIN     15
#define ORIG_CASE_LIGHTS_PIN 16
//frei                       17

#define ORIG_BEEPER_PIN          -1
#define ORIG_PS_ON_PIN           -1
#define LED_PIN                  -1
#define KILL_PIN                 -1
#define SUICIDE_PIN              -1  //PIN that has to be turned on right after start, to keep power flowing.

// RAyWB special

#define ORIG_SAFETY_PIN          67 
#define ORIG_M6_ACK_PIN          66

 
#define HOME_BUTTON              61   //AD0 printedA7

//  UI PINS

#define UI_Display_Data          43
#define UI_Display_CS            44
#define UI_Display_CK            45
 
#define ENC_A                    46
#define ENC_B                    47

#define OK_BUTTON                48 

#define UI1_BUTTON               68 
#define UI2_BUTTON               69 

// SD
#define SDSUPPORT                 1
#define SDPOWER 	               -1
#define SDSS		                 52  // 4,10,52 if using HW SPI.
#define ORIG_SDCARDDETECT        49
#define SDCARDDETECTINVERTED      0


#define E0_PINS ORIG_E0_STEP_PIN,ORIG_E0_DIR_PIN,ORIG_E0_ENABLE_PIN,
#define E1_PINS ORIG_E1_STEP_PIN,ORIG_E1_DIR_PIN,ORIG_E1_ENABLE_PIN,
#define E2_PINS ORIG_E2_STEP_PIN,ORIG_E2_DIR_PIN,ORIG_E2_ENABLE_PIN,

#define SDA_PIN         20    // 20 or 70
#define SCL_PIN         21    // 21 or 71

#define TWI_CLOCK_FREQ          400000 //100000

// Serielles EEProm 24LC256

#define EEPROM_SERIAL_ADDR      0x50   // 7 bit i2c address (without R/W bit)
#define EEPROM_PAGE_SIZE        64     // page write buffer size
#define EEPROM_PAGE_WRITE_TIME  7      // page write time in milliseconds (docs say 5ms but that is too short)
#define EEPROM_ADDRSZ_BYTES     TWI_MMR_IADRSZ_2_BYTE
#define EEPROM_AVAILABLE 1

#endif// Motherboard 999
#endif// userpins_h



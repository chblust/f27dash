#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#define MAX_RPM 10500

#define LED_COUNT 64

#define SHIFT_LIGHT_COUNT 50

#define NUM_GEARS 4

// Start of the 7 segment display control LEDs (base 0 index)
#define SEGMENT_DISPLAY_START_LED 50

// Number of LEDs required to control 7-segment display
#define SEGMENT_DISPLAY_LED_COUNT 8

// Indexes (base 0) of LED indicator outputs of shift registers
#define AUTO_UP_LED_1 63 

#define AUTO_UP_LED_2 62

#define CRITICAL_ERROR_LED 61

#define WARNING_LED 60

#define DRS_LED 59

#define HOLD_LED 58

void updateLights();

void setRPM( unsigned int rpm );

void setAutoUp( unsigned char state );

void setCriticalError( unsigned char state );

void setWarning( unsigned char state );

void setDRS( unsigned char state );

void setHold( unsigned char state );

void setGearPosition( unsigned short int position );

#endif // LIGHTCONTROL_H
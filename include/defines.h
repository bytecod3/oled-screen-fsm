#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>

#define BAUDRATE        115200
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_RESET      -1
#define SCREEN_ADDRESS  0x3C

// button pin
#define MENU_BUTTON_PIN 5

/**
 * Serial debug
 */

#define debug(x)        Serial.print(x);
#define debugln(x)      Serial.println(x)
#define debugf(x, y)    Serial.printf(x, y)

#endif
/**
 * @brief This file implements a basic state machine for 
 * an I2C OLED screen
 */

#include <Arduino.h>
#include "defines.h"
#include  <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/**
 * scrren variables
 */
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/**
 * BASIC SWITCH CASE STATE MACHINE
 */
typedef enum states {
    HOME = 1,
    MENU_OPT_1,
    MENU_OPT_2,
    MENU_OPT_3
} screen_states_t;

screen_states_t current_state = screen_states_t::HOME;

/**
 * button press variables 
 */
uint8_t btn_press = 1;
uint8_t btn_prs_cnt = 0;

// PFPs
static void GPIO_init();
static uint8_t button_read();
static void SSD1306_display_init();
static void screen_show_home();
static void screen_show_mnu1();
static void screen_show_mnu2();
static void screen_show_mnu3();

static void SSD1306_display_init() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));

        // todo: retry I2C scanner 
  }

  display.clearDisplay();
}

//  gpio 
static void GPIO_init() {
    pinMode(MENU_BUTTON_PIN, INPUT);
}

static uint8_t button_read() {
    return digitalRead(MENU_BUTTON_PIN);
}

static void screen_show_home() {

}

void setup() {
    GPIO_init();
    SSD1306_display_init();
}

void loop() {

    // read menu button
    btn_press = button_read();

    // debug 
    debugln(btn_press);

    //
    if(!btn_press) {
        btn_prs_cnt++;
    }

    // check for number of presses
    if(btn_prs_cnt == 0) { // button not pressed
        current_state = screen_states_t::HOME;
    } else if(btn_prs_cnt == 1) {
        current_state = screen_states_t::MENU_OPT_1;
    } else if(btn_prs_cnt == 2) {
        current_state = screen_states_t::MENU_OPT_2;
    } else if(btn_prs_cnt == 3) {
        current_state = screen_states_t::MENU_OPT_3;
    } else {
        current_state = screen_states_t::HOME;
        btn_prs_cnt = 0; // loop back to 0
    }

    /**
     * handle the states based on button presses
     */
    switch (current_state) {
        case screen_states_t::HOME:
            screen_show_home();
            break;

        case screen_states_t::MENU_OPT_1:
            screen_show_mnu1();
            break;

        case screen_states_t::MENU_OPT_2:
           screen_show_mnu2();
            break;

        case screen_states_t::MENU_OPT_3:
            screen_show_mnu1();
            break;
        
        default:
            break;
        }

}

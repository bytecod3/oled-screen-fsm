/**
 * @brief This file implements a basic state machine for 
 * an I2C OLED screen
 */

#include <Arduino.h>
#include <Wire.h>
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
    HOME = 0,
    MENU_OPT_1,
    MENU_OPT_2,
    MENU_OPT_3
} screen_states_t;

screen_states_t current_state = screen_states_t::HOME;

char* states_str[4] = {
    "HOME",
    "MENU_OPT_1",
    "MENU_OPT_2",
    "MENU_OPT_3"
};

/**
 * button press variables 
 */
uint8_t btn_press = 1;
uint8_t btn_prs_cnt = 0;

// PFPs
static void GPIO_init();
static void button_read();
static void SSD1306_display_init();
static void screen_show_home();
static void screen_show_mnu1();
static void screen_show_mnu2();
static void screen_show_mnu3();

static void SSD1306_display_init() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
       debugln(F("SSD1306 allocation failed"));

        // todo: retry I2C scanner 
    } else {
        debugln("Screen found");
    }

  
}

//  gpio 
static void GPIO_init() {
    pinMode(MENU_BUTTON_PIN, INPUT);
}

unsigned long debounce_interval = 50; //millis
unsigned prev_press_time = 0;
unsigned current_press_time = 0;
uint8_t button_state; 
uint8_t last_button_state = HIGH;

static void button_read() {
    current_press_time = millis();
    if(current_press_time - prev_press_time >= debounce_interval) {
        button_state = digitalRead(MENU_BUTTON_PIN);
        if(button_state != last_button_state) {
            last_button_state = button_state;
            prev_press_time = millis();

            // action 
            if(button_state == HIGH) {
                btn_prs_cnt++;
            }
        }
    } 
}

static void test_screen() {
    display.clearDisplay();
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(4, 4);  

    display.print("hELL0 from this side");
    display.display();
}

/**
 * @brief show the home screen
 */
static void screen_show_home() {
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.println("HOME SCREEN");
    display.display();
}

static void screen_show_mnu1() {
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.println("MENU OPTION 1");
    display.display();
}

static void screen_show_mnu2() {
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.println("MENU OPTION 2");
    display.display();
}

static void screen_show_mnu3() {
    display.clearDisplay();
    display.setCursor(2,2);
    display.setTextSize(1);      
    display.setTextColor(SSD1306_WHITE); 
    display.println("MENU OPTION 3");
    display.display();
}

void setup() {
    Serial.begin(BAUDRATE);
    GPIO_init();
    SSD1306_display_init();
    test_screen();
}

void loop() {

    // read menu button
    button_read();

    // debug 
    //debug("Presses:");debugln(btn_prs_cnt);

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

    debug("Current state: "); debugln(states_str[current_state]);

    /**
     * handle the states based on button presses
     * SWITCH CASE STATE MACHINE 
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
            screen_show_mnu3();
            break;
        
        default:
            break;
        }

}

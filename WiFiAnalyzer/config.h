#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

//==================================================
// TFT Pins
//==================================================
#define TFT_CS      10
#define TFT_DC       9
#define TFT_RST      8

#define TFT_MOSI    11
#define TFT_MISO    13
#define TFT_SCLK    12

//==================================================
// Touch Pins
//==================================================
#define TOUCH_CS    17
#define TOUCH_IRQ   7

//==================================================
// Display
//==================================================
#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240

//==================================================
// Touch Calibration
//==================================================
constexpr float TOUCH_BX = -0.0888324901f;
constexpr float TOUCH_CX = 347.8807067871f;

constexpr float TOUCH_BY = -0.0643915012f;
constexpr float TOUCH_CY = 246.4649047852f;

#define TOUCH_SMOOTH 5

//==================================================
// UI Layout
//==================================================
#define HEADER_HEIGHT      32
#define FOOTER_HEIGHT       0

#define SCAN_BUTTON_W      70
#define SCAN_BUTTON_H      24

#define BACK_BUTTON_W      70
#define BACK_BUTTON_H      24

#define LIST_TOP           36
#define LIST_ITEM_HEIGHT   34
#define MAX_VISIBLE_ITEMS  5

//==================================================
// BUTTON POSITIONS (FIXED VALUES ONLY)
//==================================================
#define SCAN_BUTTON_X  242
#define SCAN_BUTTON_Y  4

#define BACK_BUTTON_X  8
#define BACK_BUTTON_Y  4

//==================================================
// Colors
//==================================================
#define COLOR_BACKGROUND   ILI9341_BLACK
#define COLOR_HEADER       ILI9341_NAVY
#define COLOR_BUTTON       ILI9341_BLUE
#define COLOR_BUTTON_TEXT  ILI9341_WHITE
#define COLOR_TEXT         ILI9341_WHITE
#define COLOR_TEXT_DIM     ILI9341_LIGHTGREY
#define COLOR_BORDER       ILI9341_DARKGREY
#define COLOR_SELECTED     ILI9341_DARKCYAN
#define COLOR_GOOD         ILI9341_GREEN
#define COLOR_MEDIUM       ILI9341_YELLOW
#define COLOR_WEAK         ILI9341_RED

//==================================================
// WiFi
//==================================================
#define MAX_NETWORKS   50
#define AUTO_SCAN_TIME  10000UL

//==================================================
// TFT & Touch Objects
//==================================================
extern Adafruit_ILI9341 tft;
extern XPT2046_Touchscreen ts;

//==================================================
// WiFi Structure
//==================================================
struct WifiInfo
{
    String ssid;
    int32_t rssi;
    uint8_t channel;
    wifi_auth_mode_t encryption;
};

extern WifiInfo networks[MAX_NETWORKS];
extern int networkCount;

//==================================================
// Screen State
//==================================================
enum UIScreen
{
    SCREEN_SCAN = 0,
    SCREEN_DETAIL
};

//==================================================
// Selected Network
//==================================================
extern int selectedNetwork;

//==================================================
// Touch Position
//==================================================
extern int touchX;
extern int touchY;
extern bool touchPressed;

//==================================================
// Utility
//==================================================
int RSSIToPercent(int rssi);
const char* EncryptionToString(wifi_auth_mode_t enc);

#endif
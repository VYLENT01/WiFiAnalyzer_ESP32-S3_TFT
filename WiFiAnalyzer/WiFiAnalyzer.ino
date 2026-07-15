#include "config.h"
#include "wifiScan.h"
#include "ui.h"
#include "touch.h"

//==================================================
// Globals (hardware objects)
//==================================================
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);

//==================================================
// Timing
//==================================================
static unsigned long lastScanTime = 0;

//==================================================
// Setup
//==================================================
void setup()
{
    Serial.begin(115200);

    SPI.begin(TFT_SCLK, TFT_MISO, TFT_MOSI);

    tft.begin();
    tft.setRotation(1);

    ts.begin();
    ts.setRotation(1);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);

    UI_Init();
    Touch_Init();

    WiFi_Scan();
    UI_Refresh();
}

//==================================================
// Loop
//==================================================
void loop()
{
    Touch_Update();

    // auto scan
    if (millis() - lastScanTime > AUTO_SCAN_TIME)
    {
        lastScanTime = millis();
        WiFi_Scan();
        UI_Refresh();
    }

    // scan button
    if (Touch_ScanPressed())
    {
        WiFi_Scan();
        UI_Refresh();
    }

    // back button
    if (Touch_BackPressed())
    {
        UI_Back();
    }

    // select wifi item
    int index = Touch_GetSelectedNetwork();
    if (index >= 0)
    {
        UI_OpenDetail(index);
    }
}
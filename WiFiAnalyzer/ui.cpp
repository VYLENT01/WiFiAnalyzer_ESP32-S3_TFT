#include "ui.h"
#include "wifiScan.h"
#include "touch.h"

//==================================================
// UI state
//==================================================
static UIScreen currentScreen = SCREEN_SCAN;

//==================================================
// UI state data
//==================================================
static int scrollOffset = 0;

//==================================================
// Init
//==================================================
void UI_Init()
{
    tft.fillScreen(COLOR_BACKGROUND);
    currentScreen = SCREEN_SCAN;
}

//==================================================
// Screen control
//==================================================
void UI_SetScreen(UIScreen screen)
{
    currentScreen = screen;
    UI_Refresh();
}

UIScreen UI_GetScreen()
{
    return currentScreen;
}

//==================================================
void UI_Back()
{
    if (currentScreen == SCREEN_DETAIL)
    {
        currentScreen = SCREEN_SCAN;
        UI_Refresh();
    }
}

//==================================================
void UI_OpenDetail(int index)
{
    selectedNetwork = index;
    currentScreen = SCREEN_DETAIL;
    UI_Refresh();
}

//==================================================
// Refresh
//==================================================
void UI_Refresh()
{
    tft.fillScreen(COLOR_BACKGROUND);

    if (currentScreen == SCREEN_SCAN)
        UI_DrawScanScreen();
    else
        UI_DrawDetailScreen();
}

//==================================================
// Header
//==================================================
void UI_DrawHeader(const String &title)
{
    tft.fillRect(0, 0, SCREEN_WIDTH, HEADER_HEIGHT, COLOR_HEADER);

    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(2);
    tft.setCursor(8, 8);
    tft.print(title);
}

//==================================================
// Scan Screen
//==================================================
void UI_DrawScanScreen()
{
    UI_DrawHeader("WiFi Analyzer");

    UI_DrawScanButton(false);
    UI_DrawWiFiList();
}

//==================================================
// Detail Screen
//==================================================
void UI_DrawDetailScreen()
{
    UI_DrawHeader("Network Detail");

    UI_DrawBackButton(false);
    UI_DrawNetworkDetail();
}

//==================================================
// Scan button
//==================================================
void UI_DrawScanButton(bool pressed)
{
    uint16_t color = pressed ? COLOR_SELECTED : COLOR_BUTTON;

    tft.fillRect(SCAN_BUTTON_X, SCAN_BUTTON_Y, SCAN_BUTTON_W, SCAN_BUTTON_H, color);

    tft.setTextColor(COLOR_BUTTON_TEXT);
    tft.setTextSize(1);
    tft.setCursor(SCAN_BUTTON_X + 10, SCAN_BUTTON_Y + 8);
    tft.print("SCAN");
}

//==================================================
// Back button
//==================================================
void UI_DrawBackButton(bool pressed)
{
    uint16_t color = pressed ? COLOR_SELECTED : COLOR_BUTTON;

    tft.fillRect(BACK_BUTTON_X, BACK_BUTTON_Y, BACK_BUTTON_W, BACK_BUTTON_H, color);

    tft.setTextColor(COLOR_BUTTON_TEXT);
    tft.setTextSize(1);
    tft.setCursor(BACK_BUTTON_X + 10, BACK_BUTTON_Y + 8);
    tft.print("BACK");
}

//==================================================
// WiFi list
//==================================================
void UI_DrawWiFiList()
{
    int count = WiFi_GetCount();
    WifiInfo *list = WiFi_GetList();

    for (int i = 0; i < count && i < MAX_VISIBLE_ITEMS; i++)
    {
        int realIndex = i + scrollOffset;
        if (realIndex >= count) break;

        int y = LIST_TOP + i * LIST_ITEM_HEIGHT;

        UI_DrawWiFiItem(realIndex, y, realIndex == selectedNetwork);
    }
}

//==================================================
void UI_DrawWiFiItem(int index, int y, bool selected)
{
    WifiInfo *list = WiFi_GetList();

    if (index < 0 || index >= WiFi_GetCount()) return;

    WifiInfo &n = list[index];

    uint16_t bg = selected ? COLOR_SELECTED : COLOR_BACKGROUND;

    tft.fillRect(0, y, SCREEN_WIDTH, LIST_ITEM_HEIGHT, bg);

    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(1);

    tft.setCursor(6, y + 6);
    tft.print(n.ssid.substring(0, 14));

    int percent = RSSIToPercent(n.rssi);

    tft.setCursor(200, y + 6);
    tft.print(percent);
    tft.print("%");
}

//==================================================
// Detail page
//==================================================
void UI_DrawNetworkDetail()
{
    WifiInfo *list = WiFi_GetList();

    if (selectedNetwork < 0 || selectedNetwork >= WiFi_GetCount())
        return;

    WifiInfo &n = list[selectedNetwork];

    int y = 50;

    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(2);

    tft.setCursor(10, y);
    tft.print(n.ssid);
    y += 30;

    tft.setCursor(10, y);
    tft.print("RSSI: ");
    tft.print(n.rssi);
    y += 30;

    tft.setCursor(10, y);
    tft.print("Channel: ");
    tft.print(n.channel);
    y += 30;

    tft.setCursor(10, y);
    tft.print("Security: ");
    tft.print(EncryptionToString(n.encryption));
}
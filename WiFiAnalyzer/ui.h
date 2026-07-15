#ifndef UI_H
#define UI_H

#include "config.h"

//==================================================
// UI Initialization
//==================================================
void UI_Init();

//==================================================
// Screen Control
//==================================================
void UI_SetScreen(UIScreen screen);
UIScreen UI_GetScreen();

void UI_Back();
void UI_OpenDetail(int index);

//==================================================
// Draw Screens
//==================================================
void UI_DrawScanScreen();
void UI_DrawDetailScreen();

//==================================================
// Header
//==================================================
void UI_DrawHeader(const String &title);

//==================================================
// Buttons
//==================================================
void UI_DrawScanButton(bool pressed = false);
void UI_DrawBackButton(bool pressed = false);

//==================================================
// WiFi List
//==================================================
void UI_DrawWiFiList();
void UI_DrawWiFiItem(int index, int y, bool selected);

//==================================================
// Detail Page
//==================================================
void UI_DrawNetworkDetail();

//==================================================
// Screen Refresh
//==================================================
void UI_Refresh();

#endif
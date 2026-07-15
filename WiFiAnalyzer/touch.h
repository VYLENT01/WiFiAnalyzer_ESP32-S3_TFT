#ifndef TOUCH_H
#define TOUCH_H

#include "config.h"

//--------------------------------------------------
// Touch initialization
//--------------------------------------------------
void Touch_Init(void);
void Touch_Update(void);

//--------------------------------------------------
// Raw touch
//--------------------------------------------------
bool Touch_IsTouched(void);
bool Touch_GetRaw(TS_Point &p);

//--------------------------------------------------
// Calibrated touch
//--------------------------------------------------
bool Touch_GetPoint(int &x, int &y);

//--------------------------------------------------
// Screen buttons
//--------------------------------------------------
bool Touch_ScanPressed(void);
bool Touch_BackPressed(void);

//--------------------------------------------------
// WiFi list selection
//--------------------------------------------------
int Touch_GetSelectedNetwork(void);

#endif
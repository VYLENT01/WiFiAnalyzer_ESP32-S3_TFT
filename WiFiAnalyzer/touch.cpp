#include "touch.h"
#include "wifiScan.h"

//==================================================
// Internal buffer (smoothing)
//==================================================
static int bufX[TOUCH_SMOOTH];
static int bufY[TOUCH_SMOOTH];
static int bufIndex = 0;

static int lastX = -1;
static int lastY = -1;

//==================================================
// Touch state
//==================================================
int touchX = 0;
int touchY = 0;
bool touchPressed = false;

//==================================================
// Init
//==================================================
void Touch_Init()
{
    ts.begin();
    ts.setRotation(1);

    for (int i = 0; i < TOUCH_SMOOTH; i++)
    {
        bufX[i] = 0;
        bufY[i] = 0;
    }
}

//==================================================
// Raw read
//==================================================
bool Touch_GetRaw(TS_Point &p)
{
    if (!ts.touched())
        return false;

    p = ts.getPoint();
    return true;
}

//==================================================
// Smooth helper
//==================================================
static int smooth(int *buf, int v)
{
    buf[bufIndex] = v;

    int sum = 0;
    for (int i = 0; i < TOUCH_SMOOTH; i++)
        sum += buf[i];

    return sum / TOUCH_SMOOTH;
}

//==================================================
// Convert calibrated touch
//==================================================
bool Touch_GetPoint(int &x, int &y)
{
    TS_Point p;

    if (!Touch_GetRaw(p))
    {
        touchPressed = false;
        return false;
    }

    int sx = smooth(bufX, p.x);
    int sy = smooth(bufY, p.y);

    bufIndex = (bufIndex + 1) % TOUCH_SMOOTH;

    float tx = TOUCH_BX * sx + TOUCH_CX;
    float ty = TOUCH_BY * sy + TOUCH_CY;

    x = (int)tx;
    y = (int)ty;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
    if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;

    touchX = x;
    touchY = y;
    touchPressed = true;

    return true;
}

//==================================================
// Update state
//==================================================
void Touch_Update()
{
    int x, y;

    if (Touch_GetPoint(x, y))
    {
        touchPressed = true;
        lastX = x;
        lastY = y;
    }
    else
    {
        touchPressed = false;
        lastX = -1;
        lastY = -1;
    }
}

//==================================================
// Simple state
//==================================================
bool Touch_IsTouched()
{
    return touchPressed;
}

//==================================================
// Scan button hitbox
//==================================================
bool Touch_ScanPressed()
{
    if (!touchPressed) return false;

    return (touchX >= SCAN_BUTTON_X &&
            touchX <= SCAN_BUTTON_X + SCAN_BUTTON_W &&
            touchY >= SCAN_BUTTON_Y &&
            touchY <= SCAN_BUTTON_Y + SCAN_BUTTON_H);
}

//==================================================
// Back button hitbox
//==================================================
bool Touch_BackPressed()
{
    if (!touchPressed) return false;

    return (touchX >= BACK_BUTTON_X &&
            touchX <= BACK_BUTTON_X + BACK_BUTTON_W &&
            touchY >= BACK_BUTTON_Y &&
            touchY <= BACK_BUTTON_Y + BACK_BUTTON_H);
}

//==================================================
// WiFi list selection
//==================================================
int Touch_GetSelectedNetwork()
{
    if (!touchPressed) return -1;

    int index = (touchY - LIST_TOP) / LIST_ITEM_HEIGHT;

    if (index < 0)
        return -1;

    if (index >= WiFi_GetCount())
        return -1;

    return index;
}
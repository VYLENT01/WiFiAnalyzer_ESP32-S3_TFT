#include "config.h"

//==================================================
// Globals
//==================================================
int selectedNetwork = -1;

//==================================================
// RSSI to percent
//==================================================
int RSSIToPercent(int rssi)
{
    if (rssi <= -100) return 0;
    if (rssi >= -50) return 100;
    return 2 * (rssi + 100);
}

//==================================================
// Encryption to string
//==================================================
const char* EncryptionToString(wifi_auth_mode_t enc)
{
    switch (enc)
    {
        case WIFI_AUTH_OPEN: return "OPEN";
        case WIFI_AUTH_WEP: return "WEP";
        case WIFI_AUTH_WPA_PSK: return "WPA";
        case WIFI_AUTH_WPA2_PSK: return "WPA2";
        case WIFI_AUTH_WPA_WPA2_PSK: return "WPA/WPA2";
        case WIFI_AUTH_WPA3_PSK: return "WPA3";
        default: return "?";
    }
}
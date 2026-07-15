#include "wifiScan.h"

//==================================================
// Globals (defined here once)
//==================================================
WifiInfo networks[MAX_NETWORKS];
int networkCount = 0;

//==================================================
// Clear results
//==================================================
void WiFi_Clear()
{
    networkCount = 0;
}

//==================================================
// Scan WiFi
//==================================================
void WiFi_Scan()
{
    WiFi_Clear();

    int n = WiFi.scanNetworks();

    if (n <= 0)
    {
        networkCount = 0;
        return;
    }

    networkCount = (n > MAX_NETWORKS) ? MAX_NETWORKS : n;

    for (int i = 0; i < networkCount; i++)
    {
        networks[i].ssid = WiFi.SSID(i);
        networks[i].rssi = WiFi.RSSI(i);
        networks[i].channel = WiFi.channel(i);
        networks[i].encryption = WiFi.encryptionType(i);
    }

    WiFi_SortByRSSI();
}

//==================================================
// Sort by RSSI (strongest first)
//==================================================
void WiFi_SortByRSSI()
{
    for (int i = 0; i < networkCount - 1; i++)
    {
        for (int j = i + 1; j < networkCount; j++)
        {
            if (networks[j].rssi > networks[i].rssi)
            {
                WifiInfo tmp = networks[i];
                networks[i] = networks[j];
                networks[j] = tmp;
            }
        }
    }
}

//==================================================
// Get count
//==================================================
int WiFi_GetCount()
{
    return networkCount;
}

//==================================================
// Get list pointer
//==================================================
WifiInfo* WiFi_GetList()
{
    return networks;
}

//==================================================
// Find index safety check
//==================================================
int WiFi_FindByIndex(int index)
{
    if (index < 0 || index >= networkCount)
        return -1;

    return index;
}
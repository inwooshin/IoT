#ifndef GOOGLE_H
#define GOOGLE_H

#define IO_USERNAME "EnochOf"
#define IO_KEY "aio_GIKS55qveBhkIml4iFUPJuNtX8tm"
#define WIFI_SSID "INS"
#define WIFI_PASS "sksmswjstjf2!"
#include "AdafruitIO_WiFi.h"
#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
#if !defined(SPIWIFI_SS) 
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif

#define intPin 

// io.run loop 

void google_setup();

void handleMessage(AdafruitIO_Data *data);

#endif

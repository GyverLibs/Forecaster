This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/Forecaster.svg?color=brightgreen)](https://github.com/GyverLibs/Forecaster/releases/latest/download/Forecaster.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/Forecaster.svg)](https://registry.platformio.org/libraries/gyverlibs/Forecaster)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Forecaster?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Forecaster
Pressure weather forecast library for Arduino
- Determination of short-term weather forecast by Zambretti algorithm
- Takes pressure, temperature, altitude above the sea and month of the year
- Determining the pressure trend using linearization

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **Forecaster** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/Forecaster/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="init"></a>
## Initialization
```cpp
Forecaster cond;
```

<a id="usage"></a>
## Use of use
```cpp
void setH(int h);               // set the height above sea level (in meters)
void addP(long P, float t);     // Add the current pressure to Pa and the temperature to C (every 30 minutes), here the calculation takes place.
void addPmm(float P, float t);  // add current pressure in mmHg and temperature in C (Each 30 minutes)
void setMonth(uint8_t month);   // Set a month (1-12), 0 to turn off seasonality
float getCast();                // Get a forecast (0 good weather) 10 downpours-storms
int getTrend();                 // Get a pressure change in Pa in 3 hours
```

<a id="example"></a>
## Example
```cpp
#include "Forecaster.h"
Forecaster cond;

void setup() {
  Serial.begin(9600);
  // set the altitude above sea level (Moscow 255 m)
  cond.setH(255);

  // If you have an RTC, you can set the month 1-12.
  //cond.setMonth(5);
}
void loop() {
  // timer
  static uint32_t tmr;
  if (millis() - tmr >= 30*60*1000ul) {
    tmr = millis();
    // Every 30 minutes transmit the current pressure (Pa) and temperature (C) from the sensor
    cond.addP(99218, 25.2);

    // getCast() returns the current forecast from 0 to 10
    // 0 - good weather, 10 and above - storm / shower
    Serial.println(cond.getCast());
  }
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - added a pressure trend in 3 hours
- v1.2 - compatibility esp8266/32

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.

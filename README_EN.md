This is an automatic translation, may be incorrect in some places. See sources and examples!

# Forecaster
Library for determining the weather forecast by pressure for Arduino
- Determination of a short-term weather forecast using the Zambretti algorithm
- Accepts pressure, temperature, height above ur. seas and month of the year
- Determining the pressure trend using linearization

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **Forecaster** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/Forecaster/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
Forecaster cond.
```

<a id="usage"></a>
## Usage
```cpp
void setH(int h); // set height above sea level (in meters)
void addP(long P, float t); // add the current pressure in Pa and temperature in C (EVERY 30 MINUTES), calculation is also performed here
void addPmm(float P, float t); // add current pressure in mmHg and temperature in C (EVERY 30 MINUTES)
void setMonth(uint8_t month); // set month (1-12), 0 to disable seasonality
float getCast(); // get forecast (0 good weather... 10 rainstorm)
int getTrend(); // get pressure change in Pa for 3 hours
```

<a id="example"></a>
## Example
```cpp
#include "Forecaster.h"
Forecaster cond.

void setup() {
  Serial.begin(9600);
  // set altitude above sea level (Moscow 255m)
  cond.setH(255);

  // if there is RTC - you can set the month 1-12
  //cond.setMonth(5);
}
void loop() {
  // timer for 30 minutes
  static uint32_t tmr;
  if (millis() - tmr >= 30*60*1000ul) {
    tmr = millis();
    // every 30 minutes we transmit the current pressure (Pa) and temperature (C) from the sensor
    cond.addPmm(99218, 25.2);

    // getCast() returns the current forecast from 0 to 10
    // 0 - good weather, 10 and above - storm/rain
    Serial.println(cond.getCast());
  }
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - added pressure trend output for 3 hours

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!
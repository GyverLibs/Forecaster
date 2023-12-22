This is an automatic translation, may be incorrect in some places. See sources and examples!

# Forecaster
Library for determining the forecast for pressure on arduino
- Definition of a short -term weather forecast for the Zambretti algorithm
- Takes pressure, temperature, height above the ur.Seas and month of the year
- Determination of the pressure trend using linarization

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** Forecaster ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/Forecaster/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Forecaster Cond;
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID Seth (inth);// set a height above sea level (in meters)
Void Addp (Long P, Float T);// Add the current pressure in PA and temperature in C (every 30 minutes), there is also a calculation
Void Addpm (Float P, Float T);// Add the current pressure in mm hg and temperature in C (every 30 minutes)
VOID SetMonth (Uint8_t Month);// install a month (1-12), 0 to turn off seasonality
Float getcast ();// Get a forecast (0 Good weather ... 10 rain-storm)
Inttrend ();// get a change in pressure in Pa in 3 hours
`` `

<a id="EXAMPLE"> </a>
## Example
`` `CPP
#include "Forecaster.h"
Forecaster Cond;

VOID setup () {
  Serial.Begin (9600);
  // set a height above sea level (Moscow 255m)
  Cond.Seth (255);

  // if there is RTC - you can install a month 1-12
  //cond.setmonth (5);
}
VOID loop () {
  // timer for 30 minutes
  Static uint32_t tmr;
  if (millis () - tmr> = 30*60*1000ul) {
    TMR = Millis ();
    // every 30 minutes we transmit the current pressure (PA) and temperature (c) from the sensor
    Cond.Addp (99218, 25.2);

    // getcast () returns the current forecast from 0 to 10
    // 0 - good weather, 10 and above - storm/rain
    Serial.println (cond.getcast ());
  }
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - added the output of the pressure trend in 3 hours
- V1.2 - Compatibility ESP8266/32

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code
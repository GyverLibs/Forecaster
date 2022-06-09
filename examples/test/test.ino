#include "Forecaster.h"
Forecaster cond;

void setup() {
  Serial.begin(9600);
  // установить высоту над уровнем моря (Москва 255м)
  cond.setH(255);

  // если есть RTC - можно установить месяц 1-12
  //cond.setMonth(5);
}
void loop() {
  // таймер на 30 минут  
  static uint32_t tmr;
  if (millis() - tmr >= 30*60*1000ul) {
    tmr = millis();
    // каждые 30 минут передаём текущее давление (Па) и температуру (С) с датчика
    cond.addP(99218, 25.2);

    // getCast() возвращает текущий прогноз от 0 до 10
    // 0 - хорошая погода, 10 и выше - шторм/ливень
    Serial.println(cond.getCast());
  }
}

[![latest](https://img.shields.io/github/v/release/GyverLibs/Forecaster.svg?color=brightgreen)](https://github.com/GyverLibs/Forecaster/releases/latest/download/Forecaster.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Forecaster?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Forecaster
Библиотека для определения прогноза погоды по давлению для Arduino
- Определение краткосрочного прогноза погоды по алгоритму Замбретти
- Принимает давление, температуру, высоту над ур. моря и месяц года
- Определение тренда давления при помощи линеаризации

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **Forecaster** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/Forecaster/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
```cpp
Forecaster cond;
```

<a id="usage"></a>
## Использование
```cpp
void setH(int h);               // установить высоту над уровнем моря (в метрах)
void addP(long P, float t);     // добавить текущее давление в Па и температуру в С (КАЖДЫЕ 30 МИНУТ), здесь же происходит расчёт
void addPmm(float P, float t);  // добавить текущее давление в мм.рт.ст и температуру в С (КАЖДЫЕ 30 МИНУТ)
void setMonth(uint8_t month);   // установить месяц (1-12), 0 чтобы отключить сезонность
float getCast();                // получить прогноз (0 хорошая погода... 10 ливень-шторм)
int getTrend();                 // получить изменение давления в Па за 3 часа
```

<a id="example"></a>
## Пример
```cpp
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
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - добавил вывод тренда давления за 3 часа
- v1.2 - совместимость esp8266/32

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код

/*
    Библиотека для определения прогноза погоды по давлению для Arduino
    Документация:
    GitHub: https://github.com/GyverLibs/Forecaster
    Возможности:
    - Определение краткосрочного прогноза погоды по алгоритму Замбретти
    - Принимает давление, температуру, высоту над ур. моря и месяц года
    - Определение тренда давления при помощи линеаризации
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    Основано на
    https://integritext.net/DrKFS/zambretti.htm

    Версии:
    v1.0 - релиз
    v1.1 - добавил вывод тренда давления за 3 часа
    v1.2 - совместимость esp8266/32
*/

#ifndef _Forecaster_h
#define _Forecaster_h
#include <Arduino.h>
#define _FC_SIZE 6  // размер буфера. Усреднение за 3 часа, при размере 6 - каждые 30 минут

class Forecaster {
public:
    // установить высоту над уровнем моря (в метрах)
    void setH(int h) {
        H = h * 0.0065f;
    }
    
    // добавить текущее давление в Па и температуру в С (КАЖДЫЕ 30 МИНУТ)
    // здесь же происходит расчёт прогноза
    void addP(long P, float t) {
        P = (float)P * pow(1 - H / (t + H + 273.15), -5.257);   // над уровнем моря
        if (!start) {
            start = true;
            for (uint8_t i = 0; i < _FC_SIZE; i++) Parr[i] = P;
        } else {
            for (uint8_t i = 0; i < (_FC_SIZE-1); i++) Parr[i] = Parr[i + 1];
            Parr[_FC_SIZE - 1] = P;
        }
        
        // расчёт изменения по наименьшим квадратам
        long sumX = 0, sumY = 0, sumX2 = 0, sumXY = 0;        
        for (int i = 0; i < _FC_SIZE; i++) {
            sumX += i;
            sumY += Parr[i];
            sumX2 += i * i;
            sumXY += Parr[i] * i;
        }
        float a = _FC_SIZE * sumXY - sumX * sumY;
        a /= _FC_SIZE * sumX2 - sumX * sumX;
        delta = a * (_FC_SIZE - 1);
        
        // расчёт прогноза по Zambretti
        P /= 100;   // -> ГПа
        if (delta > 150) cast = 160 - 0.155 * P - season;        // rising
        else if (delta < -150) cast = 130 - 0.124 * P + season;  // falling
        else cast = 138 - 0.133 * P;                             // steady
        if (cast < 0) cast = 0;
    }
    
    // добавить текущее давление в мм.рт.ст и температуру в С (КАЖДЫЕ 30 МИНУТ)
    void addPmm(float P, float t) {
        addP(P * 133.322f, t);
    }
    
    // установить месяц (1-12)
    // 0 чтобы отключить сезонность
    void setMonth(uint8_t month) {
        if (month == 0) season = 0;
        else season = (month >= 4 && month <= 9) ? 2 : 1;
        /*
        if (month == 12) month = 0;
        month /= 3;                         // 0 зима, 1 весна, 2 лето, 3 осень
        season = month * 0.5 + 1;           // 1, 1.5, 2, 2.5
        if (season == 2.5) season = 1.5;    // 1, 1.5, 2, 1.5
        */
    }
    
    // получить прогноз (0 хорошая погода... 10 ливень-шторм)
    float getCast() {
        return cast;
    }
    
    // получить изменение давления в Па за 3 часа
    int getTrend() {
        return delta;
    }
    
private:
    long Parr[_FC_SIZE];
    float H = 0;
    bool start = false;
    float cast = 0;
    int delta = 0;
    uint8_t season = 0;
};
#endif
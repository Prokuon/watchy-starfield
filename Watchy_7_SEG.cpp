#include "Watchy_7_SEG.h"

// DARKMODE
// #define DARKMODE false

// HOUR_SET, change it to 12 to switch to 12-hour
// #define HOUR_SET 24

// change it to your location 
//          latitude, longitude, timezone
#define LOC 31.00, 121.00, 8

RTC_DATA_ATTR bool DARKMODE = false;
// RTC_DATA_ATTR int showState = 0;
RTC_DATA_ATTR bool HOUR_SET = true;

moonPhaser moonP;

void Watchy7SEG::handleButtonPress()
{
    if (guiState == WATCHFACE_STATE)
    {
        uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
        if (wakeupBit & UP_BTN_MASK) 
        {
            // showState++;
            // if (showState > 2) { showState = 0; }
            HOUR_SET = !HOUR_SET;
            RTC.read(currentTime);
            showWatchFace(true);
            return;
        }
        if (wakeupBit & DOWN_BTN_MASK) 
        {
            // showState--;
            // if (showState < 0) { showState = 2; }
            HOUR_SET = !HOUR_SET;
            RTC.read(currentTime);
            showWatchFace(true);
            return;
        }
        if (wakeupBit & BACK_BTN_MASK) 
        {
            DARKMODE = !DARKMODE;
            RTC.read(currentTime);
            showWatchFace(true);
            return;
        } 
        if (wakeupBit & MENU_BTN_MASK) 
        {
            Watchy::handleButtonPress();
            return;
        }
    } 
    else {Watchy::handleButtonPress();}
    return;
}

void Watchy7SEG::drawWatchFace()
{
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawFiel ();
    drawTime();
    drawDate();
    drawSteps();
    // drawWeather();
    drawBattery();
    // drawEva();
    // drawLine();

    display.drawBitmap(118, 168, WIFI_CONFIGURED ? wifi : wifioff, 25, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // if(BLE_CONFIGURED)
    // {
    //     display.drawBitmap(100, 75, bluetooth, 13, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // }
    drawMoon();
    drawSun();
}

void Watchy7SEG::drawTime()
{
    display.setFont(&DSEG7_Classic_Bold_53);
    display.setCursor(6, 53+5);
    // int displayHour;
    // if(HOUR_SET==12)
    // {
    //     displayHour = ((currentTime.Hour+11)%12)+1;
    // } 
    // else 
    // {
    //     displayHour = currentTime.Hour;
    // }
    // if(displayHour < 10)
    // {
    //     display.print("0");
    // }
    // display.print(displayHour);
    // display.print(":");
    // if(currentTime.Minute < 10)
    // {
    //     display.print("0");
    // }
    // display.println(currentTime.Minute);
    long ss = currentTime.Hour * 60 + currentTime.Minute;
    int sh = ss / 60;

    if (HOUR_SET == false && sh >= 12)
    {
        display.fillRect(7, 60, 25, 9, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
        display.drawBitmap(7, 60, pm, 25, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else if (HOUR_SET == false && sh < 12)
    {
        display.fillRect(7, 60, 25, 9, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
        display.drawBitmap(7, 60, am, 25, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    if (HOUR_SET == false && sh > 12)
    {
        sh -= 12;
    }
    int sm = ss % 60;
    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;

    if (a == 0)
        display.drawBitmap(11, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        display.drawBitmap(11, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        display.drawBitmap(11, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        display.drawBitmap(11, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        display.drawBitmap(11, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        display.drawBitmap(11, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        display.drawBitmap(11, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        display.drawBitmap(11, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        display.drawBitmap(11, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        display.drawBitmap(11, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        display.drawBitmap(55, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        display.drawBitmap(55, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        display.drawBitmap(55, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        display.drawBitmap(55, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        display.drawBitmap(55, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        display.drawBitmap(55, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        display.drawBitmap(55, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        display.drawBitmap(55, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        display.drawBitmap(55, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        display.drawBitmap(55, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        display.drawBitmap(111, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        display.drawBitmap(111, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        display.drawBitmap(111, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        display.drawBitmap(111, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        display.drawBitmap(111, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        display.drawBitmap(111, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        display.drawBitmap(111, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        display.drawBitmap(111, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        display.drawBitmap(111, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        display.drawBitmap(111, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        display.drawBitmap(155, 5, fd_0, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        display.drawBitmap(155, 5, fd_1, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        display.drawBitmap(155, 5, fd_2, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        display.drawBitmap(155, 5, fd_3, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        display.drawBitmap(155, 5, fd_4, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        display.drawBitmap(155, 5, fd_5, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        display.drawBitmap(155, 5, fd_6, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        display.drawBitmap(155, 5, fd_7, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        display.drawBitmap(155, 5, fd_8, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        display.drawBitmap(155, 5, fd_9, 33, 53, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        
}

void Watchy7SEG::drawDate()
{
    display.setFont(&Seven_Segment10pt7b);

    int16_t  x1, y1;
    uint16_t w, h;

    String dayOfWeek = dayStr(currentTime.Wday);
    dayOfWeek = dayOfWeek.substring(0, dayOfWeek.length() - 3);
    display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
    if(currentTime.Wday == 4)
    {
        w = w - 5;
    }
    display.setCursor(76 - w, 86);
    display.println(dayOfWeek);

    String month = monthShortStr(currentTime.Month);
    display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
    display.setCursor(79 - w, 110);
    display.println(month);

    // display.setFont(&DSEG7_Classic_Bold_25);
    // display.setCursor(6, 120);
    // if(currentTime.Day < 10)
    // {
    // display.print("0");
    // }
    // display.println(currentTime.Day);
    // display.setCursor(6, 154);
    // display.println(tmYearToCalendar(currentTime.Year));// offset from 1970, since year is stored in uint8_t

    int da = currentTime.Day;
    int ye = currentTime.Year + 1970;

    int a = da / 10;
    int b = da % 10;
    int c = ye / 1000;
    ye = ye % 1000;
    int d = ye / 100;
    ye = ye % 100;
    int e = ye / 10;
    ye = ye % 10;
    int f = ye;

    if (a == 0)
        display.drawBitmap(8, 95, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        display.drawBitmap(8, 95, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        display.drawBitmap(8, 95, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        display.drawBitmap(8, 95, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        display.drawBitmap(8, 95, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        display.drawBitmap(8, 95, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        display.drawBitmap(8, 95, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        display.drawBitmap(8, 95, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        display.drawBitmap(8, 95, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        display.drawBitmap(8, 95, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        display.drawBitmap(29, 95, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        display.drawBitmap(29, 95, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        display.drawBitmap(29, 95, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        display.drawBitmap(29, 95, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        display.drawBitmap(29, 95, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        display.drawBitmap(29, 95, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        display.drawBitmap(29, 95, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        display.drawBitmap(29, 95, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        display.drawBitmap(29, 95, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        display.drawBitmap(29, 95, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        display.drawBitmap(8, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        display.drawBitmap(8, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        display.drawBitmap(8, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        display.drawBitmap(8, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        display.drawBitmap(8, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        display.drawBitmap(8, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        display.drawBitmap(8, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        display.drawBitmap(8, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        display.drawBitmap(8, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        display.drawBitmap(8, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        display.drawBitmap(29, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        display.drawBitmap(29, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        display.drawBitmap(29, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        display.drawBitmap(29, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        display.drawBitmap(29, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        display.drawBitmap(29, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        display.drawBitmap(29, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        display.drawBitmap(29, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        display.drawBitmap(29, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        display.drawBitmap(29, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        display.drawBitmap(50, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        display.drawBitmap(50, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        display.drawBitmap(50, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        display.drawBitmap(50, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        display.drawBitmap(50, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        display.drawBitmap(50, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        display.drawBitmap(50, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        display.drawBitmap(50, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        display.drawBitmap(50, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        display.drawBitmap(50, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        display.drawBitmap(71, 129, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        display.drawBitmap(71, 129, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        display.drawBitmap(71, 129, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        display.drawBitmap(71, 129, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        display.drawBitmap(71, 129, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        display.drawBitmap(71, 129, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        display.drawBitmap(71, 129, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        display.drawBitmap(71, 129, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        display.drawBitmap(71, 129, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        display.drawBitmap(71, 129, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

}
void Watchy7SEG::drawSteps()
{
    // reset step counter at midnight
    if (currentTime.Hour == 0 && currentTime.Minute == 0)
    {
        // st4 = st3;
        // st3 = st2;
        // st2 = st1;
        // st1 = stepCount;
        sensor.resetStepCounter();
        // stepCount = 0;
    }
    uint32_t stepCount = sensor.getCounter();

    // display.drawBitmap(10, 165, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.setCursor(6, 190);
    // if (stepCount >= 10000)
    //     ;
    // else if (stepCount >= 1000)
    //     display.print("0");
    // else if (stepCount >= 100)
    //     display.print("00");
    // else if (stepCount >= 10)
    //     display.print("000");
    // else if (stepCount >= 0)
    //     display.print("0000");
    // display.println(stepCount);

    // uint32_t l1 = 61 * st1 / 20000;
    // uint32_t l2 = 61 * st2 / 20000;
    // uint32_t l3 = 61 * st3 / 20000;
    // uint32_t l4 = 61 * st4 / 20000;
    uint32_t l5 = 61 * stepCount / 10000;

    if (l5 > 61)
    {
        l5 = 61;
    }

    // display.fillRect(125, 73 + 61 - l1, 9, l4, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.fillRect(143, 73 + 61 - l1, 9, l3, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.fillRect(161, 73 + 61 - l1, 9, l2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.fillRect(179, 73 + 61 - l1, 9, l1, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillRect(131, 148, l5, 9, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.

    int a = stepCount / 10000;
    stepCount = stepCount % 10000;
    int b = stepCount / 1000;
    stepCount = stepCount % 1000;
    int c = stepCount / 100;
    stepCount = stepCount % 100;
    int d = stepCount / 10;
    int e = stepCount % 10;

    if (a == 0)
        display.drawBitmap(8, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        display.drawBitmap(8, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        display.drawBitmap(8, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        display.drawBitmap(8, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        display.drawBitmap(8, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        display.drawBitmap(8, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        display.drawBitmap(8, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        display.drawBitmap(8, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        display.drawBitmap(8, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        display.drawBitmap(8, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        display.drawBitmap(29, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        display.drawBitmap(29, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        display.drawBitmap(29, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        display.drawBitmap(29, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        display.drawBitmap(29, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        display.drawBitmap(29, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        display.drawBitmap(29, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        display.drawBitmap(29, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        display.drawBitmap(29, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        display.drawBitmap(29, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        display.drawBitmap(50, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        display.drawBitmap(50, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        display.drawBitmap(50, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        display.drawBitmap(50, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        display.drawBitmap(50, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        display.drawBitmap(50, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        display.drawBitmap(50, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        display.drawBitmap(50, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        display.drawBitmap(50, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        display.drawBitmap(50, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        display.drawBitmap(71, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        display.drawBitmap(71, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        display.drawBitmap(71, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        display.drawBitmap(71, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        display.drawBitmap(71, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        display.drawBitmap(71, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        display.drawBitmap(71, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        display.drawBitmap(71, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        display.drawBitmap(71, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        display.drawBitmap(71, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        display.drawBitmap(92, 165, dd_0, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        display.drawBitmap(92, 165, dd_1, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        display.drawBitmap(92, 165, dd_2, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        display.drawBitmap(92, 165, dd_3, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        display.drawBitmap(92, 165, dd_4, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        display.drawBitmap(92, 165, dd_5, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        display.drawBitmap(92, 165, dd_6, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        display.drawBitmap(92, 165, dd_7, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        display.drawBitmap(92, 165, dd_8, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        display.drawBitmap(92, 165, dd_9, 16, 25, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);



}
void Watchy7SEG::drawBattery()
{
    // display.drawBitmap(154, 73, battery, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // display.fillRect(159, 78, 27, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);//clear battery segments
    int8_t batteryLevel = 0;
    float VBAT = getBatteryVoltage();
    if(VBAT > 4.1)
    {
        batteryLevel = 37;
    }
    else if(VBAT > 4.05 && VBAT <= 4.1)
    {
        batteryLevel = 33;
    }
    else if(VBAT > 4 && VBAT <= 4.05)
    {
        batteryLevel = 28;
    }

    else if(VBAT > 3.95 && VBAT <= 4)
    {
        batteryLevel = 23;
    }
    else if(VBAT > 3.9 && VBAT <= 3.95)
    {
        batteryLevel = 18;
    }
    else if(VBAT > 3.85 && VBAT <= 3.9)
    {
        batteryLevel = 13;
    }
    else if(VBAT > 3.8 && VBAT <= 3.85)
    {
        batteryLevel = 8;
    }
    else if(VBAT > 3.75 && VBAT <= 3.8)
    {
        batteryLevel = 4;
    }
    else if(VBAT <= 3.75)
    {
        batteryLevel = 0;
    }

    // for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++)
    // {
        display.fillRect(155, 169, batteryLevel, 15, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    // }
}



void Watchy7SEG::drawFiel()
{
    display.drawBitmap(0, 0, field, 200, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}


void Watchy7SEG::drawMoon() {
    moonData_t moon;                        // variable to receive the data
    
    // January 31st, 2020 @ 1:30PM UTC
    int year = currentTime.Year + 1970;
    int32_t month = currentTime.Month;
    int32_t day = currentTime.Day;
    double hour = currentTime.Hour + 0.1;

    moon = moonP.getPhase(year, month, day, hour);

    int ag = moon.angle;
    double lt = moon.percentLit;



    // Waxing: 0-180
    // Waning: 180-360
    // display.setCursor(100, 74);

    if (ag <= 180)
    {
        if (lt < 0.1)
            display.drawBitmap(131, 74, luna1, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            display.drawBitmap(131, 74, luna12, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            display.drawBitmap(131, 74, luna11, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            display.drawBitmap(131, 74, luna10, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            display.drawBitmap(131, 74, luna9, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            display.drawBitmap(131, 74, luna8, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else 
            display.drawBitmap(131, 74, luna7, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }
    else
    {
        if (lt < 0.1)
            display.drawBitmap(131, 74, luna1, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.25)
            display.drawBitmap(131, 74, luna2, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.4)
            display.drawBitmap(131, 74, luna3, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.6)
            display.drawBitmap(131, 74, luna4, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.75)
            display.drawBitmap(131, 74, luna5, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else if (lt < 0.9)
            display.drawBitmap(131, 74, luna6, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
        else 
            display.drawBitmap(131, 74, luna7, 61, 61, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    }

    // display.print(year);
    // // display.print(moon.angle);
    // display.setCursor(100, 100);
    // // display.print(moon.percentLit);
    // display.print(month);

    // display.setCursor(100, 130);
    // display.print(day);
    //  Serial.print( "Moon phase angle: " );
    //  Serial.print( moon.angle );             // angle is a integer between 0-360
    //  Serial.println( " degrees." );
    //  Serial.print( "Moon surface lit: " );
    //  Serial.println( moon.percentLit * 100 );  // percentLit is a real between 0-1
}

void Watchy7SEG::drawSun() {
    Dusk2Dawn location(LOC);
    int year = currentTime.Year + 1970;
    int32_t month = currentTime.Month;
    int32_t day = currentTime.Day;
    int sr = location.sunrise(year, month, day, false);
    int ss = location.sunset(year, month, day, false);

    long k = currentTime.Hour * 60 + currentTime.Minute;
    int tk = (k - sr) * 60 / (ss - sr);
    if (k > ss)
        tk = 60;
    else if (k < sr)
        tk = 0;
    display.drawBitmap(110, 132 - tk, arr, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    int rh = sr / 60;
    int rm = sr % 60;
    int sh = ss / 60;
    int sm = ss % 60;

    if (HOUR_SET == false && rh > 12)
    {
        rh -= 12;
    }

    if (HOUR_SET == false && sh >12)
    {
        sh -= 12;
    }

    int a = sh >= 10 ? sh / 10 : 0;
    int b = sh % 10;
    int c = sm >= 10 ? sm / 10 : 0;
    int d = sm % 10;
    int e = rh >= 10 ? rh / 10 : 0;
    int f = rh % 10;
    int g = rm >= 10 ? rm / 10 : 0;
    int h = rm % 10;

    if (a == 0)
        display.drawBitmap(116, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 1)
        display.drawBitmap(116, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 2)
        display.drawBitmap(116, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 3)
        display.drawBitmap(116, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 4)
        display.drawBitmap(116, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 5)
        display.drawBitmap(116, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 6)
        display.drawBitmap(116, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 7)
        display.drawBitmap(116, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 8)
        display.drawBitmap(116, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (a == 9)
        display.drawBitmap(116, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (b == 0)
        display.drawBitmap(120, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 1)
        display.drawBitmap(120, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 2)
        display.drawBitmap(120, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 3)
        display.drawBitmap(120, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 4)
        display.drawBitmap(120, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 5)
        display.drawBitmap(120, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 6)
        display.drawBitmap(120, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 7)
        display.drawBitmap(120, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 8)
        display.drawBitmap(120, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (b == 9)
        display.drawBitmap(120, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (c == 0)
        display.drawBitmap(128, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 1)
        display.drawBitmap(128, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 2)
        display.drawBitmap(128, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 3)
        display.drawBitmap(128, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 4)
        display.drawBitmap(128, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 5)
        display.drawBitmap(128, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 6)
        display.drawBitmap(128, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 7)
        display.drawBitmap(128, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 8)
        display.drawBitmap(128, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (c == 9)
        display.drawBitmap(128, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (d == 0)
        display.drawBitmap(132, 67, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 1)
        display.drawBitmap(132, 67, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 2)
        display.drawBitmap(132, 67, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 3)
        display.drawBitmap(132, 67, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 4)
        display.drawBitmap(132, 67, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 5)
        display.drawBitmap(132, 67, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 6)
        display.drawBitmap(132, 67, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 7)
        display.drawBitmap(132, 67, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 8)
        display.drawBitmap(132, 67, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (d == 9)
        display.drawBitmap(132, 67, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (e == 0)
        display.drawBitmap(116, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 1)
        display.drawBitmap(116, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 2)
        display.drawBitmap(116, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 3)
        display.drawBitmap(116, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 4)
        display.drawBitmap(116, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 5)
        display.drawBitmap(116, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 6)
        display.drawBitmap(116, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 7)
        display.drawBitmap(116, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 8)
        display.drawBitmap(116, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (e == 9)
        display.drawBitmap(116, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (f == 0)
        display.drawBitmap(120, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 1)
        display.drawBitmap(120, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 2)
        display.drawBitmap(120, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 3)
        display.drawBitmap(120, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 4)
        display.drawBitmap(120, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 5)
        display.drawBitmap(120, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 6)
        display.drawBitmap(120, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 7)
        display.drawBitmap(120, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 8)
        display.drawBitmap(120, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (f == 9)
        display.drawBitmap(120, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (g == 0)
        display.drawBitmap(128, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 1)
        display.drawBitmap(128, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 2)
        display.drawBitmap(128, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 3)
        display.drawBitmap(128, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 4)
        display.drawBitmap(128, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 5)
        display.drawBitmap(128, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 6)
        display.drawBitmap(128, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 7)
        display.drawBitmap(128, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 8)
        display.drawBitmap(128, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (g == 9)
        display.drawBitmap(128, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    if (h == 0)
        display.drawBitmap(132, 137, num_0, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 1)
        display.drawBitmap(132, 137, num_1, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 2)
        display.drawBitmap(132, 137, num_2, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 3)
        display.drawBitmap(132, 137, num_3, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 4)
        display.drawBitmap(132, 137, num_4, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 5)
        display.drawBitmap(132, 137, num_5, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 6)
        display.drawBitmap(132, 137, num_6, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 7)
        display.drawBitmap(132, 137, num_7, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 8)
        display.drawBitmap(132, 137, num_8, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    else if (h == 9)
        display.drawBitmap(132, 137, num_9, 3, 5, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

//void Watchy7SEG::drawWeather()
//{
//
//    weatherData currentWeather = getWeatherData();
//
//    int8_t temperature = currentWeather.temperature;
//    int16_t weatherConditionCode = currentWeather.weatherConditionCode;
//
//    display.setFont(&DSEG7_Classic_Regular_39);
//    int16_t  x1, y1;
//    uint16_t w, h;
//    display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
//    if(159 - w - x1 > 87)
//    {
//        display.setCursor(159 - w - x1, 150);
//    }
//    else
//    {
//        display.setFont(&DSEG7_Classic_Bold_25);
//        display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
//        display.setCursor(159 - w - x1, 136);
//    }
//    display.println(temperature);
//    display.drawBitmap(165, 110, currentWeather.isMetric ? celsius : fahrenheit, 26, 20, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
//    const unsigned char* weatherIcon;
//
//    //https://openweathermap.org/weather-conditions
//    if(weatherConditionCode > 801)
//    {
//        //Cloudy
//        weatherIcon = cloudy;
//    }
//    else if(weatherConditionCode == 801)
//    {
//        //Few Clouds
//        weatherIcon = cloudsun;
//    }
//    else if(weatherConditionCode == 800)
//    {
//        //Clear
//        weatherIcon = sunny;
//    }
//    else if(weatherConditionCode >=700)
//    {
//        //Atmosphere
//        weatherIcon = atmosphere;
//    }
//    else if(weatherConditionCode >=600)
//    {
//        //Snow
//        weatherIcon = snow;
//    }
//    else if(weatherConditionCode >=500)
//    {
//        //Rain
//        weatherIcon = rain;
//    }
//    else if(weatherConditionCode >=300)
//    {
//        //Drizzle
//        weatherIcon = drizzle;
//    }
//    else if(weatherConditionCode >=200)
//    {
//        //Thunderstorm
//        weatherIcon = thunderstorm;
//    }
//    else
//        return;
//    display.drawBitmap(145, 158, weatherIcon, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
//}

// void Watchy7SEG::drawEva()
// {
//     display.drawBitmap(105, 100, eva, 100, 100, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
// }

// void Watchy7SEG::drawLine()
// {
//     display.drawBitmap(100, 72, line, 1, 77, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
// }
